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

/// Constant for a result of `strcmp`.
extern const int EQUAL;

/// Definition of white spaces.
extern const char WHITE_SPACE[7];

/** @brief Count number of digits in a given number.
 * @param[in] x - number whose digits need counting.
 * @return Number of digits in the given number.
 */
extern unsigned count_digits(uint32_t x);

/** @brief Kopiuje napis `src` do `dest` zaczynając od indeksu o numerze
 * `start_point`.
 * '\0' na końcu `src` nie jest kopiowany.
 * @param[in] dest        - W `dest` powinno byc wystarczajaco miejsca,
 *                          zaczynając od `start_point`.
 * @param[in] src         - powinien być zakończony `'\0'` i nie może być
 * `NULL`.
 * @param[in] start_point - indeks, od którego zaczyna się kopiowanie.
 */
extern void cat_strings(char* dest, char* src, uint64_t start_point);

/** @brief Wypełnia tablicę `strings` `stings_count` słowami.
 * Wypełnia tablicę słowami.
 * Przed wywołaniem funkcji należy pobrać pierwszy token z napisu
 * (funkcja używa strtok(NULL, whiteSpaces).
 * @param[in] strings_count - liczba oczekiwanych napisów,
 * @param[in] strings       - tablica napisów, gdzie będzie
 *                            zapisany wynik.
 * @return `true` wtw gdy wczyta nie mniej i nie więcej niż `strings_count`
 * słow.
 */
extern bool get_strings(int strings_count, char* strings[]);

/** @brief Konwertuje napis na unsigned long.
 * Może się nie udać z powodu braku pamięci. Wtedy ustawia errno na ENOMEM.
 * @param[in] string - napis do konwersji,
 * @param[in] dest   - wskaźnik na zmienną, gdzie będzie zapisany wynik.
 * @return `true` wtw gdy konwersja się udała.
 */
extern bool string_to_ul(char* string, unsigned long* dest);

/** @brief Konwertuje tablicę napisów na tablicę unsigned long.
 * Zapisuje w tablicy wyniki konwersji.
 * Może się nie udać z powodu braku pamięci. Wtedy ustawia errno na ENOMEM.
 * @param[in] strings_count - rozmiar `strings`,
 * @param[in] strings       - tablica napisów,
 * @param[in] numbers       - tablica, gdzie będzie zapisany wynik.
 * @return `true` wtw gdy konwersja się uda dla każdego napisu.
 */
extern bool stringArr_to_ulArr(int strings_count, char* strings[],
                               unsigned long numbers[]);

/** @brief Konwertuje unsigned long na uint32_t.
 * @param[in] x    - liczba do konwersji,
 * @param[in] dest - wskaźnik na zmienną, gdzie będzie zapisany wynik.
 * @return `true` wtw gdy konwersja się uda.
 */
extern bool ul_to_uint32_t(unsigned long x, uint32_t* dest);

/** @brief Konwertuje tablicę unsigned long na tablicę uint32_t.
 * Zapisuje w tablicy wyniki konwersji.
 * @param[in] size - rozmiar `x`,
 * @param[in] x    - tablica liczb,
 * @param[in] dest - tablica, gdzie będzie zapisany wynik.
 * @return `true` wtw gdy konwersja się uda dla każdej liczby z tablicy.
 */
extern bool ulArr_to_uintArr(int size, unsigned long x[], uint32_t dest[]);

#endif /* STRINGS_H */
