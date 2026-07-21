/** @file
 * Implementation of @ref interactive-mode.h
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 17.05.2020
 */

#include "interactive-mode.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "../game_engine/gamma-move.h"
#include "../game_engine/gamma.h"
#include "strings.h"

/// Ctrl+d character.
static const int EOT = '\4';

/// @brief Cursor's coordinates.
static point_t cursor;

/// @brief Drawn board's height.
static uint32_t HEIGHT;

/// @brief Drawn board's width.
static uint32_t WIDTH;

/// @brief Drawn column's width.
static unsigned COLUMN_WIDTH;

/// @brief Auxilary buffer to write over board's fields.
char buffer[MAX_COLUMN_WIDTH];

/// Reset all visual attributes.
static inline void reset_attributes() { printf("\033[m"); }

/// Clear screen, go to left top corner.
static inline void top_left() { printf("\033[2J\033[H"); }

/// @brief Move cursor to given coordinates of the drawn board.
static inline void move_cursor(point_t x) {
  printf("\033[%" PRIu32 ";%" PRIu32 "H", x.line, x.col);
}

/// @brief Convert cursor coordinates to field coordinates for @ref gamma_move.
static void cursor_to_pos(uint32_t* x, uint32_t* y) {
  *y = HEIGHT - cursor.line;
  *x = cursor.col / COLUMN_WIDTH - 1;
}

/// @brief Move cursor back if possible.
static void cursor_back() {
  if (cursor.col == COLUMN_WIDTH) return;
  cursor.col -= COLUMN_WIDTH;
}

/// @brief Move cursor down if possible.
static void cursor_down() {
  if (cursor.line == HEIGHT) return;
  ++cursor.line;
}

/// @brief Move cursor up if possible.
static void cursor_up() {
  if (cursor.line == 1) return;
  --cursor.line;
}

/// @brief Move cursor forward if possible.
static void cursor_forward() {
  if (cursor.col == WIDTH) return;
  cursor.col += COLUMN_WIDTH;
}

/// Check if a @p player has a valid move to make.
static inline bool has_a_move(gamma_t* g, uint32_t player) {
  return gamma_free_fields(g, player) > 0 || gamma_golden_possible(g, player);
}

/** @brief Increment @p player index until finding a player that can move, if
 * possible.
 * @param[in] g          - game's state,
 * @param[in,out] player - incremented player.
 * @return @p true iff found a player that can make a move.
 */
static bool next_player(gamma_t* g, uint32_t* player) {
  uint32_t start = *player;
  *player = (*player) % g->players_number + 1;
  while (*player != start && !has_a_move(g, *player)) {
    *player = (*player) % g->players_number + 1;
  }
  return *player != start || has_a_move(g, *player);
}

/// @brief Turn off cursor blink and scrolling.
static void cursor_and_scrolling() {
  // Turn off cursor blink.
  printf("\033[?25l");
  // Turn off ability to scroll.
  printf("\033[?1049h");
}

/// @brief Bring back cursor and scrolling.
static void bring_back_cursor() {
  // Scrolling.
  printf("\033[?1049l");
  // Cursor.
  printf("\033[?25h");
}

/// @brief Print a player's statistics.
static void print_player_stats(gamma_t* g, uint32_t player) {
  printf("PLAYER %" PRIu32 " %" PRIu64, player, gamma_busy_fields(g, player));
  bool use_red = g->areas[player - 1] == g->areas_number;
  if (use_red) printf("\033[31m");
  printf(" %" PRIu32 "/%" PRIu32, g->areas[player - 1], g->areas_number);
  if (use_red) printf("\033[m");
  // Use yellow color for golden move ability.
  if (g->golden_not_used[player - 1]) printf(" \033[33mG\033[m");
}

/// @brief Print board and prompt the player for a move.
static void print_board(gamma_t* g, uint32_t player) {
  if (g == NULL) return;

  uint32_t cursorX, cursorY;
  cursor_to_pos(&cursorX, &cursorY);

  top_left();
  for (uint32_t i = 0; i < g->height; ++i) {
    for (uint32_t j = 0; j < g->width; ++j) {
      sprintf(buffer, "%*" PRIu32, COLUMN_WIDTH, g->board[i][j]->player);
      if (g->board[i][j]->player == NOPLAYER) buffer[COLUMN_WIDTH - 1] = '.';

      bool use_reverse_video = g->height - i - 1 == cursorY && j == cursorX,
           use_green = g->board[i][j]->player == player;
      if (use_reverse_video) {
        // Reverse video in cursor's position.
        printf("\033[7m");
      }
      if (use_green) printf("\033[32m");

      printf("%s", buffer);

      if (use_green) printf("\033[m");
      if (use_reverse_video) printf("\033[m");
    }
    printf("\n");
  }
  print_player_stats(g, player);
  move_cursor(cursor);
}

