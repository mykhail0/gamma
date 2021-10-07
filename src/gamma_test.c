#include <stdint.h>

#include <stdlib.h>

#include <assert.h>

#include <stdio.h>

#include "game_engine/gamma.h"



int main()

{

gamma_t *test = gamma_new(20, 40, 8, 4);

assert(1 == gamma_move(test, 1, 4, 28));

assert(1 == gamma_move(test, 8, 2, 10));

assert(0 == gamma_move(test, 9, 16, 3));

assert(1 == gamma_move(test, 5, 4, 35));

assert(1 == gamma_move(test, 5, 18, 10));

assert(1 == gamma_move(test, 5, 17, 1));

assert(1 == gamma_move(test, 1, 16, 3));

assert(1 == gamma_move(test, 8, 6, 32));

assert(1 == gamma_move(test, 1, 5, 31));

assert(0 == gamma_move(test, 9, 11, 8));

assert(0 == gamma_move(test, 9, 5, 18));

assert(1 == gamma_move(test, 1, 13, 12));

assert(1 == gamma_move(test, 7, 2, 23));

assert(0 == gamma_move(test, 7, 20, 39));

assert(1 == gamma_move(test, 2, 5, 39));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(1 == gamma_busy_fields(test, 2));

assert(789 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(0 == gamma_busy_fields(test, 3));

assert(789 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 1);
assert(0 == gamma_busy_fields(test, 4));

assert(789 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(3 == gamma_busy_fields(test, 5));

assert(789 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(0 == gamma_busy_fields(test, 6));

assert(789 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(1 == gamma_busy_fields(test, 7));

assert(789 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 1);
assert(2 == gamma_busy_fields(test, 8));

assert(789 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(1 == gamma_move(test, 8, 6, 8));

assert(0 == gamma_move(test, 6, 6, 40));

assert(0 == gamma_move(test, 0, 4, 31));

assert(1 == gamma_move(test, 5, 14, 14));

assert(0 == gamma_move(test, 1, 1, 35));

assert(0 == gamma_move(test, 0, 20, 35));

assert(1 == gamma_move(test, 2, 5, 19));

assert(0 == gamma_move(test, 0, 16, 16));

assert(1 == gamma_move(test, 8, 9, 33));

assert(1 == gamma_move(test, 4, 11, 1));

assert(1 == gamma_move(test, 7, 14, 18));

assert(0 == gamma_move(test, 9, 0, 10));

assert(1 == gamma_move(test, 6, 19, 10));

assert(0 == gamma_move(test, 9, 8, 26));

assert(0 == gamma_move(test, 9, 17, 23));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(2 == gamma_busy_fields(test, 2));

assert(782 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(0 == gamma_busy_fields(test, 3));

assert(782 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 1);
assert(1 == gamma_busy_fields(test, 4));

assert(782 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(1 == gamma_busy_fields(test, 6));

assert(782 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(2 == gamma_busy_fields(test, 7));

assert(782 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 1);
assert(4 == gamma_busy_fields(test, 8));

assert(16 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 0);


assert(1 == gamma_move(test, 4, 13, 1));

assert(0 == gamma_move(test, 3, 20, 29));

assert(0 == gamma_move(test, 6, 0, 40));

assert(0 == gamma_move(test, 5, 7, 34));

assert(1 == gamma_move(test, 6, 5, 9));

assert(1 == gamma_move(test, 6, 8, 16));

assert(0 == gamma_move(test, 0, 16, 16));

assert(0 == gamma_move(test, 8, 0, 15));

assert(1 == gamma_move(test, 4, 5, 2));

assert(1 == gamma_move(test, 3, 17, 14));

assert(0 == gamma_move(test, 8, 5, 15));

assert(0 == gamma_move(test, 8, 12, 29));

assert(1 == gamma_move(test, 6, 11, 24));

assert(1 == gamma_move(test, 3, 2, 25));

assert(0 == gamma_move(test, 5, 4, 29));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(2 == gamma_busy_fields(test, 2));

assert(775 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(2 == gamma_busy_fields(test, 3));

assert(775 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 1);
assert(3 == gamma_busy_fields(test, 4));

assert(775 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(4 == gamma_busy_fields(test, 6));

assert(14 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(2 == gamma_busy_fields(test, 7));

assert(775 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 1);
assert(4 == gamma_busy_fields(test, 8));

assert(16 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 0);


assert(0 == gamma_move(test, 7, 20, 1));

assert(0 == gamma_move(test, 8, 16, 25));

assert(1 == gamma_move(test, 4, 16, 26));

assert(0 == gamma_move(test, 5, 1, 35));

assert(0 == gamma_move(test, 9, 7, 22));

assert(0 == gamma_move(test, 9, 12, 24));

assert(0 == gamma_move(test, 6, 12, 36));

assert(1 == gamma_move(test, 3, 14, 38));

assert(1 == gamma_move(test, 2, 11, 2));

assert(1 == gamma_move(test, 3, 12, 7));

assert(0 == gamma_move(test, 1, 5, 11));

assert(0 == gamma_move(test, 9, 4, 35));

assert(0 == gamma_move(test, 4, 11, 11));

assert(0 == gamma_move(test, 9, 1, 30));

assert(0 == gamma_move(test, 8, 2, 37));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(3 == gamma_busy_fields(test, 2));

assert(771 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(4 == gamma_busy_fields(test, 4));

assert(14 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(4 == gamma_busy_fields(test, 6));

assert(14 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(2 == gamma_busy_fields(test, 7));

assert(771 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 1);
assert(4 == gamma_busy_fields(test, 8));

assert(16 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 0);


assert(0 == gamma_move(test, 8, 9, 18));

assert(0 == gamma_move(test, 9, 14, 13));

assert(0 == gamma_move(test, 1, 17, 13));

assert(0 == gamma_move(test, 3, 14, 20));

assert(0 == gamma_move(test, 6, 16, 25));

assert(1 == gamma_move(test, 2, 4, 39));

assert(0 == gamma_move(test, 1, 8, 0));

assert(0 == gamma_move(test, 3, 0, 4));

assert(0 == gamma_move(test, 0, 0, 27));

assert(1 == gamma_move(test, 2, 13, 30));

assert(0 == gamma_move(test, 5, 14, 31));

assert(0 == gamma_move(test, 1, 5, 1));

assert(0 == gamma_move(test, 3, 20, 13));

assert(1 == gamma_move(test, 6, 6, 9));

assert(0 == gamma_move(test, 9, 5, 13));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(4 == gamma_busy_fields(test, 4));

assert(14 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(2 == gamma_busy_fields(test, 7));

assert(768 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 1);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 2, 0, 19));

assert(0 == gamma_move(test, 2, 11, 26));

assert(0 == gamma_move(test, 8, 11, 21));

assert(0 == gamma_move(test, 2, 16, 29));

assert(0 == gamma_move(test, 5, 5, 9));

assert(0 == gamma_move(test, 5, 6, 20));

assert(0 == gamma_move(test, 4, 12, 6));

assert(0 == gamma_move(test, 2, 9, 5));

assert(0 == gamma_move(test, 0, 12, 16));

assert(0 == gamma_move(test, 6, 9, 39));

assert(0 == gamma_move(test, 1, 12, 3));

assert(0 == gamma_move(test, 2, 7, 0));

assert(0 == gamma_move(test, 5, 14, 23));

assert(0 == gamma_move(test, 8, 5, 5));

assert(0 == gamma_move(test, 1, 19, 19));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(4 == gamma_busy_fields(test, 4));

assert(14 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(2 == gamma_busy_fields(test, 7));

assert(768 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 1);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 6, 19, 17));

assert(0 == gamma_move(test, 6, 12, 21));

assert(0 == gamma_move(test, 6, 10, 1));

assert(0 == gamma_move(test, 3, 9, 17));

assert(0 == gamma_move(test, 4, 1, 7));

assert(0 == gamma_move(test, 7, 20, 36));

assert(0 == gamma_move(test, 2, 5, 21));

assert(0 == gamma_move(test, 2, 7, 8));

assert(0 == gamma_move(test, 3, 1, 40));

assert(1 == gamma_move(test, 7, 11, 21));

assert(0 == gamma_move(test, 4, 3, 26));

assert(0 == gamma_move(test, 2, 14, 4));

assert(0 == gamma_move(test, 4, 5, 38));

assert(0 == gamma_move(test, 3, 18, 18));

assert(1 == gamma_move(test, 7, 15, 37));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(4 == gamma_busy_fields(test, 4));

assert(14 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 6, 0, 30));

assert(0 == gamma_move(test, 5, 15, 15));

assert(0 == gamma_move(test, 8, 5, 21));

assert(0 == gamma_move(test, 1, 2, 30));

assert(0 == gamma_move(test, 0, 1, 29));

assert(0 == gamma_move(test, 7, 6, 29));

assert(0 == gamma_move(test, 1, 2, 11));

assert(0 == gamma_move(test, 7, 3, 21));

assert(0 == gamma_move(test, 3, 11, 26));

assert(0 == gamma_move(test, 5, 19, 3));

assert(0 == gamma_move(test, 7, 12, 34));

assert(0 == gamma_move(test, 2, 6, 37));

assert(0 == gamma_move(test, 2, 2, 16));

assert(0 == gamma_move(test, 5, 16, 37));

assert(0 == gamma_move(test, 2, 7, 24));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(4 == gamma_busy_fields(test, 4));

assert(14 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 2, 18, 35));

assert(0 == gamma_move(test, 4, 2, 11));

assert(0 == gamma_move(test, 4, 15, 13));

assert(0 == gamma_move(test, 0, 4, 4));

assert(0 == gamma_move(test, 6, 19, 40));

assert(0 == gamma_move(test, 5, 20, 13));

assert(0 == gamma_move(test, 7, 2, 35));

assert(0 == gamma_move(test, 2, 12, 8));

assert(0 == gamma_move(test, 9, 18, 24));

assert(0 == gamma_move(test, 9, 16, 0));

assert(0 == gamma_move(test, 2, 17, 40));

assert(0 == gamma_move(test, 1, 20, 10));

assert(0 == gamma_move(test, 1, 1, 35));

assert(0 == gamma_move(test, 6, 3, 30));

assert(0 == gamma_move(test, 1, 0, 17));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(4 == gamma_busy_fields(test, 4));

assert(14 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 4, 8, 35));

assert(0 == gamma_move(test, 3, 5, 33));

assert(0 == gamma_move(test, 4, 2, 27));

assert(0 == gamma_move(test, 3, 8, 0));

assert(0 == gamma_move(test, 6, 19, 23));

assert(0 == gamma_move(test, 1, 15, 2));

assert(0 == gamma_move(test, 8, 4, 7));

assert(0 == gamma_move(test, 9, 7, 9));

assert(0 == gamma_move(test, 3, 4, 31));

assert(0 == gamma_move(test, 5, 4, 16));

assert(0 == gamma_move(test, 8, 8, 13));

assert(0 == gamma_move(test, 5, 4, 13));

assert(0 == gamma_move(test, 6, 17, 14));

assert(0 == gamma_move(test, 3, 9, 34));

assert(0 == gamma_move(test, 5, 16, 29));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(4 == gamma_busy_fields(test, 4));

assert(14 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 4, 19, 27));

assert(0 == gamma_move(test, 5, 0, 17));

assert(0 == gamma_move(test, 7, 0, 18));

assert(0 == gamma_move(test, 0, 12, 0));

assert(0 == gamma_move(test, 6, 0, 10));

assert(0 == gamma_move(test, 1, 3, 9));

assert(0 == gamma_move(test, 0, 18, 6));

assert(0 == gamma_move(test, 8, 2, 1));

assert(1 == gamma_move(test, 4, 13, 2));

assert(0 == gamma_move(test, 4, 0, 33));

assert(0 == gamma_move(test, 1, 4, 14));

assert(0 == gamma_move(test, 7, 13, 29));

assert(0 == gamma_move(test, 6, 7, 3));

assert(0 == gamma_move(test, 5, 12, 18));

assert(0 == gamma_move(test, 5, 3, 18));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 5, 3, 28));

assert(0 == gamma_move(test, 0, 16, 0));

assert(0 == gamma_move(test, 6, 7, 8));

assert(0 == gamma_move(test, 7, 18, 2));

assert(0 == gamma_move(test, 6, 13, 21));

assert(0 == gamma_move(test, 2, 11, 7));

assert(0 == gamma_move(test, 5, 5, 3));

assert(0 == gamma_move(test, 5, 20, 18));

assert(0 == gamma_move(test, 1, 0, 19));

assert(0 == gamma_move(test, 8, 9, 0));

assert(0 == gamma_move(test, 2, 10, 19));

assert(0 == gamma_move(test, 1, 11, 7));

assert(0 == gamma_move(test, 5, 13, 19));

assert(0 == gamma_move(test, 7, 13, 28));

assert(0 == gamma_move(test, 4, 20, 33));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 3, 5, 21));

assert(0 == gamma_move(test, 1, 10, 19));

assert(0 == gamma_move(test, 2, 10, 7));

assert(0 == gamma_move(test, 6, 7, 40));

assert(0 == gamma_move(test, 5, 9, 3));

assert(0 == gamma_move(test, 7, 19, 25));

assert(0 == gamma_move(test, 4, 12, 36));

assert(0 == gamma_move(test, 7, 12, 2));

assert(0 == gamma_move(test, 6, 14, 6));

assert(0 == gamma_move(test, 4, 14, 13));

assert(0 == gamma_move(test, 9, 10, 17));

assert(0 == gamma_move(test, 9, 6, 30));

assert(0 == gamma_move(test, 4, 11, 1));

assert(0 == gamma_move(test, 0, 13, 17));

assert(0 == gamma_move(test, 4, 3, 14));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 2, 2, 13));

assert(0 == gamma_move(test, 0, 12, 1));

assert(0 == gamma_move(test, 8, 6, 20));

assert(0 == gamma_move(test, 6, 16, 2));

assert(0 == gamma_move(test, 1, 14, 26));

assert(0 == gamma_move(test, 0, 13, 34));

assert(0 == gamma_move(test, 9, 20, 33));

assert(0 == gamma_move(test, 8, 2, 26));

assert(0 == gamma_move(test, 8, 15, 31));

assert(0 == gamma_move(test, 7, 20, 30));

assert(0 == gamma_move(test, 7, 0, 20));

assert(0 == gamma_move(test, 1, 8, 25));

assert(0 == gamma_move(test, 1, 13, 9));

assert(0 == gamma_move(test, 4, 3, 34));

assert(0 == gamma_move(test, 8, 14, 5));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 6, 20, 40));

assert(0 == gamma_move(test, 7, 5, 37));

assert(0 == gamma_move(test, 9, 18, 14));

assert(0 == gamma_move(test, 0, 9, 25));

assert(0 == gamma_move(test, 3, 4, 25));

assert(0 == gamma_move(test, 4, 12, 18));

assert(0 == gamma_move(test, 4, 10, 35));

assert(0 == gamma_move(test, 5, 8, 26));

assert(0 == gamma_move(test, 6, 18, 38));

assert(0 == gamma_move(test, 1, 11, 38));

assert(0 == gamma_move(test, 0, 2, 39));

assert(0 == gamma_move(test, 3, 20, 20));

assert(0 == gamma_move(test, 5, 8, 11));

assert(0 == gamma_move(test, 9, 19, 15));

assert(0 == gamma_move(test, 1, 4, 9));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 9, 7, 8));

