/** @file
 * Implementation of @ref gamma-launch.h.
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 17.05.2020
 */

/// To use `getline`.
#define _GNU_SOURCE

#include "gamma-launch.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UI/batch-mode.h"
#include "UI/error-handling.h"
#include "UI/interactive-mode.h"
#include "UI/strings.h"

/// Number of parameters for a game mode.
#define PARAMS_COUNT 4

/// Possible game modes.
typedef enum { NOMODE, BATCH, INTERACTIVE } game_mode_t;

/** @brief Plays the game.
 * @param[in] mode     - game mode,
 * @param[in,out] line - a pointer to the line, if the mode is batch, this value
 *                       is updated,
 * @param[in] width    - board's width,
 * @param[in] height   - board's height,
 * @param[in] players  - number of players,
 * @param[in] areas    - number of allowed areas.
 * @return @p true iff the game was played successfully.
 */
static bool play_game(game_mode_t mode, unsigned long long* line,
                      uint32_t width, uint32_t height, uint32_t players,
                      uint32_t areas) {
  bool success = false;
  if (mode == BATCH) {
    success = batch_mode(line, width, height, players, areas);
  } else if (mode == INTERACTIVE) {
    success = interactive_mode(width, height, players, areas);
    if (!success) printERR(*line);
  }
  return success;
}

/** @brief Validate parameters for the given mode.
 * Launch the game if the parameters are correct.
 * @param[in] mode     - game mode,
 * @param[in,out] line - a pointer to the line, if the mode is batch, this value
 *                       is updated.
 * @return @p true iff the game was played successfully.
 */
static bool load_game(game_mode_t mode, unsigned long long* line) {
  uint32_t params[PARAMS_COUNT];
  bool success = get_uints(PARAMS_COUNT, params);
  if (success) {
    success = play_game(mode, line, params[0], params[1], params[2], params[3]);
  } else {
    printERR(*line);
  }
  return success;
}

// TODO more graceful getline handling
int launch_game() {
  bool successful_interactive = false, finished_on_failed_interactive = false;
  unsigned long long line_number = 1;
  char* line = NULL;
  size_t line_size = 0;

  for (ssize_t getline_result = getline(&line, &line_size, stdin);
       getline_result != -1 && !successful_interactive; ++line_number) {
    game_mode_t mode = NOMODE;
    char* first_word = strtok(line, WHITE_SPACE);
    if (first_word != NULL && strlen(first_word) == 1 &&
        // No white spaces at the beginning of the line allowed.
        first_word[0] == line[0]) {
      if (line[0] == 'B') mode = BATCH;
      if (line[0] == 'I') mode = INTERACTIVE;
    }
    if (mode == NOMODE && line[0] != '#' && line[0] != '\n')
      printERR(line_number);

    finished_on_failed_interactive = false;
    if (mode != NOMODE) {
      bool success = load_game(mode, &line_number);
      if (mode == INTERACTIVE) {
        finished_on_failed_interactive = !success;
        successful_interactive = success;
      }
    }

    if (!successful_interactive)
      getline_result = getline(&line, &line_size, stdin);
  }

  free(line);
  return finished_on_failed_interactive ? EXIT_FAILURE : EXIT_SUCCESS;
}
