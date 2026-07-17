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

static const int LINE = 0;
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

/** @brief Find neighbouring fields of a given field.
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

void set_neighbours(gamma_t* g, uint32_t player, uint32_t col, uint32_t line,
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

void unite_with_neighbours(gamma_t* g, elem_t* neighbours[NEIGHBOURS_COUNT],
                           elem_t* e) {
  elem_t* united = e;
  for (size_t i = 0; i < NEIGHBOURS_COUNT; ++i) {
    if (neighbours[i] != NULL) {
      --(g->areas[united->player - 1]);
      united = unite(united, neighbours[i]);
    }
  }

  // To compensate for subtractions of area count in the loop above.
  ++(g->areas[united->player - 1]);
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

/** @brief Dodaje element do stosu.
 * @param[in] g   - stan gry.
 * @param[in] top - wskaźnik na indeks pierwszego pustego miejsca na stosie.
 * @param[in] x   - w `x[LINE]` jest `line` jak w innych funkcjach,
 *                  w `x[COL]` jest `col` jak w innych funkcjach.
 */
static void push(gamma_t* g, uint64_t* top, uint32_t x[COORDS_COUNT]) {
  for (int i = 0; i < COORDS_COUNT; ++i) g->stack[*top][i] = x[i];
  ++(*top);
}

/** @brief Zdejmuje element ze stosu.
 * @param[in] g   - stan gry.
 * @param[in] top - wskaźnik na indeks pierwszego pustego miejsca na stosie.
 * @param[in] x   - w `x[LINE]` jest `line` jak w innych funkcjach,
 *                  w `x[COL]` jest `col` jak w innych funkcjach.
 */
static void pop(gamma_t* g, uint64_t* top, uint32_t x[COORDS_COUNT]) {
  --(*top);
  for (int i = 0; i < COORDS_COUNT; ++i) x[i] = g->stack[*top][i];
}

/** @brief Dodaje niezwiedzonych sąsiadów do stosu.
 * Dodaje niezwiedzonych sąsiadów `x` do stosu
 * takich, że pionek stojący na sąsiedzie jest taki sam jak na `x`.
 * @param[in] g   - stan gry.
 * @param[in] top - wskaźnik na indeks pierwszego pustego miejsca na stosie.
 * @param[in] x   - w `x[LINE]` jest `line` jak w innych funkcjach,
 *                  w `x[COL]` jest `col` jak w innych funkcjach.
 */
static void push_neighbours(gamma_t* g, uint64_t* top,
                            uint32_t x[COORDS_COUNT]) {
  uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT];
  size_t neighbours_num = find_neighbours(g, neighbours, x);

  for (size_t i = 0; i < neighbours_num; ++i) {
    if (!(g->visited[neighbours[i][LINE]][neighbours[i][COL]]) &&
        g->board[neighbours[i][LINE]][neighbours[i][COL]]->player ==
            g->board[x[LINE]][x[COL]]->player) {
      g->visited[neighbours[i][LINE]][neighbours[i][COL]] = true;
      push(g, top, neighbours[i]);
    }
  }
}

/** @brief Sprawdza, czy komórka należy do tablicy `dest`.
 * (z poprawką na to że niektóre elementy `dest` nie mają znaczenia).
 * @param[in] x             - w `x[LINE]` jest `line` jak w innych funkcjach,
 *                            w `x[COL]` jest `col` jak w innych funkcjach.
 * @param[in] dest          - gdzie szukamy.
 * @param[in] legit_dest    - poprawka.
 * @param[out] dest_visited - wynik.
 */
static void check_dest(uint32_t x[COORDS_COUNT], size_t neighbours_num,
                       uint32_t dest[NEIGHBOURS_COUNT][COORDS_COUNT],
                       bool legit_dest[NEIGHBOURS_COUNT],
                       bool dest_visited[NEIGHBOURS_COUNT]) {
  for (size_t i = 0; i < neighbours_num; ++i) {
    if (legit_dest[i] && dest[i][LINE] == x[LINE] && dest[i][COL] == x[COL])

      dest_visited[i] = true;
  }
}