assert(0 == gamma_move(test, 5, 7, 25));

assert(0 == gamma_move(test, 9, 14, 22));

assert(0 == gamma_move(test, 3, 15, 18));

assert(0 == gamma_move(test, 1, 20, 20));

assert(0 == gamma_move(test, 7, 5, 9));

assert(0 == gamma_move(test, 4, 20, 25));

assert(0 == gamma_move(test, 9, 3, 17));

assert(0 == gamma_move(test, 2, 18, 12));

assert(0 == gamma_move(test, 5, 16, 4));

assert(0 == gamma_move(test, 5, 17, 19));

assert(0 == gamma_move(test, 0, 15, 1));

assert(0 == gamma_move(test, 4, 3, 14));

assert(0 == gamma_move(test, 1, 9, 30));

assert(0 == gamma_move(test, 5, 19, 1));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 6, 20, 15));

assert(0 == gamma_move(test, 2, 13, 33));

assert(0 == gamma_move(test, 8, 1, 8));

assert(0 == gamma_move(test, 9, 1, 0));

assert(0 == gamma_move(test, 1, 20, 30));

assert(0 == gamma_move(test, 9, 3, 5));

assert(0 == gamma_move(test, 9, 0, 25));

assert(0 == gamma_move(test, 9, 0, 3));

