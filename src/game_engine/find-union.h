/** @file
 * Implementacja struktury Find-Union
 *
 * @author Mykhailo Shevchenko <ms420826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.04.2020
 */

#ifndef FIND_UNION_H
#define FIND_UNION_H

#include <stdint.h>

/** Komórka planszy
 */
struct elem {
    uint32_t player; ///< numer gracza, czyj pionek stoi na tym polu.
    uint64_t rank; ///< ogarniczenie górne wysokości drzewa obszaru. Ma znaczenie wtw parent jest adresem komórki.
/** adres komórki która jest nadrzędna do tej.
 * Jeśli komórka jest nadrzędna samej sobie
 * to jest korzeniem obszaru
 * o identyfikatorze równym adresie tej komórki.
 */
    struct elem *parent;
};

/** @brief Pomocniczy rekord do struktury danych "Find-Union".
 * Reprezentuje komórkę planszy.
 */
typedef struct elem elem_t;

/** @brief Inicjuje obszar.
 * Tworzy z `e` zbiór (obszar) z polem `player` o wartości `player`.
 * @param[in] e      - nie jest `NULL` i ma zaalokowane pole `parent`.
 * @param[in] player - numer gracza, dla którego jest tworzony ten obszar.
 */
extern elem_t *make_set(elem_t *e, uint32_t player);

/** @brief Zwraca reprezentanta zbioru do którego należy `e`.
 * @param[in] e - pole planszy, nie jest `NULL`.
 *                Dodatkowo kompresuje ścieżkę.
 */
extern elem_t* find(elem_t *e);

/** @brief Łączy dwa zbiory, których reprezentantami są `x` i `y`.
 * @param[in] x - reprezentant pewnego obszaru.
 * @param[in] y - reprezentant pewnego obszaru.
 */
extern elem_t *unite(elem_t *x, elem_t *y);

#endif /* FIND_UNION_H */
