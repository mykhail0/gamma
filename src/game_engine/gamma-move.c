/** @file
 * Implementation of @ref gamma-move.h.
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 18.04.2020
 */

#include "gamma-move.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "find-union.h"
#include "gamma-struct.h"

/// Difference between field coordinates.
typedef struct {
  /// Difference in lines.
  int32_t dline;
  /// Difference in columns.
  int32_t dcol;
} field_diff_t;

const uint32_t NOPLAYER = 0;

bool player_is_ok(const gamma_t* g, uint32_t player) {
  return g != NULL && 0 < player && player <= g->players_number;
}

bool coords_are_ok(const gamma_t* g, point_t field) {
  assert(g != NULL);
  return field.col < g->width && field.line < g->height;
}

/// Differences between adjacent fields' coordinates.
static const field_diff_t ADJACENT_DIFFS[NEIGHBOURS_COUNT] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

/// Apply a given difference in field coordinates to a given field.
static point_t apply_diff(point_t field, field_diff_t diff) {
  point_t diffed = {.line = field.line + diff.dline,
                    .col = field.col + diff.dcol};
  return diffed;
}

/// Check if the field moved by `ADJACENT_DIFFS[adj_i]` has correct coords.
static bool move_is_valid(const gamma_t* g, size_t adj_i, point_t field) {
  return (ADJACENT_DIFFS[adj_i].dline >= 0 || field.line != 0) &&
         (ADJACENT_DIFFS[adj_i].dcol >= 0 || field.col != 0) &&
         coords_are_ok(g, apply_diff(field, ADJACENT_DIFFS[adj_i]));
}

/** @brief Find fields neighbouring a given field.
 * @param[in] g           - game's state,
 * @param[out] neighbours - coordinates of the neighbours,
 * @param[in] field       - coordinates of the field whose neighbours we find.
 * @return The number of neighbours.
 */
static size_t find_neighbours(const gamma_t* g,
                              point_t neighbours[NEIGHBOURS_COUNT],
                              point_t field) {
  size_t i = 0;
  for (size_t j = 0; j < NEIGHBOURS_COUNT; ++j) {
    if (move_is_valid(g, j, field)) {
      neighbours[i++] = apply_diff(field, ADJACENT_DIFFS[j]);
    }
  }
  return i;
}

/** Find fields neighbouring a given field, that belong to the given player.
 * @param[in] g           - game's state,
 * @param[out] neighbours - coordinates of the neighbours,
 * @param[in] field       - coordinates of the field whose neighbours we find,
 * @param[in] player      - player we are looking for.
 * @return The number of neighbours.
 */
static size_t find_neighbour_player(const gamma_t* g,
                                    point_t neighbours[NEIGHBOURS_COUNT],
                                    point_t field, uint32_t player) {
  size_t i = 0;
  for (size_t j = 0; j < NEIGHBOURS_COUNT; ++j) {
    if (move_is_valid(g, j, field)) {
      neighbours[i] = apply_diff(field, ADJACENT_DIFFS[j]);
      if (g->board[neighbours[i].line][neighbours[i].col]->player == player)
        ++i;
    }
  }
  return i;
}

bool exists_neighbour(const gamma_t* g, uint32_t player, point_t field) {
  bool exists = false;
  for (size_t j = 0; !exists && j < NEIGHBOURS_COUNT; ++j) {
    if (move_is_valid(g, j, field)) {
      exists = g->board[field.line + ADJACENT_DIFFS[j].dline]
                       [field.col + ADJACENT_DIFFS[j].dcol]
                           ->player == player;
    }
  }
  return exists;
}

size_t set_neighbours(gamma_t* g, uint32_t player, point_t field,
                      elem_t* neighbours[NEIGHBOURS_COUNT]) {
  for (size_t i = 0; i < NEIGHBOURS_COUNT; ++i) neighbours[i] = NULL;

  size_t i = 0;
  for (size_t j = 0; j < NEIGHBOURS_COUNT; ++j) {
    if (move_is_valid(g, j, field)) {
      elem_t* neighbour = find(g->board[field.line + ADJACENT_DIFFS[j].dline]
                                       [field.col + ADJACENT_DIFFS[j].dcol]);
      if (neighbour->player == player) {
        bool is_unique = true;
        for (size_t k = 0; is_unique && k < i; ++k) {
          if (neighbours[k] == neighbour) is_unique = false;
        }
        if (is_unique) neighbours[i++] = neighbour;
      }
    }
  }
  return i;
}

bool gamma_move_possible(const gamma_t* g, uint32_t player, point_t field) {
  return player_is_ok(g, player) && coords_are_ok(g, field) &&
         g->board[field.line][field.col]->player == NOPLAYER &&
         (g->areas[player - 1] < g->areas_number ||
          exists_neighbour(g, player, field));
}

