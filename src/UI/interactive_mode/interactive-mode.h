/** @file
 * Obsługa trybu interaktywnego.
 *
 * @author Mykhailo Shevchenko <ms420826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.05.2020
 */

#ifndef INTERACTIVE_MODE_H
#define INTERACTIVE_MODE_H

#include <stdint.h>
#include <stdbool.h>

/** @brief Puszcza tryb interaktywny.
 * Jeśli został zwrócony `false` to errno informuje o błędzie.
 */
extern bool interactive_mode(uint32_t width, uint32_t height,
                             uint32_t players, uint32_t areas);

#endif /* INTERACTIVE_MODE_H */