/** @brief Processes a command from the given player.
 * @param[in] g                - game's state,
 * @param[in] player           - pointer to the index of a player making the
 *                               move,
 * @param[in] c                - pointer to the character to interpret,
 * @param[out] need_to_getchar - @p false if @p c already contains an
 *                               unprocessed character.
 * @return @p true iff the game has finished.
 */
static bool make_move(gamma_t* g, uint32_t* player, int* c,
                      bool* need_to_getchar) {
  if (*need_to_getchar) {
    *c = getchar();
    *need_to_getchar = false;
  }
  if (*c == EOF || *c == EOT) return false;
  *need_to_getchar = true;

  if (*c == 'c' || *c == 'C') return !next_player(g, player);

  uint32_t x, y;
  cursor_to_pos(&x, &y);
  if (*c == ' ') return gamma_move(g, *player, x, y) && !next_player(g, player);
  if (*c == 'g' || *c == 'G')
    return gamma_golden_move(g, *player, x, y) && !next_player(g, player);

  if (*c == '\033') {
    if (EOF == (*c = getchar())) return false;

    if (*c == '[') {
      if (EOF == (*c = getchar())) return false;

      if (*c == 'A') cursor_up();
      if (*c == 'B') cursor_down();
      if (*c == 'C') cursor_forward();
      if (*c == 'D') cursor_back();
      if (*c < 'A' || 'D' < *c) *need_to_getchar = false;
    } else {
      *need_to_getchar = false;
    }
  } else {
    *need_to_getchar = false;
  }

  return false;
}

/** @brief Process players' input.
 * @return @p true iff everything went well, @p false otherwise.
 */
static bool play(gamma_t* g) {
  uint32_t player = 1;
  bool game_finished = false, need_to_getchar = true;
  int c = '\n';

  for (print_board(g, player); c != EOF && c != EOT && !game_finished;
       print_board(g, player)) {
    game_finished = make_move(g, &player, &c, &need_to_getchar);
  }

  return c != EOF;
}

/// @brief Print players' statistics at the end of the game.
static void print_summary(gamma_t* g) {
  top_left();
  char* s = gamma_board(g);
  printf("%s", s);
  free(s);

  // Clear line.
  printf("\033[2K");
  for (uint32_t player = 0; player++ < g->players_number;) {
    print_player_stats(g, player);
    printf("\n");
  }
}

/** Check window size, set cursor position and drawn board size.
 * @return @p true iff success.
 */
static bool handle_windowsize(gamma_t* g) {
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) return false;

  COLUMN_WIDTH = count_digits(g->players_number);
  if (COLUMN_WIDTH > 1) COLUMN_WIDTH += 1;

  if ((uint64_t)g->width * COLUMN_WIDTH > UINT32_MAX) {
    // Overflow.
    return false;
  }
  HEIGHT = g->height;
  WIDTH = COLUMN_WIDTH * g->width;

  cursor.col = COLUMN_WIDTH * (g->width == 1 ? 1 : g->width / 2);
  cursor.line = HEIGHT == 1 ? 1 : HEIGHT / 2;

  if (w.ws_row < HEIGHT || w.ws_col < WIDTH) {
    puts("Please, resize your terminal window and make it bigger.");
    errno = 0;
    return false;
  }

  return true;
}

/** Set variables, constants and settings around the terminal.
 * @return @p true iff everything went fine, otherwise `errno` shows what's
 * wrong.
 */
static bool set_terminal(gamma_t* g, struct termios* oldt) {
  if (!handle_windowsize(g)) return false;
  // Set new terminal attributes and store the old ones.
  struct termios newt;
  if (tcgetattr(STDIN_FILENO, oldt) == -1) return false;
  newt = *oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  return tcsetattr(STDIN_FILENO, TCSANOW, &newt) != -1;
}

/** Prepare the terminal, variables and constants for the game.
 * errno is set when something doesn't succeed.
 * @return @ref gamma_t game state on success, @p NULL otherwise.
 */
gamma_t* prepare(struct termios* oldt, uint32_t width, uint32_t height,
                 uint32_t players, uint32_t areas) {
  errno = 0;
  gamma_t* g = gamma_new(width, height, players, areas);
  if (g == NULL) return g;
  assert(errno == 0);
  if (!set_terminal(g, oldt)) {
    gamma_delete(g);
    return NULL;
  }
  cursor_and_scrolling();
  return g;
}

bool interactive_mode(uint32_t width, uint32_t height, uint32_t players,
                      uint32_t areas) {
  struct termios oldt;
  gamma_t* g = prepare(&oldt, width, height, players, areas);
  if (g == NULL) return false;

  bool success = play(g);
  bring_back_cursor();

  if (success) print_summary(g);
  gamma_delete(g);

  if (!success) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return false;
  }

  return tcsetattr(STDIN_FILENO, TCSANOW, &oldt) != -1;
}