void update_free_neighbours(gamma_t* g, uint32_t player, uint32_t col,
                            uint32_t line, bool disappeared) {
  uint32_t player_encountered[NEIGHBOURS_COUNT];
  point_t neighbours[NEIGHBOURS_COUNT], field = {.line = line, .col = col};
  size_t neighbours_num = find_neighbours(g, neighbours, field);

  for (size_t i = 0; i < neighbours_num; ++i) {
    uint32_t p = g->board[neighbours[i].line][neighbours[i].col]->player;
    player_encountered[i] = NOPLAYER;
    if (p == NOPLAYER) {
      // Neighbouring field was empty, so it *may* change number of free
      // neighbours for the @p player.
      if (!exists_neighbour(g, player, neighbours[i]))
        g->free_neighbours[player - 1] += disappeared ? -1 : 1;
    } else {
      // Neighbouring field had some player on it, number of free neighbours
      // should change for them *once*.
      bool encountered = false;
      for (size_t j = 0; !encountered && j < i; ++j)
        encountered = p == player_encountered[j];
      if (!encountered) {
        player_encountered[i] = p;
        g->free_neighbours[p - 1] += disappeared ? 1 : -1;
      }
    }
  }
}

/** @brief Push a field onto the stack.
 * @param[in] g - game's state,
 * @param[in] x - field's coordinates.
 */
static void push(gamma_t* g, point_t x) {
  g->stack[g->top] = x;
  ++(g->top);
}

/** @brief Pop a field off the stack.
 * @param[in] g  - game's state,
 * @param[out] x - field's coordinates.
 */
static void pop(gamma_t* g, point_t* x) {
  --(g->top);
  *x = g->stack[g->top];
}

/** @brief Push not visited neighbours on the stack.
 * Push not visited neighbours of @p field such that belong to the same player
 * as on @p field on the stack.
 * @param[in] g     - game's state,
 * @param[in] field - field of interest.
 */
static void push_neighbours(gamma_t* g, point_t field) {
  point_t neighbours[NEIGHBOURS_COUNT];
  size_t neighbours_num = find_neighbour_player(
      g, neighbours, field, g->board[field.line][field.col]->player);

  for (size_t i = 0; i < neighbours_num; ++i) {
    if (!g->visited[neighbours[i].line][neighbours[i].col]) {
      g->visited[neighbours[i].line][neighbours[i].col] = true;
      push(g, neighbours[i]);
    }
  }
}

/** @brief Add visited neighbours of @p field on the stack.
 * @param[in] g     - game's state,
 * @param[in] field - field of interest.
 */
static void push_neighbours_clear(gamma_t* g, point_t field) {
  point_t neighbours[NEIGHBOURS_COUNT];
  size_t neighbours_num = find_neighbours(g, neighbours, field);

  for (size_t i = 0; i < neighbours_num; ++i) {
    if (g->visited[neighbours[i].line][neighbours[i].col]) {
      g->visited[neighbours[i].line][neighbours[i].col] = false;
      push(g, neighbours[i]);
    }
  }
}

/** @brief Set all fields connected to @p start as not visited.
 * @param[in] g     - game's state,
 * @param[in] start - starting field's coordinates.
 */
static void clear_visited(gamma_t* g, point_t start) {
  g->top = 0;
  g->visited[start.line][start.col] = false;
  push(g, start);
  while (g->top != 0) {
    point_t current;
    pop(g, &current);
    push_neighbours_clear(g, current);
  }
}

/** @brief Updates a player's area given a starting field using DFS.
 * @param[in] g - game's state,
 * @param[in] start - DFS starting point,
 * @param[in] neighbours_num - number of fields belonging to the player
 *                             adjacent to the removed piece,
 * @param[in] neighbours     - fields belonging to the player adjacent to the
 *                             removed piece,
 * @param[out] visited       - if a given neighbour was visited during this DFS.
 * @return Representative of a newly created/updated area.
 */
static elem_t* update_area(gamma_t* g, point_t start, size_t neighbours_num,
                           point_t neighbours[NEIGHBOURS_COUNT],
                           bool visited[NEIGHBOURS_COUNT]) {
  elem_t* updated_area_rep = make_set(g->board[start.line][start.col],
                                      g->board[start.line][start.col]->player);
  g->top = 0;
  push(g, start);
  g->visited[start.line][start.col] = true;
  while (g->top != 0) {
    point_t current;
    pop(g, &current);

    updated_area_rep =
        unite(updated_area_rep,
              make_set(g->board[current.line][current.col],
                       g->board[current.line][current.col]->player));

    push_neighbours(g, current);
  }

  for (size_t i = 0; i < neighbours_num; ++i) {
    if (!visited[i])
      visited[i] = g->visited[neighbours[i].line][neighbours[i].col];
  }
  clear_visited(g, start);

  return updated_area_rep;
}

uint32_t make_areas(gamma_t* g, uint32_t player, point_t field,
                    elem_t* areas[NEIGHBOURS_COUNT]) {
  point_t neighbours[NEIGHBOURS_COUNT];
  size_t neighbours_num = find_neighbour_player(g, neighbours, field, player);
  bool visited[NEIGHBOURS_COUNT];
  for (size_t i = 0; i < neighbours_num; ++i) visited[i] = false;

  uint32_t areas_count = 0;
  for (size_t i = 0; i < neighbours_num; ++i) {
    if (!visited[i]) {
      areas[areas_count++] =
          update_area(g, neighbours[i], neighbours_num, neighbours, visited);
    }
  }
  return areas_count;
}
