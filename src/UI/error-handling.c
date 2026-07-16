/** @file
 * Implementation of @ref error-handling.h.
 *
 * @author Mykhailo Shevchenko <mykhailo.shev@gmail.com>
 * @copyright University of Warsaw
 * @date 17.05.2020
 */

#include "error-handling.h"

#include <stdio.h>

void printERR(unsigned long long line) {
  fprintf(stderr, "ERROR %llu\n", line);
}
