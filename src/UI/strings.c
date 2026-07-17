#include "strings.h"

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int EQUAL = 0;
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

void cat_strings(char* dest, char* src, uint64_t start_point) {
  uint32_t i = start_point;
  int j = 0;
  bool null_not_found = src[0] != '\0';
  while (null_not_found) {
    dest[i++] = src[j++];
    null_not_found = src[j] != '\0';
  }
}

bool get_strings(int strings_count, char* strings[]) {
  int i = 0;

  while (i < strings_count) {
    strings[i] = strtok(NULL, WHITE_SPACE);
    i++;
  }

  return (i == strings_count) && (strtok(NULL, WHITE_SPACE) == NULL);
}

bool string_to_ul(char* string, unsigned long* dest) {
  if (string == NULL || dest == NULL) return false;
  *dest = strtoul(string, NULL, 10);

  size_t string_length = strlen(string);
  // TODO cast
  if (count_digits(*dest) != string_length) return false;

  char* converted = malloc((string_length + 1) * sizeof *converted);
  if (converted == NULL) {
    errno = ENOMEM;
    return false;
  }
  sprintf(converted, "%lu", *dest);
  bool ans = strcmp(converted, string) == EQUAL;
  free(converted);

  return ans;
}

bool stringArr_to_ulArr(int strings_count, char* strings[],
                        unsigned long numbers[]) {
  bool ans = true;

  for (int i = 0; i < strings_count; ++i) {
    errno = 0;
    bool tmp = string_to_ul(strings[i], &(numbers[i]));
    if (errno == ENOMEM) return false;
    ans = ans ? tmp : ans;
  }

  return ans;
}

bool ul_to_uint32_t(unsigned long x, uint32_t* dest) {
  *dest = x;
  return x <= UINT32_MAX;
}

bool ulArr_to_uintArr(int size, unsigned long x[], uint32_t dest[]) {
  bool ans = true;

  for (int i = 0; i < size; ++i) {
    bool tmp = ul_to_uint32_t(x[i], &(dest[i]));
    ans = ans ? tmp : ans;
  }

  return ans;
}
