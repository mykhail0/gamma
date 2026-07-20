/** @file
 * Implementation of @ref batch-mode.h
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 17.05.2020
 */

/// To use `getline`.
#define _GNU_SOURCE

#include "batch-mode.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../game_engine/gamma.h"
#include "error-handling.h"
#include "strings.h"

/// Position of `player` parameter in an arguments array.
#define PLAYER 0
/// Position of `x` parameter in an arguments array.
#define X 1
/// Position of `y` parameter in an arguments array.
#define Y 2

/// Number of commands in the batch moode.
#define POSSIBLE_COMMANDS 8

/// Number of parameters for command NO_COMMAND.
#define NO_COMMAND_PARAMS 0
/// Number of parameters for command INVALID_COMMAND.
#define INVALID_COMMAND_PARAMS 0
/// Number of parameters for command GAMMA_MOVE.
#define GAMMA_MOVE_PARAMS 3
/// Number of parameters for command GAMMA_GOLDEN_MOVE.
#define GAMMA_GOLDEN_MOVE_PARAMS 3
/// Number of parameters for command GAMMA_BUSY_FIELDS.
#define GAMMA_BUSY_FIELDS_PARAMS 1
/// Number of parameters for command GAMMA_FREE_FIELDS.
#define GAMMA_FREE_FIELDS_PARAMS 1
/// Number of parameters for command GAMMA_GOLDEN_POSSIBLE.
#define GAMMA_GOLDEN_POSSIBLE_PARAMS 1
/// Number of parameters for command GAMMA_BOARD.
#define GAMMA_BOARD_PARAMS 0

/// Maximum number of parameters for a command.
#define MAX_PARAMS_NUM 3

/** Possible commands in the batch mode.
 * Used to index into @ref COMMAND_CHARACTERS and @ref params_number.
 */
typedef enum {
  NO_COMMAND,
  INVALID_COMMAND,
  GAMMA_MOVE,
  GAMMA_GOLDEN_MOVE,
  GAMMA_BUSY_FIELDS,
  GAMMA_FREE_FIELDS,
  GAMMA_GOLDEN_POSSIBLE,
  GAMMA_BOARD
} command_t;

/// Characters for each command.
static const char COMMAND_CHARACTERS[] = "mgbfqp";

/// Number of expected parameters for each type of command.
static const size_t params_number[POSSIBLE_COMMANDS] = {
    NO_COMMAND_PARAMS,
    INVALID_COMMAND_PARAMS,
    GAMMA_MOVE_PARAMS,
    GAMMA_GOLDEN_MOVE_PARAMS,
    GAMMA_BUSY_FIELDS_PARAMS,
    GAMMA_FREE_FIELDS_PARAMS,
    GAMMA_GOLDEN_POSSIBLE_PARAMS,
    GAMMA_BOARD_PARAMS};

/// Process `m` command.
static void process_gamma_move(gamma_t* g, uint32_t params[]) {
  printf("%d\n", (int)gamma_move(g, params[PLAYER], params[X], params[Y]));
}

/// Process `g` command.
static void process_gamma_golden_move(gamma_t* g, uint32_t params[]) {
  printf("%d\n",
         (int)gamma_golden_move(g, params[PLAYER], params[X], params[Y]));
}

/// Process `b` command.
static void process_gamma_busy_fields(gamma_t* g, uint32_t params[]) {
  printf("%" PRIu64 "\n", gamma_busy_fields(g, params[PLAYER]));
}

/// Process `f` command.
static void process_gamma_free_fields(gamma_t* g, uint32_t params[]) {
  printf("%" PRIu64 "\n", gamma_free_fields(g, params[PLAYER]));
}

/// Process `q` command.
static void process_gamma_golden_possible(gamma_t* g, uint32_t params[]) {
  printf("%d\n", (int)gamma_golden_possible(g, params[PLAYER]));
}

/// Process `p` command.
static void process_gamma_board(gamma_t* g) {
  char* board = gamma_board(g);
  if (board == NULL)
    puts("0");
  else
    printf("%s", board);
  free(board);
}

/// Process a given command.
static void process_command(command_t com, gamma_t* g, uint32_t params[]) {
  switch (com) {
    case GAMMA_MOVE:
      process_gamma_move(g, params);
      break;
    case GAMMA_GOLDEN_MOVE:
      process_gamma_golden_move(g, params);
      break;
    case GAMMA_BUSY_FIELDS:
      process_gamma_busy_fields(g, params);
      break;
    case GAMMA_FREE_FIELDS:
      process_gamma_free_fields(g, params);
      break;
    case GAMMA_GOLDEN_POSSIBLE:
      process_gamma_golden_possible(g, params);
      break;
    case GAMMA_BOARD:
      process_gamma_board(g);
      break;
    default:
      assert(false);
      break;
  }
}

/// Parse a string into an appropriate command code.
static command_t parse_command(char* line) {
  if (line == NULL || line[0] == '\n' || line[0] == '#') return NO_COMMAND;

  char* first_word = strtok(line, WHITE_SPACE);
  command_t command = INVALID_COMMAND;
  if (first_word != NULL && strlen(first_word) == 1 &&
      // No white spaces at the beginning of the line allowed.
      first_word[0] == line[0]) {
    const char* command_ptr = strchr(COMMAND_CHARACTERS, first_word[0]);
    if (command_ptr != NULL)
      command = GAMMA_MOVE + (command_t)(command_ptr - COMMAND_CHARACTERS);
  }
  return command;
}

// TODO getline handling more graceful
/// Process a single line.
static int process_line(gamma_t* g, unsigned long long* line) {
  ++(*line);
  char* str = NULL;
  size_t str_size = 0;
  errno = 0;
  ssize_t getline_result = getline(&str, &str_size, stdin);
  if (getline_result == -1) {
    free(str);
    return getline_result;
  }

  // Mogę zrzutować ponieważ nie jest równe - 1
  if ((size_t)getline_result != strlen(str)) {
    free(str);
    printERR(*line);
    return getline_result;
  }

  command_t command = parse_command(str);
  if (command == NO_COMMAND || command == INVALID_COMMAND) {
    if (command == INVALID_COMMAND) printERR(*line);
    free(str);
    return getline_result;
  }

  uint32_t params[MAX_PARAMS_NUM];
  size_t params_count = params_number[command];

  bool params_are_correct = get_uints(params_count, params);
  free(str);

  if (params_are_correct) {
    process_command(command, g, params);
  } else {
    printERR(*line);
  }

  return getline_result;
}

/// Process inputs line by line.
static void process(gamma_t* g, unsigned long long* line) {
  bool reached_EOF = false;
  errno = 0;
  while (errno != ENOMEM && !reached_EOF) {
    errno = 0;
    reached_EOF = process_line(g, line) == -1;
  }
}

bool batch_mode(unsigned long long* line, uint32_t width, uint32_t height,
                uint32_t players, uint32_t areas) {
  gamma_t* g = gamma_new(width, height, players, areas);
  bool success = false;
  if (g) {
    printf("OK %llu\n", *line);
    process(g, line);
    gamma_delete(g);
    success = true;
  } else {
    printERR(*line);
  }
  return success;
}
