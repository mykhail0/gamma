/** @file
 * Obsługa trybu wsadowego.
 *
 * @author Mykhailo Shevchenko <ms420826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.05.2020
 */

#ifndef BATCH_MODE_H
#define BATCH_MODE_H

#include <stdint.h>
#include <stdbool.h>

/** @brief Puszcza tryb wsadowy dla zadanych parametrów.
 * @return `true` wtw gdy gra zostałą przeprowadzona.
 */
extern bool batch_mode(unsigned long long *line,
                       uint32_t width, uint32_t height,
                       uint32_t players, uint32_t areas);

#endif /* BATCH_MODE_H */
