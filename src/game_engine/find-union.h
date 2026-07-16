/** @file
 * Find-Union data structure.
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 17.04.2020
 */

#ifndef FIND_UNION_H
#define FIND_UNION_H

#include <stdint.h>

/** A field on the board.
 */
struct elem {
  uint32_t player;  ///< a player's index, who owns the piece on this field,
  uint64_t rank;    ///< upper limit on height of the area's tree. Meaningful
                    /// only if parent is equal to the address of this field.

  /** Address of the field parental to this one.
   * If the address is equal to the address of this field then it is the root of
   * the area, which has id equal to this address.
   */
  struct elem* parent;
};

/** @brief Auxilary struct for the Find-Union data structure.
 * Represents a field on the board.
 */
typedef struct elem elem_t;

/** @brief Initialize an area.
 * Initialize area @p e as the root with @p player as the owner.
 * @param[in,out] e  - is not `NULL`,
 * @param[in] player - player's index, for whom this area is initialized.
 * @return Pointer to the initialized area.
 */
extern elem_t* make_set(elem_t* e, uint32_t player);

/** @brief Return the representative of the area which contains the field.
 * Return the representative of the area which contains the field @p e. Uses
 * path compression in the implementation.
 * @param[in] e - non-NULL field on the board.
 * @return The representative of the area which contains the given field.
 */
extern elem_t* find(elem_t* e);

/** @brief Merges two areas represented by given fields.
 * @param[in] x - representative of some area,
 * @param[in] y - representative of some area.
 * @return The representative of the united area.
 */
extern elem_t* unite(elem_t* x, elem_t* y);

#endif /* FIND_UNION_H */
