/** @file
 * Pomocnicze funkcje do @ref gamma_delete.
 *
 * @author Mykhailo Shevchenko <ms420826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 18.04.2020
 */

#ifndef GAMMA_DELETE_H
#define GAMMA_DELETE_H

#include "gamma-struct.h"
#include <stdint.h>

/** @brief Zwalnia pamięć po `g->visited`.
 */
void visited_delete(gamma_t *g);

/** @brief Zwalnia pamięć po 'g->board`.
 */
void board_delete(gamma_t *g);

#endif /* GAMMA_DELETE_H */