assert(0 == gamma_move(test, 0, 11, 4));

assert(0 == gamma_move(test, 2, 9, 28));

assert(0 == gamma_move(test, 7, 1, 35));

assert(0 == gamma_move(test, 5, 10, 18));

assert(0 == gamma_move(test, 2, 14, 1));

assert(0 == gamma_move(test, 3, 18, 38));

assert(0 == gamma_move(test, 8, 0, 20));

assert(4 == gamma_busy_fields(test, 1));

assert(16 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 0);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(15 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 1, 4, 39));

assert(0 == gamma_move(test, 1, 15, 25));

assert(0 == gamma_move(test, 3, 19, 3));

assert(0 == gamma_move(test, 9, 8, 36));

assert(0 == gamma_move(test, 3, 16, 23));

assert(0 == gamma_move(test, 8, 1, 23));

assert(0 == gamma_move(test, 5, 8, 8));

assert(0 == gamma_move(test, 5, 14, 40));

assert(0 == gamma_move(test, 9, 2, 21));

assert(0 == gamma_move(test, 0, 11, 0));

assert(0 == gamma_move(test, 6, 12, 27));

assert(0 == gamma_move(test, 2, 20, 36));

assert(0 == gamma_move(test, 9, 12, 32));

assert(1 == gamma_move(test, 1, 6, 31));

