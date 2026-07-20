/** @file
 * Implementation of @ref gamma.h.
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 17.04.2020
 */

#include "gamma.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../UI/strings.h"
#include "find-union.h"
#include "gamma-move.h"
#include "gamma-struct.h"

/** @brief Macro @ref gamma_new.
 */
#define GAMMA_DELETE(g) \
  do {                  \
    gamma_delete(g);    \
    return NULL;        \
  } while (false);

/** @brief Initial memory allocation and initialization of variables.
 * @param[in] g       - pointer to the board to be allocated,
 * @param[in] width   - board's width, positive integer,
 * @param[in] height  - board's height, positive integer,
 * @param[in] players - number of players, positive integer,
 * @param[in] areas   – maximum number of areas, which one player can possess.
 * @return @p true if operation succeeded and @p false if not enough memory or
 * incorrect arguments.
 */
static bool initial_init(gamma_t** g, uint32_t width, uint32_t height,
                         uint32_t players, uint32_t areas) {
  if (width == 0 || height == 0 || players == 0 || areas == 0) return false;

  if (NULL == (*g = malloc(sizeof **g))) return false;

  (*g)->width = width;
  (*g)->height = height;
  (*g)->areas_number = areas;
  (*g)->players_number = players;

  // Multiply it like this so there is no overflow.
  (*g)->free_fields = (*g)->width;
  (*g)->free_fields *= (*g)->height;

  (*g)->free_neighbours = NULL;
  (*g)->busy_fields = NULL;
  (*g)->areas = NULL;
  (*g)->golden_not_used = NULL;
  (*g)->board = NULL;
  (*g)->visited = NULL;
  (*g)->stack = NULL;
  (*g)->top = 0;

  return true;
}

/** @brief Allocate memory for player specific fields and initialize them.
 * @param[in] g - game's state.
 * @return @p true on success and @p false if no memory.
 */
static bool init_players(gamma_t* g) {
  g->free_neighbours = calloc(g->players_number, sizeof *(g->free_neighbours));
  if (g->free_neighbours == NULL) return false;

  g->busy_fields = calloc(g->players_number, sizeof *(g->busy_fields));
  if (g->busy_fields == NULL) return false;

  g->areas = calloc(g->players_number, sizeof *(g->areas));
  if (g->areas == NULL) return false;

  g->golden_not_used = calloc(g->players_number, sizeof *(g->golden_not_used));
  if (g->golden_not_used == NULL) return false;

  for (uint32_t i = 0; i < g->players_number; ++i) g->golden_not_used[i] = true;
  return true;
}

/** @brief Allocate the board and set every field to empty.
 * @return @p true on success and @p false if no memory.
 */
static bool init_board(gamma_t* g) {
  if (NULL == (g->board = calloc(g->height, sizeof *(g->board)))) return false;

  for (uint32_t i = 0; i < g->height; ++i) {
    g->board[i] = calloc(g->width, sizeof *(g->board[i]));
    if (g->board[i] == NULL) return false;

    for (uint32_t j = 0; j < g->width; ++j) {
      g->board[i][j] = malloc(sizeof *(g->board[i][j]));
      if (g->board[i][j] == NULL) return false;

      make_set(g->board[i][j], NOPLAYER);
    }
  }
  return true;
}

/** Allocate and initialize auxilary DS for DFS in @ref gamma_golden_move.
 * Allocate upfront and initialize `visited` array and `stack` for DFS in
 * @ref gamma_golden_move.
 * @return @p true on success and @p false if no memory.
 */
static bool init_dfs_aux(gamma_t* g) {
  g->visited = calloc(g->height, sizeof *(g->visited));
  if (g->visited == NULL) return false;

  for (uint32_t i = 0; i < g->height; ++i) {
    g->visited[i] = calloc(g->width, sizeof *(g->visited[i]));
    if (g->visited[i] == NULL) return false;
  }

  g->stack = calloc(g->free_fields, sizeof *(g->stack));
  if (g->stack == NULL) return false;

  return true;
}

gamma_t* gamma_new(uint32_t width, uint32_t height, uint32_t players,
                   uint32_t areas) {
  gamma_t* g = NULL;
  if (!initial_init(&g, width, height, players, areas)) GAMMA_DELETE(g);
  if (!init_players(g)) GAMMA_DELETE(g);
  if (!init_board(g)) GAMMA_DELETE(g);
  if (!init_dfs_aux(g)) GAMMA_DELETE(g);
  return g;
}

void gamma_delete(gamma_t* g) {
  if (g != NULL) {
    if (g->board != NULL) {
      for (uint32_t i = 0; i < g->height; ++i) {
        if (g->board[i] != NULL) {
          for (uint32_t j = 0; j < g->width; ++j) free(g->board[i][j]);
          free(g->board[i]);
        }
      }
      free(g->board);
    }

    if (g->visited != NULL) {
      for (uint32_t i = 0; i < g->height; ++i) free(g->visited[i]);
      free(g->visited);
    }

    free(g->free_neighbours);
    free(g->busy_fields);
    free(g->areas);
    free(g->golden_not_used);
    free(g->stack);
    free(g);
  }
}

