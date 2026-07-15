/** @file
 * Definicja rekordu, który przechowuje stan gry.
 *
 * @author Mykhailo Shevchenko <ms420826@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.04.2020
 */

#ifndef GAMMA_STRUCT_H
#define GAMMA_STRUCT_H

#include "find-union.h"
#include <stdbool.h>
#include <inttypes.h>

/** @brief Liczba współrzędnych komórki.
 */
#define COORDS_COUNT 2

/** Stan gry.
*/
struct gamma {
    uint32_t width; ///< szerokość planszy
    uint32_t height; ///< wysokość planszy
    uint32_t areas_number; ///< maksymalna liczba obszarów dla dowolnego gracza
    uint32_t players_number; ///< liczba graczy
    uint64_t free_fields; ///< liczba wolnych pól
    uint64_t *free_neighbours; ///< w i-tym indeksie liczba wolnych pól stycznych dla gracza `i + 1`
    uint64_t *busy_fields; ///< w i-tym indeksie liczba pól zajętych przez gracza `i + 1`
    uint32_t *areas; ///< w i-tym indeksie liczba obszarów gracza `i + 1`
    bool *golden_not_used; ///< w i-tym indeksie `true` jeśli gracz `i + 1` nie wykonał złotego ruchu
/** w i-tym wierszu i-tej kolumnie tablicy
 * jest element drzewa zbioru
 * jakim jest obszar gracza,
 * do którego należy komórka o danych współrzędnych
 */
    elem_t ***board;
/** przechowuje informacje o odwiedzonych komórkach
 * przy reorganizacji obszarów
 * w trakcie wykonania złotego ruchu.
 */
    bool **visited;
/** stos zaimplementowany tablicowo na potrzeby DFS'a,
 * który reorganizuje obszary podczas złotego ruchu.
 */
    uint32_t (*stack)[COORDS_COUNT];
};

/** @brief Rekord przechowujący stan gry.
 */
typedef struct gamma gamma_t;

#endif /* GAMMA_STRUCT_H */