assert(0 == gamma_move(test, 4, 17, 19));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 3, 16, 0));

assert(0 == gamma_move(test, 5, 5, 32));

assert(0 == gamma_move(test, 4, 16, 24));

assert(0 == gamma_move(test, 7, 8, 29));

assert(0 == gamma_move(test, 5, 0, 3));

assert(0 == gamma_move(test, 0, 15, 23));

assert(0 == gamma_move(test, 3, 12, 11));

assert(0 == gamma_move(test, 5, 12, 36));

assert(0 == gamma_move(test, 3, 15, 17));

assert(0 == gamma_move(test, 9, 10, 1));

assert(0 == gamma_move(test, 7, 7, 19));

assert(0 == gamma_move(test, 5, 1, 24));

assert(0 == gamma_move(test, 5, 8, 36));

assert(0 == gamma_move(test, 3, 14, 16));

assert(0 == gamma_move(test, 4, 20, 3));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 4, 2, 21));

assert(0 == gamma_move(test, 0, 6, 25));

assert(0 == gamma_move(test, 1, 6, 1));

assert(0 == gamma_move(test, 3, 18, 39));

assert(0 == gamma_move(test, 6, 6, 9));

assert(0 == gamma_move(test, 2, 13, 20));

assert(0 == gamma_move(test, 5, 12, 14));

