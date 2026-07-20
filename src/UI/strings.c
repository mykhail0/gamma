#include "strings.h"

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char WHITE_SPACE[7] = {' ', '\t', '\n', '\v', '\f', '\r', '\0'};

unsigned count_digits(uint32_t x) {
  unsigned digits = 0;
  if (x == 0) return 1;
  while (x != 0) {
    x /= 10;
    ++digits;
  }
  return digits;
}

/** @brief Convert a string to `unsigned long`.
 * Can fail. In that case check errno for ENOMEM or ERANGE.
 * @param[in] string - a null-terminated string to convert,
 * @param[out] dest  - pointer to value where result will be stored.
 * @return @p true iff converted successfully.
 */
static bool string_to_ul(char* string, unsigned long* dest) {
  // Try to convert.
  errno = 0;
  if (string == NULL || dest == NULL ||
      (ULONG_MAX == (*dest = strtoul(string, NULL, 10)) && errno == ERANGE))
    return false;

  // Check for success.
  size_t string_length = strlen(string);
  if (string_length != count_digits(*dest)) return false;
  char* converted = calloc(string_length + 1, sizeof *converted);
  if (converted == NULL) {
    return false;
  }

  int sprintf_ret = sprintf(converted, "%lu", *dest);
  assert(sprintf_ret >= 0);
  assert((size_t)sprintf_ret == string_length);
  bool success = strcmp(converted, string) == 0;
  free(converted);

  return success;
}

/** @brief Convert `unsigned long` to `uint32_t`.
 * @param[in] from  - number to convert,
 * @param[out] dest - pointer to value where result will be stored.
 * @return @p true iff converted successfully.
 */
static bool ul_to_uint32_t(unsigned long from, uint32_t* dest) {
  *dest = from;
  return from <= UINT32_MAX;
}

bool get_uints(size_t strings_count, uint32_t numbers[]) {
  bool success = true;
  for (size_t i = 0; success && i < strings_count; ++i) {
    char* s = strtok(NULL, WHITE_SPACE);
    unsigned long intermediate;
    success = string_to_ul(s, &intermediate) &&
              ul_to_uint32_t(intermediate, &(numbers[i]));
  }
  return success && strtok(NULL, WHITE_SPACE) == NULL;
}
