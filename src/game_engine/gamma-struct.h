/** @file
 * Game's state object.
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 17.04.2020
 */

#ifndef GAMMA_STRUCT_H
#define GAMMA_STRUCT_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#include "find-union.h"

/** @brief Board's dimensionality.
 */
#define COORDS_COUNT 2

/// Game's state.
struct gamma {
  /// board's width,
  uint32_t width;
  /// board's height,
  uint32_t height;
  /// maximum number of areas, which one player can possess,
  uint32_t areas_number;
  /// number of players,
  uint32_t players_number;
  /// number of free fields,
  uint64_t free_fields;
  /// for a given player, number of free fields adjacent to their fields,
  uint64_t* free_neighbours;
  /// for a given player, number of fields taken by them,
  uint64_t* busy_fields;
  /// for a given player, number of areas they have,
  uint32_t* areas;
  /// for a given player, information on whether they have used their golden
  /// move.
  bool* golden_not_used;

  /** Find-Union object to represent fields on the board and their ownership by
   * players.
   */
  elem_t*** board;
  /// Auxilary array for checking area changes during golden move DFS.
  bool** visited;
  /// Auxilary stack for checking area changes during golden move DFS.
  uint32_t (*stack)[COORDS_COUNT];
  /// Index of the first empty spot on the stack.
  size_t top;
};

/** @brief Game's state object.
 */
typedef struct gamma gamma_t;

#endif /* GAMMA_STRUCT_H */