bool gamma_move(gamma_t* g, uint32_t player, uint32_t col, uint32_t line) {
  if (g == NULL) return false;

  line = g->height - line - 1;
  field_t field = {.col = col, .line = line};
  if (!gamma_move_possible(g, player, field)) return false;

  bool neighbour_exists = exists_neighbour(g, player, field);
  if (!neighbour_exists) ++(g->areas[player - 1]);

  ++(g->busy_fields[player - 1]);
  --(g->free_fields);
  update_free_neighbours(g, player, col, line, false);
  make_set(g->board[line][col], player);

  if (neighbour_exists) {
    elem_t *neighbours[NEIGHBOURS_COUNT], *united = g->board[line][col];
    size_t neighbours_num = set_neighbours(g, player, field, neighbours);
    aggregate_unite(neighbours_num, neighbours, united);
    g->areas[united->player - 1] -= neighbours_num - 1;
  }
  return true;
}

bool gamma_golden_move(gamma_t* g, uint32_t player, uint32_t col,
                       uint32_t line) {
  if (!player_is_ok(g, player)) return false;

  line = g->height - line - 1;
  field_t field = {.col = col, .line = line};
  if (!coords_are_ok(g, field)) return false;

  elem_t former = *(g->board[line][col]);
  make_set(g->board[line][col], NOPLAYER);

  if (!gamma_move_possible(g, player, field) ||
      !g->golden_not_used[player - 1] || former.player == NOPLAYER ||
      former.player == player) {
    *(g->board[line][col]) = former;
    return false;
  }

  elem_t* areas[NEIGHBOURS_COUNT];
  uint32_t areas_count = make_areas(g, former.player, field, areas);

  if ((uint64_t)g->areas[former.player - 1] - UINT64_C(1) + areas_count >
      g->areas_number) {
    elem_t* root = g->board[line][col];
    make_set(root, former.player);
    aggregate_unite((size_t)areas_count, areas, root);
    return false;
  }

  --(g->areas[former.player - 1]);
  g->areas[former.player - 1] += areas_count;

  --(g->busy_fields[former.player - 1]);
  g->golden_not_used[player - 1] = false;
  ++(g->free_fields);
  update_free_neighbours(g, former.player, col, line, true);

  line = g->height - line - 1;
  bool success = gamma_move(g, player, col, line);
  assert(success);
  return success;
}

uint64_t gamma_busy_fields(gamma_t* g, uint32_t player) {
  return player_is_ok(g, player) ? g->busy_fields[player - 1] : 0;
}

uint64_t gamma_free_fields(gamma_t* g, uint32_t player) {
  return !player_is_ok(g, player) ? 0
         : g->areas[player - 1] == g->areas_number
             ? g->free_neighbours[player - 1]
             : g->free_fields;
}

/** @brief Odwraca skutki wykonania ruchu innego gracza na pole
 * (`x`, `y`), zajęte przez gracza o numerze `player`.
 */
static void reverse_gamma_move(gamma_t* g, uint32_t player, uint32_t x,
                               uint32_t y) {
  bool gamma_golden_not_used = g->golden_not_used[player - 1];
  g->golden_not_used[player - 1] = true;
  gamma_golden_move(g, player, x, y);
  g->golden_not_used[player - 1] = gamma_golden_not_used;
}

bool gamma_golden_possible(gamma_t* g, uint32_t player) {
  bool is_possible = false;
  if (!player_is_ok(g, player)) return is_possible;
  if (g->golden_not_used[player - 1] == false) return is_possible;

  if (g->areas[player - 1] == g->areas_number) {
    uint32_t x, y, former_player;
    for (y = g->height; (y--) > 0 && !is_possible;) {
      for (x = 0; x < g->width && !is_possible; ++x) {
        former_player = g->board[y][x]->player;
        is_possible = gamma_golden_move(g, player, x, y);
      }
    }
    if (is_possible) {
      g->golden_not_used[player - 1] = true;
      reverse_gamma_move(g, former_player, x, y);
    }
  } else {
    for (uint32_t i = 0; i < g->players_number; ++i) {
      if (i + 1 != player && g->busy_fields[i] != 0) return true;
    }
  }

  return is_possible;
}

char* gamma_board(gamma_t* g) {
  if (g == NULL) return NULL;

  unsigned column_width = count_digits(g->players_number);
  if (column_width > 1) ++column_width;
  // TODO overflow, dokladnosc?
  char* str =
      calloc(g->height /* number of lines */ *
                     ((uint64_t)g->width * column_width + 1 /* newline */) +
                 1 /* null-termination */,
             sizeof *str);
  if (str == NULL) return NULL;

  char* buffer = calloc(column_width + 1, sizeof *buffer);
  if (buffer == NULL) return NULL;
  buffer[column_width] = '\0';

  size_t count = 0;
  for (uint32_t i = 0; i < g->height; ++i) {
    for (uint32_t j = 0; j < g->width; ++j) {
      assert(sprintf(buffer, "%*" PRIu32, column_width,
                     g->board[i][j]->player) > 0);
      if (g->board[i][j]->player == NOPLAYER) buffer[column_width - 1] = '.';

      strcpy(str + count, buffer);
      count += column_width;
    }
    str[count++] = '\n';
  }

  str[count] = '\0';
  free(buffer);
  return str;
}