assert(0 == gamma_move(test, 7, 12, 0));

assert(0 == gamma_move(test, 7, 4, 19));

assert(0 == gamma_move(test, 2, 11, 10));

assert(0 == gamma_move(test, 4, 1, 20));

assert(0 == gamma_move(test, 1, 9, 29));

assert(0 == gamma_move(test, 6, 6, 38));

assert(0 == gamma_move(test, 9, 10, 38));

assert(0 == gamma_move(test, 5, 3, 20));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 4, 1, 4));

assert(0 == gamma_move(test, 3, 20, 30));

assert(0 == gamma_move(test, 1, 2, 11));

assert(0 == gamma_move(test, 8, 3, 12));

assert(0 == gamma_move(test, 6, 6, 21));

assert(0 == gamma_move(test, 9, 15, 2));

assert(0 == gamma_move(test, 1, 20, 20));

assert(0 == gamma_move(test, 5, 14, 4));

assert(0 == gamma_move(test, 8, 6, 32));

assert(0 == gamma_move(test, 1, 11, 0));

assert(0 == gamma_move(test, 7, 19, 32));

assert(0 == gamma_move(test, 5, 12, 24));

assert(0 == gamma_move(test, 0, 15, 5));

assert(0 == gamma_move(test, 7, 9, 10));

assert(0 == gamma_move(test, 6, 12, 14));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 6, 0, 25));

assert(0 == gamma_move(test, 8, 15, 19));

assert(0 == gamma_move(test, 8, 3, 24));

assert(0 == gamma_move(test, 3, 7, 1));

assert(0 == gamma_move(test, 2, 3, 28));

assert(0 == gamma_move(test, 5, 20, 38));

assert(0 == gamma_move(test, 4, 2, 7));

assert(0 == gamma_move(test, 4, 5, 33));

assert(0 == gamma_move(test, 8, 18, 35));

assert(0 == gamma_move(test, 0, 1, 32));

assert(0 == gamma_move(test, 7, 6, 37));

assert(0 == gamma_move(test, 9, 12, 31));

assert(0 == gamma_move(test, 3, 7, 1));

assert(0 == gamma_move(test, 3, 18, 27));

assert(0 == gamma_move(test, 1, 10, 26));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 3, 9, 21));

assert(0 == gamma_move(test, 6, 13, 16));

assert(0 == gamma_move(test, 1, 0, 40));

assert(0 == gamma_move(test, 3, 12, 26));

assert(0 == gamma_move(test, 1, 8, 26));

assert(0 == gamma_move(test, 1, 15, 24));

assert(0 == gamma_move(test, 3, 6, 20));

assert(0 == gamma_move(test, 0, 19, 36));

assert(0 == gamma_move(test, 9, 7, 38));

assert(0 == gamma_move(test, 7, 12, 16));

assert(0 == gamma_move(test, 4, 9, 15));

assert(0 == gamma_move(test, 5, 11, 28));

assert(0 == gamma_move(test, 3, 11, 35));

assert(0 == gamma_move(test, 9, 0, 3));

assert(0 == gamma_move(test, 3, 11, 26));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 1, 11, 38));

assert(0 == gamma_move(test, 1, 17, 22));

assert(0 == gamma_move(test, 9, 8, 38));

assert(0 == gamma_move(test, 8, 0, 33));

assert(0 == gamma_move(test, 7, 4, 6));

assert(0 == gamma_move(test, 6, 20, 27));

assert(0 == gamma_move(test, 0, 3, 13));

assert(0 == gamma_move(test, 1, 18, 10));

assert(0 == gamma_move(test, 9, 7, 12));

assert(0 == gamma_move(test, 3, 7, 13));

assert(0 == gamma_move(test, 2, 0, 8));

assert(0 == gamma_move(test, 6, 8, 35));

assert(0 == gamma_move(test, 6, 3, 3));

assert(0 == gamma_move(test, 7, 14, 34));

assert(0 == gamma_move(test, 9, 13, 37));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 9, 11, 38));

assert(0 == gamma_move(test, 9, 16, 18));

assert(0 == gamma_move(test, 7, 20, 39));

assert(0 == gamma_move(test, 5, 2, 14));

assert(0 == gamma_move(test, 4, 14, 16));

assert(0 == gamma_move(test, 9, 3, 31));

assert(0 == gamma_move(test, 9, 1, 0));

assert(0 == gamma_move(test, 1, 16, 27));

assert(0 == gamma_move(test, 8, 20, 29));

assert(0 == gamma_move(test, 8, 0, 1));

assert(0 == gamma_move(test, 8, 9, 4));

assert(0 == gamma_move(test, 5, 14, 14));

