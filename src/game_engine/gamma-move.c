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

/// Index of the line integer in a 2 element field array.
static const int LINE = 0;
/// Index of the column integer in a 2 element field array.
static const int COL = 1;

const uint32_t NOPLAYER = 0;

void init_field(uint32_t field[], uint32_t col, uint32_t line) {
  field[LINE] = line;
  field[COL] = col;
}

bool player_is_ok(gamma_t* g, uint32_t player) {
  return g != NULL && 0 < player && player <= g->players_number;
}

bool coords_are_ok(gamma_t* g, uint32_t col, uint32_t line) {
  assert(g != NULL);
  return col < g->width && line < g->height;
}

/** Differences between adjacent fields' coordinates.
 */
static const int32_t ADJACENT_DIFFS[NEIGHBOURS_COUNT][COORDS_COUNT] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

/** Check if the field moved by `ADJACENT_DIFFS[adj_i]` has correct coords.
 */
static bool move_is_valid(gamma_t* g, size_t adj_i,
                          uint32_t field[COORDS_COUNT]) {
  return (ADJACENT_DIFFS[adj_i][LINE] >= 0 || field[LINE] != 0) &&
         (ADJACENT_DIFFS[adj_i][COL] >= 0 || field[COL] != 0) &&
         coords_are_ok(g, ADJACENT_DIFFS[adj_i][COL] + field[COL],
                       ADJACENT_DIFFS[adj_i][LINE] + field[LINE]);
}

/** @brief Find fields neighbouring a given field.
 * @param[in] g           - game's state,
 * @param[out] neighbours - coordinates of the neighbours,
 * @param[in] field       - coordinates of the field whose neighbours we find.
 * @return The number of neighbours.
 */
