/** @file
 * Implementation of @ref gamma-launch.h.
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 17.05.2020
 */

/** @brief To use `getline`.
 */
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
enum Mode { NOMODE, BATCH, INTERACTIVE };

typedef enum Mode game_mode_t;

/** @brief Plays the game.
 * @param[in] mode    - game mode,
 * @param[in] line    - a pointer to the line, if the mode is batch, this value
 *                      is updated,
 * @param[in] width   - board's width,
 * @param[in] height  - board's height,
 * @param[in] players - number of players,
 * @param[in] areas   - number of allowed areas.
 * @return @p true iff the game was played successfully.
 */
static bool play_game(game_mode_t mode, unsigned long long* line,
                      uint32_t width, uint32_t height, uint32_t players,
                      uint32_t areas) {
  return mode == BATCH         ? batch_mode(line, width, height, players, areas)
         : mode == INTERACTIVE ? interactive_mode(width, height, players, areas)
                               : false;
}

/** @brief Validate parameters for the given mode.
 * Launch the game if the parameters are correct.
 * @param[in] mode - game mode,
 * @param[in] line - a pointer to the line, if the mode is batch, this value is
 *                   updated.
 * @return @p true iff the game was played successfully.
 */
static bool load_game(game_mode_t mode, unsigned long long* line) {
  char* params_as_strings[PARAMS_COUNT];
  unsigned long params_as_ul[PARAMS_COUNT];
  uint32_t params_as_uint[PARAMS_COUNT];

  bool ans = get_strings(PARAMS_COUNT, params_as_strings);
  if (ans)
    ans = stringArr_to_ulArr(PARAMS_COUNT, params_as_strings, params_as_ul);
  if (ans) ans = ulArr_to_uintArr(PARAMS_COUNT, params_as_ul, params_as_uint);
  if (ans)
    ans = play_game(mode, line, params_as_uint[0], params_as_uint[1],
                    params_as_uint[2], params_as_uint[3]);

  if (!ans) printERR(*line);
  return ans;
}

int launch_game() {
  bool interactive_game_played = false;
  unsigned long long line_number = 1;
  char* line = NULL;
  size_t line_size = 0;
  ssize_t errsv = getline(&line, &line_size, stdin);

  while (errsv != -1 && !interactive_game_played) {
    game_mode_t mode = NOMODE;
    char* first_word = strtok(line, WHITE_SPACE);
    if (first_word != NULL) {
      if (strcmp(first_word, "B") == EQUAL && line[0] == 'B') mode = BATCH;
      if (strcmp(first_word, "I") == EQUAL && line[0] == 'I')
        mode = INTERACTIVE;
    }
    if (mode == NOMODE && line[0] != '#' && line[0] != '\n')
      printERR(line_number);

    if (mode != NOMODE) {
      interactive_game_played =
          load_game(mode, &line_number) && mode == INTERACTIVE;
    }

    if (!interactive_game_played) errsv = getline(&line, &line_size, stdin);
    ++line_number;
  }

  free(line);
  return EXIT_SUCCESS;
}