assert(0 == gamma_move(test, 5, 3, 17));

assert(0 == gamma_move(test, 1, 7, 12));

assert(0 == gamma_move(test, 7, 5, 0));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 4, 9, 11));

assert(0 == gamma_move(test, 7, 3, 1));

assert(0 == gamma_move(test, 4, 9, 35));

assert(0 == gamma_move(test, 7, 10, 29));

assert(0 == gamma_move(test, 6, 5, 17));

assert(0 == gamma_move(test, 8, 19, 5));

assert(0 == gamma_move(test, 1, 8, 24));

assert(0 == gamma_move(test, 7, 13, 6));

assert(0 == gamma_move(test, 7, 14, 0));

assert(0 == gamma_move(test, 5, 15, 21));

assert(0 == gamma_move(test, 1, 3, 1));

assert(0 == gamma_move(test, 7, 18, 32));

assert(0 == gamma_move(test, 6, 5, 28));

assert(0 == gamma_move(test, 4, 9, 30));

assert(0 == gamma_move(test, 6, 2, 38));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 5, 17, 3));

assert(0 == gamma_move(test, 9, 20, 10));

assert(0 == gamma_move(test, 0, 2, 34));

assert(0 == gamma_move(test, 9, 8, 36));

assert(0 == gamma_move(test, 6, 13, 27));

assert(0 == gamma_move(test, 9, 14, 27));

assert(0 == gamma_move(test, 1, 12, 25));

assert(0 == gamma_move(test, 8, 9, 23));

assert(0 == gamma_move(test, 6, 18, 8));

assert(0 == gamma_move(test, 3, 19, 13));

assert(0 == gamma_move(test, 9, 6, 34));

assert(0 == gamma_move(test, 3, 13, 39));

assert(0 == gamma_move(test, 0, 7, 40));

assert(0 == gamma_move(test, 4, 12, 16));

assert(0 == gamma_move(test, 9, 15, 24));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 4, 19, 20));

assert(0 == gamma_move(test, 7, 15, 19));

assert(0 == gamma_move(test, 2, 20, 21));

assert(0 == gamma_move(test, 5, 6, 26));

assert(0 == gamma_move(test, 6, 0, 21));

assert(0 == gamma_move(test, 1, 5, 23));

assert(0 == gamma_move(test, 0, 0, 38));

assert(0 == gamma_move(test, 5, 10, 13));

assert(0 == gamma_move(test, 4, 9, 32));

assert(0 == gamma_move(test, 8, 8, 19));

assert(0 == gamma_move(test, 0, 3, 32));

assert(0 == gamma_move(test, 2, 16, 33));

assert(0 == gamma_move(test, 4, 3, 19));

assert(0 == gamma_move(test, 4, 9, 12));

assert(0 == gamma_move(test, 6, 2, 5));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 7, 2, 40));

assert(0 == gamma_move(test, 5, 11, 37));

assert(0 == gamma_move(test, 9, 20, 7));

assert(0 == gamma_move(test, 1, 14, 30));

assert(0 == gamma_move(test, 3, 1, 17));

assert(0 == gamma_move(test, 3, 8, 38));

assert(0 == gamma_move(test, 7, 13, 40));

assert(0 == gamma_move(test, 0, 1, 5));

assert(0 == gamma_move(test, 8, 4, 1));

assert(0 == gamma_move(test, 1, 16, 38));

assert(0 == gamma_move(test, 0, 13, 6));

assert(0 == gamma_move(test, 8, 0, 20));

assert(0 == gamma_move(test, 0, 13, 39));

assert(0 == gamma_move(test, 4, 13, 23));

assert(0 == gamma_move(test, 8, 14, 30));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 1, 10, 2));

assert(0 == gamma_move(test, 0, 19, 4));

assert(0 == gamma_move(test, 3, 12, 10));

assert(0 == gamma_move(test, 0, 10, 6));

assert(0 == gamma_move(test, 0, 17, 17));

assert(0 == gamma_move(test, 8, 13, 24));

assert(0 == gamma_move(test, 8, 20, 9));

assert(0 == gamma_move(test, 0, 19, 14));

assert(0 == gamma_move(test, 2, 18, 9));

assert(0 == gamma_move(test, 8, 3, 30));

assert(0 == gamma_move(test, 1, 3, 11));

assert(0 == gamma_move(test, 0, 19, 29));

assert(0 == gamma_move(test, 5, 5, 34));

assert(0 == gamma_move(test, 7, 7, 7));

assert(0 == gamma_move(test, 6, 11, 1));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 0, 18, 25));

assert(0 == gamma_move(test, 6, 7, 36));

assert(0 == gamma_move(test, 3, 12, 31));

assert(0 == gamma_move(test, 8, 10, 17));

assert(0 == gamma_move(test, 5, 14, 29));

assert(0 == gamma_move(test, 0, 4, 39));

