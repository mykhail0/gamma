/** @file
 * Auxilary functions for @ref gamma_move and @ref gamma_golden_move.
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 18.04.2020
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "find-union.h"
#include "gamma-struct.h"
#include "strings.h"

/** @brief Maximum number of neighbours for a field.
 */
#define NEIGHBOURS_COUNT 4

/** @brief Placeholder for a null player.
 */
extern const uint32_t NOPLAYER;

/** @brief Check correctness of a player's index.
 * @return @p false if the board is empty or @p player is out of bounds.
 */
bool player_is_ok(gamma_t* g, uint32_t player);

/** @brief Check correctness of a given field, given board's dimensions.
 * @return @p false if the field is out of bounds.
 */
bool coords_are_ok(gamma_t* g, field_t field);

/** @brief Check if the given field neighbours the player's area.
 * Assumes arguments are correct.
 * @param[in] g      - game's state,
 * @param[in] player - player's index,
 * @param[in] field  - field's coordinates.
 * @return @p true if the given field neighbours any piece of the @p player.
 */
bool exists_neighbour(gamma_t* g, uint32_t player, field_t field);

/** Find representatives of neighbouring fields belonging to the given player.
 * @param[in] g           - game's state,
 * @param[in] player      - player's index,
 * @param[in] field       - coordinates of a field of interest,
 * @param[out] neighbours - unique representatives of fields belonging to the
 *                          @p player, which neighbour field (@p col, @p line).
 * @return The number of elements in the array @p neighbours.
 */
size_t set_neighbours(gamma_t* g, uint32_t player, field_t field,
                      elem_t* neighbours[NEIGHBOURS_COUNT]);

/** @brief Checks where @ref gamma_move succeeds.
 * @param[in] g      - game's state,
 * @param[in] player - player's index,
 * @param[in] field  - coordinates of a field to move to.
 * @return @p true if the move is possible and @p false otherwise.
 */
bool gamma_move_possible(gamma_t* g, uint32_t player, field_t field);

/** @brief Update the number of free neighbours for every player.
 * Update the number of free neighbours for every player as if @p player
 * put/took off their piece on/from (@p col, @p line), when @p disappeared is
 * false/true respectively.
 * @param[in] g           - game's state,
 * @param[in] player      - index of a player who is moving into the given
 *                          field,
 * @param[in] col         - column of the given field,
 * @param[in] line        - line of the given field,
 * @param[in] disappeared - whether @p player put or took off their piece.
 */
void update_free_neighbours(gamma_t* g, uint32_t player, uint32_t col,
                            uint32_t line, bool disappeared);

/** @brief Update areas surrounding the deleted piece.
 * Auxilary function for @ref gamma_golden_move. After removing a piece of the
 * @p player from the field (@p col, @p line), update representatives of areas
 * surrounding the field and add them to @p subsets array.
 * @param[in] g      - game's state,
 * @param[in] player - index of a player, whose piece was removed,
 * @param[in] field  - field's coordinates,
 * @param[out] areas - representatives of surrounding areas.
 * @return The number of surrounding areas.
 */
uint32_t make_areas(gamma_t* g, uint32_t player, field_t field,
                    elem_t* areas[NEIGHBOURS_COUNT]);