/** @brief Dodaje zwiedzonych sąsiadów `x` do stosu.
 * @param[in] g   - stan gry.
 * @param[in] top - wskaźnik na indeks pierwszego pustego miejsca na stosie.
 * @param[in] x   - w `x[LINE]` jest `line` jak w innych funkcjach,
 *                  w `x[COL]` jest `col` jak w innych funkcjach.
 */
static void push_neighbours_clear(gamma_t* g, uint64_t* top,
                                  uint32_t x[COORDS_COUNT]) {
  uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT];
  size_t neighbours_num = find_neighbours(g, neighbours, x);

  for (size_t i = 0; i < neighbours_num; ++i) {
    if (g->visited[neighbours[i][LINE]][neighbours[i][COL]]) {
      g->visited[neighbours[i][LINE]][neighbours[i][COL]] = false;
      push(g, top, neighbours[i]);
    }
  }
}

/** @brief Ustawia wszystkie zwiedzone komórki wokół `start` na niezwiedzone.
 * @param[in] g     - stan gry.
 * @param[in] start - współrzędne komórki startowej.
 */
static void clear_visited(gamma_t* g, uint32_t start[COORDS_COUNT]) {
  uint64_t top = 0;
  g->visited[start[LINE]][start[COL]] = false;
  push(g, &top, start);
  while (top != 0) {
    uint32_t current[COORDS_COUNT];
    pop(g, &top, current);
    push_neighbours_clear(g, &top, current);
  }
}

/** @brief Reorganizuje obszar.
 * DFS startuje z pola `start`.
 * W `dest_visited[i]` zapisuje czy pole `dest[i]` było zwiedzone.
 * (Jeśli `legit_dest[i]` jest ustawione na `true`).
 * @return reprezentanta obszaru, który powstał
 */
static elem_t* remake_subset(gamma_t* g, uint32_t start[COORDS_COUNT],
                             size_t neighbours_num,
                             uint32_t dest[NEIGHBOURS_COUNT][COORDS_COUNT],
                             bool legit_dest[NEIGHBOURS_COUNT],
                             bool dest_visited[NEIGHBOURS_COUNT]) {
  elem_t* new_area = make_set(g->board[start[LINE]][start[COL]],
                              g->board[start[LINE]][start[COL]]->player);
  uint64_t top = 0;
  push(g, &top, start);
  g->visited[start[LINE]][start[COL]] = true;
  while (top != 0) {
    uint32_t current[COORDS_COUNT];
    pop(g, &top, current);
    check_dest(current, neighbours_num, dest, legit_dest, dest_visited);

    new_area = unite(new_area,
                     make_set(g->board[current[LINE]][current[COL]],
                              g->board[current[LINE]][current[COL]]->player));

    push_neighbours(g, &top, current);
  }
  clear_visited(g, start);
  return new_area;
}

size_t make_subsets(gamma_t* g, uint32_t player, uint32_t col, uint32_t line,
                    elem_t* subsets[NEIGHBOURS_COUNT]) {
  uint32_t field[COORDS_COUNT], dest[NEIGHBOURS_COUNT][COORDS_COUNT];
  init_field(field, col, line);
  size_t neighbours_num = find_neighbours(g, dest, field), areas_count = 0;
  bool legit_dest[NEIGHBOURS_COUNT], dest_visited[NEIGHBOURS_COUNT];
  for (size_t i = 0; i < neighbours_num; ++i) {
    dest_visited[i] = false;
    legit_dest[i] = true;
  }

  for (size_t i = 0; i < neighbours_num; ++i) {
    if (g->board[dest[i][LINE]][dest[i][COL]]->player != player)
      legit_dest[i] = false;
  }

  for (int i = 0; i < NEIGHBOURS_COUNT; ++i) subsets[i] = NULL;
  for (size_t i = 0; i < neighbours_num; ++i) {
    if (legit_dest[i] && !dest_visited[i]) {
      subsets[i] = remake_subset(g, dest[i], neighbours_num, dest, legit_dest,
                                 dest_visited);

      ++areas_count;
    }
  }
  return areas_count;
}