assert(0 == gamma_move(test, 6, 10, 10));

assert(0 == gamma_move(test, 1, 19, 20));

assert(0 == gamma_move(test, 3, 15, 35));

assert(0 == gamma_move(test, 6, 2, 15));

assert(0 == gamma_move(test, 7, 13, 2));

assert(0 == gamma_move(test, 0, 17, 39));

assert(0 == gamma_move(test, 5, 14, 27));

assert(0 == gamma_move(test, 5, 17, 6));

assert(0 == gamma_move(test, 3, 14, 3));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 1, 19, 6));

assert(0 == gamma_move(test, 0, 2, 21));

assert(0 == gamma_move(test, 4, 19, 11));

assert(0 == gamma_move(test, 2, 1, 30));

assert(0 == gamma_move(test, 9, 17, 1));

assert(0 == gamma_move(test, 2, 1, 25));

assert(0 == gamma_move(test, 3, 10, 4));

assert(0 == gamma_move(test, 9, 17, 27));

assert(0 == gamma_move(test, 8, 5, 27));

assert(0 == gamma_move(test, 7, 6, 17));

assert(0 == gamma_move(test, 5, 6, 29));

assert(0 == gamma_move(test, 3, 4, 32));

assert(0 == gamma_move(test, 1, 19, 15));

assert(0 == gamma_move(test, 0, 16, 16));

assert(0 == gamma_move(test, 3, 0, 1));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 3, 1, 14));

assert(0 == gamma_move(test, 7, 18, 40));

assert(0 == gamma_move(test, 7, 17, 31));

assert(0 == gamma_move(test, 2, 7, 21));

assert(0 == gamma_move(test, 7, 0, 27));

assert(0 == gamma_move(test, 4, 9, 40));

assert(0 == gamma_move(test, 8, 17, 16));

assert(0 == gamma_move(test, 3, 10, 8));

assert(0 == gamma_move(test, 0, 11, 39));

assert(0 == gamma_move(test, 8, 9, 19));

assert(0 == gamma_move(test, 2, 8, 5));

assert(0 == gamma_move(test, 9, 18, 5));

assert(0 == gamma_move(test, 4, 14, 14));

assert(0 == gamma_move(test, 1, 12, 20));

assert(0 == gamma_move(test, 7, 4, 32));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 4, 6, 10));

assert(0 == gamma_move(test, 8, 12, 6));

assert(0 == gamma_move(test, 9, 3, 38));

assert(0 == gamma_move(test, 3, 17, 39));

assert(0 == gamma_move(test, 5, 11, 39));

assert(0 == gamma_move(test, 0, 1, 38));

assert(0 == gamma_move(test, 9, 10, 27));

assert(0 == gamma_move(test, 1, 4, 6));

assert(0 == gamma_move(test, 8, 1, 5));

assert(0 == gamma_move(test, 9, 2, 12));

assert(0 == gamma_move(test, 5, 14, 4));

assert(0 == gamma_move(test, 0, 20, 12));

assert(0 == gamma_move(test, 5, 3, 23));

assert(0 == gamma_move(test, 9, 4, 19));

assert(0 == gamma_move(test, 7, 17, 14));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 5, 20, 11));

assert(0 == gamma_move(test, 0, 12, 26));

assert(0 == gamma_move(test, 1, 13, 20));

assert(0 == gamma_move(test, 3, 15, 23));

assert(0 == gamma_move(test, 3, 2, 17));

assert(0 == gamma_move(test, 6, 16, 33));

assert(0 == gamma_move(test, 1, 2, 27));

assert(0 == gamma_move(test, 6, 14, 23));

assert(0 == gamma_move(test, 3, 5, 26));

assert(0 == gamma_move(test, 2, 0, 37));

assert(0 == gamma_move(test, 7, 12, 34));

assert(0 == gamma_move(test, 7, 3, 26));

assert(0 == gamma_move(test, 4, 12, 15));

assert(0 == gamma_move(test, 4, 12, 19));

assert(0 == gamma_move(test, 8, 12, 16));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 4, 17, 38));

assert(0 == gamma_move(test, 8, 12, 17));

assert(0 == gamma_move(test, 7, 9, 0));

assert(0 == gamma_move(test, 5, 10, 28));

assert(0 == gamma_move(test, 3, 6, 16));

assert(0 == gamma_move(test, 0, 10, 7));

assert(0 == gamma_move(test, 6, 3, 35));

assert(0 == gamma_move(test, 4, 14, 8));

assert(0 == gamma_move(test, 2, 3, 15));

assert(0 == gamma_move(test, 4, 13, 21));

assert(0 == gamma_move(test, 7, 3, 38));

assert(0 == gamma_move(test, 8, 5, 31));

assert(0 == gamma_move(test, 1, 20, 13));

assert(0 == gamma_move(test, 8, 5, 9));

assert(0 == gamma_move(test, 2, 8, 38));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 9, 2, 35));

