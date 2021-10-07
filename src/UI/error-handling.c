/** @file
 * Implementacja @ref error-handling.h.
 *
 * @author Mykhailo Shevchenko <ms420826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.05.2020
 */

#include "error-handling.h"
#include <stdio.h>

void printERR(unsigned long long line)
{
    fprintf(stderr, "ERROR %llu\n", line);
}