static size_t find_neighbours(
    gamma_t* g, uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT],
    uint32_t field[COORDS_COUNT]) {
  size_t i = 0;
  for (size_t j = 0; j < NEIGHBOURS_COUNT; ++j) {
    if (move_is_valid(g, j, field)) {
      for (size_t k = 0; k < COORDS_COUNT; ++k)
        neighbours[i][k] = ADJACENT_DIFFS[j][k] + field[k];
      ++i;
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
static size_t find_neighbour_player(
    gamma_t* g, uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT],
    uint32_t field[COORDS_COUNT], uint32_t player) {
  size_t i = 0;
  for (size_t j = 0; j < NEIGHBOURS_COUNT; ++j) {
    if (move_is_valid(g, j, field)) {
      for (size_t k = 0; k < COORDS_COUNT; ++k)
        neighbours[i][k] = ADJACENT_DIFFS[j][k] + field[k];
      if (g->board[neighbours[i][LINE]][neighbours[i][COL]]->player == player)
        ++i;
    }
  }
  return i;
}

bool exists_neighbour(gamma_t* g, uint32_t player, uint32_t field[]) {
  bool exists = false;
  for (size_t j = 0; !exists && j < NEIGHBOURS_COUNT; ++j) {
    if (move_is_valid(g, j, field)) {
      exists = g->board[field[LINE] + ADJACENT_DIFFS[j][LINE]]
                       [field[COL] + ADJACENT_DIFFS[j][COL]]
                           ->player == player;
    }
  }
  return exists;
}

size_t set_neighbours(gamma_t* g, uint32_t player, uint32_t col, uint32_t line,
                      elem_t* neighbours[NEIGHBOURS_COUNT]) {
  for (size_t i = 0; i < NEIGHBOURS_COUNT; ++i) neighbours[i] = NULL;

  uint32_t field[COORDS_COUNT];
  init_field(field, col, line);
  size_t i = 0;
  for (size_t j = 0; j < NEIGHBOURS_COUNT; ++j) {
    if (move_is_valid(g, j, field)) {
      elem_t* neighbour = find(g->board[line + ADJACENT_DIFFS[j][LINE]]
                                       [col + ADJACENT_DIFFS[j][COL]]);
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

bool gamma_move_possible(gamma_t* g, uint32_t player, uint32_t col,
                         uint32_t line) {
  uint32_t field[COORDS_COUNT];
  init_field(field, col, line);
  return player_is_ok(g, player) && coords_are_ok(g, col, line) &&
         g->board[line][col]->player == NOPLAYER &&
         (g->areas[player - 1] < g->areas_number ||
          exists_neighbour(g, player, field));
}

void update_free_neighbours(gamma_t* g, uint32_t player, uint32_t col,
                            uint32_t line, bool disappeared) {
  uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT], field[COORDS_COUNT],
      player_encountered[NEIGHBOURS_COUNT];
  init_field(field, col, line);
  size_t neighbours_num = find_neighbours(g, neighbours, field);

  for (size_t i = 0; i < neighbours_num; ++i) {
    uint32_t p = g->board[neighbours[i][LINE]][neighbours[i][COL]]->player;
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
static void push(gamma_t* g, uint32_t x[COORDS_COUNT]) {
  for (size_t i = 0; i < COORDS_COUNT; ++i) g->stack[g->top][i] = x[i];
  ++(g->top);
}

/** @brief Pop a field off the stack.
 * @param[in] g - game's state,
 * @param[in] x - field's coordinates.
 */
static void pop(gamma_t* g, uint32_t x[COORDS_COUNT]) {
  --(g->top);
  for (size_t i = 0; i < COORDS_COUNT; ++i) x[i] = g->stack[g->top][i];
}

/** @brief Push not visited neighbours on the stack.
 * Push not visited neighbours of @p field such that belong to the same player
 * as on @p field on the stack.
 * @param[in] g     - game's state,
 * @param[in] field - field of interest.
 */
static void push_neighbours(gamma_t* g, uint32_t field[COORDS_COUNT]) {
  uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT];
  size_t neighbours_num = find_neighbour_player(
      g, neighbours, field, g->board[field[LINE]][field[COL]]->player);

  for (size_t i = 0; i < neighbours_num; ++i) {
    if (!g->visited[neighbours[i][LINE]][neighbours[i][COL]]) {
      g->visited[neighbours[i][LINE]][neighbours[i][COL]] = true;
      push(g, neighbours[i]);
    }
  }
}

/** @brief Add visited neighbours of @p field on the stack.
 * @param[in] g     - game's state,
 * @param[in] field - field of interest.
 */
static void push_neighbours_clear(gamma_t* g, uint32_t field[COORDS_COUNT]) {
  uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT];
  size_t neighbours_num = find_neighbours(g, neighbours, field);

  for (size_t i = 0; i < neighbours_num; ++i) {
    if (g->visited[neighbours[i][LINE]][neighbours[i][COL]]) {
      g->visited[neighbours[i][LINE]][neighbours[i][COL]] = false;
      push(g, neighbours[i]);
    }
  }
}

/** @brief Set all fields connected to @p start as not visited.
 * @param[in] g     - game's state,
 * @param[in] start - starting field's coordinates.
 */
static void clear_visited(gamma_t* g, uint32_t start[COORDS_COUNT]) {
  g->top = 0;
  g->visited[start[LINE]][start[COL]] = false;
  push(g, start);
  while (g->top != 0) {
    uint32_t current[COORDS_COUNT];
    pop(g, current);
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
static elem_t* update_area(gamma_t* g, uint32_t start[COORDS_COUNT],
                           size_t neighbours_num,
                           uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT],
                           bool visited[NEIGHBOURS_COUNT]) {
  elem_t* updated_area_rep =
      make_set(g->board[start[LINE]][start[COL]],
               g->board[start[LINE]][start[COL]]->player);
  g->top = 0;
  push(g, start);
  g->visited[start[LINE]][start[COL]] = true;
  while (g->top != 0) {
    uint32_t current[COORDS_COUNT];
    pop(g, current);

    updated_area_rep =
        unite(updated_area_rep,
              make_set(g->board[current[LINE]][current[COL]],
                       g->board[current[LINE]][current[COL]]->player));

    push_neighbours(g, current);
  }

  for (size_t i = 0; i < neighbours_num; ++i) {
    if (!visited[i])
      visited[i] = g->visited[neighbours[i][LINE]][neighbours[i][COL]];
  }
  clear_visited(g, start);

  return updated_area_rep;
}

uint32_t make_areas(gamma_t* g, uint32_t player, uint32_t col, uint32_t line,
                    elem_t* areas[NEIGHBOURS_COUNT]) {
  uint32_t areas_count = 0, neighbours[NEIGHBOURS_COUNT][COORDS_COUNT],
           field[COORDS_COUNT];
  init_field(field, col, line);
  size_t neighbours_num = find_neighbour_player(g, neighbours, field, player);
  bool visited[NEIGHBOURS_COUNT];
  for (size_t i = 0; i < neighbours_num; ++i) visited[i] = false;

  for (size_t i = 0; i < neighbours_num; ++i) {
    if (!visited[i]) {
      areas[areas_count++] =
          update_area(g, neighbours[i], neighbours_num, neighbours, visited);
    }
  }
  return areas_count;
}