assert(0 == gamma_move(test, 8, 9, 12));

assert(0 == gamma_move(test, 8, 17, 38));

assert(0 == gamma_move(test, 1, 19, 10));

assert(0 == gamma_move(test, 6, 6, 33));

assert(0 == gamma_move(test, 2, 1, 2));

assert(0 == gamma_move(test, 1, 19, 34));

assert(0 == gamma_move(test, 4, 20, 33));

assert(0 == gamma_move(test, 1, 17, 20));

assert(0 == gamma_move(test, 3, 12, 27));

assert(0 == gamma_move(test, 7, 7, 7));

assert(0 == gamma_move(test, 8, 12, 37));

assert(0 == gamma_move(test, 8, 10, 19));

assert(0 == gamma_move(test, 9, 12, 14));

assert(0 == gamma_move(test, 8, 7, 0));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 4, 7, 32));

assert(0 == gamma_move(test, 3, 8, 33));

assert(0 == gamma_move(test, 6, 20, 15));

assert(0 == gamma_move(test, 2, 11, 22));

assert(0 == gamma_move(test, 5, 12, 4));

assert(0 == gamma_move(test, 8, 5, 16));

assert(0 == gamma_move(test, 6, 3, 25));

assert(0 == gamma_move(test, 1, 5, 27));

assert(0 == gamma_move(test, 3, 4, 34));

assert(0 == gamma_move(test, 2, 4, 18));

assert(0 == gamma_move(test, 5, 15, 2));

assert(0 == gamma_move(test, 8, 19, 26));

assert(0 == gamma_move(test, 4, 19, 38));

assert(0 == gamma_move(test, 0, 18, 15));

assert(0 == gamma_move(test, 2, 14, 7));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 8, 18, 11));

assert(0 == gamma_move(test, 1, 7, 23));

assert(0 == gamma_move(test, 9, 13, 19));

assert(0 == gamma_move(test, 0, 7, 34));

assert(0 == gamma_move(test, 5, 10, 40));

assert(0 == gamma_move(test, 4, 1, 27));

assert(0 == gamma_move(test, 5, 4, 3));

assert(0 == gamma_move(test, 3, 19, 0));

assert(0 == gamma_move(test, 2, 20, 13));

assert(0 == gamma_move(test, 4, 3, 21));

assert(0 == gamma_move(test, 4, 20, 12));

assert(0 == gamma_move(test, 9, 18, 37));

assert(0 == gamma_move(test, 1, 4, 9));

assert(0 == gamma_move(test, 6, 11, 31));

assert(0 == gamma_move(test, 7, 6, 38));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


assert(0 == gamma_move(test, 2, 19, 28));

assert(0 == gamma_move(test, 5, 14, 36));

assert(0 == gamma_move(test, 8, 18, 15));

assert(0 == gamma_move(test, 0, 9, 19));

assert(0 == gamma_move(test, 5, 16, 33));

assert(0 == gamma_move(test, 8, 9, 18));

assert(0 == gamma_move(test, 7, 15, 35));

assert(0 == gamma_move(test, 2, 14, 25));

assert(0 == gamma_move(test, 3, 10, 20));

assert(0 == gamma_move(test, 6, 7, 12));

assert(0 == gamma_move(test, 7, 9, 19));

assert(0 == gamma_move(test, 1, 6, 4));

assert(0 == gamma_move(test, 5, 17, 37));

assert(0 == gamma_move(test, 7, 19, 32));

assert(0 == gamma_move(test, 6, 11, 7));

assert(5 == gamma_busy_fields(test, 1));

assert(17 == gamma_free_fields(test, 1));

assert(gamma_golden_possible(test, 1) == 1);
assert(5 == gamma_busy_fields(test, 2));

assert(15 == gamma_free_fields(test, 2));

assert(gamma_golden_possible(test, 2) == 1);
assert(4 == gamma_busy_fields(test, 3));

assert(16 == gamma_free_fields(test, 3));

assert(gamma_golden_possible(test, 3) == 0);
assert(5 == gamma_busy_fields(test, 4));

assert(16 == gamma_free_fields(test, 4));

assert(gamma_golden_possible(test, 4) == 1);
assert(4 == gamma_busy_fields(test, 5));

assert(15 == gamma_free_fields(test, 5));

assert(gamma_golden_possible(test, 5) == 1);
assert(5 == gamma_busy_fields(test, 6));

assert(15 == gamma_free_fields(test, 6));

assert(gamma_golden_possible(test, 6) == 1);
assert(4 == gamma_busy_fields(test, 7));

assert(16 == gamma_free_fields(test, 7));

assert(gamma_golden_possible(test, 7) == 0);
assert(4 == gamma_busy_fields(test, 8));

assert(14 == gamma_free_fields(test, 8));

assert(gamma_golden_possible(test, 8) == 1);


gamma_delete(test);

return 0;

}

