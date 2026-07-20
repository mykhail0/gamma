/** @file
 * Auxilary strings functions.
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 17.05.2020
 */

#ifndef STRINGS_H
#define STRINGS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/// Definition of white spaces.
extern const char WHITE_SPACE[7];

/** @brief Count number of digits in a given number.
 * @param[in] x - number whose digits need counting.
 * @return Number of digits in the given number.
 */
extern unsigned count_digits(uint32_t x);

/** @brief Collect string tokens and convert each one of them into uint32_t.
 * Before calling this function a `strtok` should be called. Fill @p numbers
 * with @p size `strtok` calls, each converted into uint32_t. Can fail. In that
 * case check errno for ENOMEM or ERANGE.
 * @param[in] size     - number of strings to convert,
 * @param[out] numbers - array to store conversions in.
 * @return @p true iff each string converted successfully.
 */
extern bool get_uints(size_t size, uint32_t numbers[]);

#endif /* STRINGS_H */
