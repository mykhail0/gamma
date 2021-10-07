/** @file
 * Pomocnicze funkcje do @ref gamma_move i @ref gamma_golden_move.
 *
 * @author Mykhailo Shevchenko <ms420826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 18.04.2020
 */

#include "gamma-struct.h"
#include "find-union.h"
#include "strings.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/** @brief Największa liczba sąsiednich pól dla wybranej komórki
 */
#define NEIGHBOURS_COUNT 4

/** @brief Sprawdza poprawność numeru gracza.
 * Zwraca 'false' jeśli plansza jest pusta.
 */
bool player_is_ok(gamma_t *g, uint32_t player);

/** @brief Sprawdza poprawność współrzędnych komórki.
 * Zwraca 'false' jeśli plansza jest pusta.
 */
bool coords_are_ok(gamma_t *g, uint32_t col, uint32_t line);

/** @brief Sprawdza, czy pole sąsiaduje z pionkiem gracza.
 * Zakłada poprawność argumentów.
 * @param[in] g      - stan gry.
 * @param[in] player - numer gracza.
 * @param[in] col    - kolumna `g->board` w jakiej znajduje się pole.
 * @param[in] line   - wiersz `g->board` w jakim znajduje się pole.
 * @return `true` jeśli komórka o danych współrzędnych.
 * sąsiaduje z pionkiem gracza `player`.
 */
bool exists_neighbour(gamma_t *g, uint32_t player,
                      uint32_t col, uint32_t line);

/** @brief Inicjuje tablicę reprezentantów obszarów do jakich należą sąsiedzi pola.
 * Niech i należy do            {0,    1,    2,    3}.
 * Liczby oznaczają odpowiedno:  lewy  dolny górny prawy sąsiad.
 * `neighbours[i]` jest ustawiany na `NULL` jeśli i-ty sąsiad nie istnieje
 * lub na tym polu nie stoi pionek gracza nr `player`.
 * W przeciwnym przypadku jest ustawiany na reprezentanta zbioru, do którego
 * należy i-ty sąsiad komórki.
 * @param[in] g           - stan gry.
 * @param[in] player      - numer gracza.
 * @param[in] col         - kolumna `g->board` w jakiej znajduje się pole.
 * @param[in] line        - wiersz `g->board` w jakim znajduje się pole.
 * @param[out] neighbours - tu są zapisywani reprezentanci.
 */
void set_neighbours(gamma_t *g, uint32_t player, uint32_t col, uint32_t line,
                    elem_t *neighbours[NEIGHBOURS_COUNT]);

/** @brief Sprawdza, czy @ref gamma_move się powiedzie.
 * @param[in] g      - stan gry.
 * @param[in] player - numer gracza.
 * @param[in] col    - kolumna `g->board` w jakiej znajduje się pole.
 * @param[in] line   - wiersz `g->board` w jakim znajduje się pole.
 * @return `true` jeśli ruch jest możliwy
 * i `false` w przeciwnym przypadku.
 */
bool gamma_move_possible(gamma_t *g, uint32_t player,
                         uint32_t col, uint32_t line);

/** @brief Łączy pole z sąsiednimi obszarami.
 * Jeśli `neighbours` to reprezentanty sąsiedzkich obszarów do `e`,
 * to wszystkie są łączone z `e` a liczba obszarów jest zaktualizowana.
 * @param[in] g          - stan gry.
 * @param[in] neighbours - reprezentanci sąsidzkich obszarów co do `e`.
 * @param[in] e          - pole.
 */
void unite_with_neighbours(gamma_t *g, elem_t *neighbours[NEIGHBOURS_COUNT],
                           elem_t *e);

/** @brief Wylicza i zapisuje w tablicy współrzędne sąsiadów komórki.
 * @param[in] g                 - stan gry.
 * @param[out] neighbours       - współrzędne sąsiadów.
 * @param[out] legit_neighbours - w `legit_neighbours[i]` `true` wtw
 *                                `neighbours[i]` zawiera prawdziwą informację.
 * @param[in] x                 - w `x[LINE]` jest `line` jak w innych funkcjach,
 *                                w `x[COL]` jest `col` jak w innych funkcjach.
 */
void calc_neighbours(gamma_t *g,
                     uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT],
                     bool legit_neighbours[NEIGHBOURS_COUNT],
                     uint32_t x[COORDS_COUNT]);

/** @brief Sprawdza, czy jest w tablicy.
 * Sprawdza, czy `x` jest w tablicy `arr` o rozmiarze `size`.
 * @param[in] x    - puszukiwany klucz.
 * @param[in] arr  - tablica, gdzie jest poszukiwany klucz.
 * @param[in] size - rozmiar tablicy.
 * @return 1 jeśli `x` jest w tablicy i 0 w przeciwnym przypadku.
 */
bool is_in_array(uint32_t x, uint32_t* arr, uint64_t size);

/** @brief Aktualizuje liczbę wolnych pól wszystkich graczy po wykonaniu ruchu.
 * Trzeba wywołać w @ref gamma_move przed zmianą pola z 0 na player.
 * @param[in] g      - stan gry.
 * @param[in] player - numer gracza, który będzie na tym polu,
 *                     wokół którego aktualizujemy.
 * @param[in] col    - kolumna `g->board` w jakiej znajduje się pole.
 * @param[in] line   - wiersz `g->board` w jakim znajduje się pole.
 */
void update_free_neighbours(gamma_t *g, uint32_t player,
                            uint32_t col, uint32_t line);

/** @brief Dodaje element do stosu.
 * @param[in] g   - stan gry.
 * @param[in] top - wskaźnik na indeks pierwszego pustego miejsca na stosie.
 * @param[in] x   - w `x[LINE]` jest `line` jak w innych funkcjach,
 *                  w `x[COL]` jest `col` jak w innych funkcjach.
 */
void push(gamma_t *g, uint64_t *top, uint32_t x[COORDS_COUNT]);

/** @brief Zdejmuje element ze stosu.
 * @param[in] g   - stan gry.
 * @param[in] top - wskaźnik na indeks pierwszego pustego miejsca na stosie.
 * @param[in] x   - w `x[LINE]` jest `line` jak w innych funkcjach,
 *                  w `x[COL]` jest `col` jak w innych funkcjach.
 */
void pop(gamma_t *g, uint64_t *top, uint32_t x[COORDS_COUNT]);

/** @brief Dodaje niezwiedzonych sąsiadów do stosu.
 * Dodaje niezwiedzonych sąsiadów `x` do stosu
 * takich, że pionek stojący na sąsiedzie jest taki sam jak na `x`.
 * @param[in] g   - stan gry.
 * @param[in] top - wskaźnik na indeks pierwszego pustego miejsca na stosie.
 * @param[in] x   - w `x[LINE]` jest `line` jak w innych funkcjach,
 *                  w `x[COL]` jest `col` jak w innych funkcjach.
 */
void push_neighbours(gamma_t *g, uint64_t *top, uint32_t x[COORDS_COUNT]);

/** @brief Sprawdza, czy komórka należy do tablicy `dest`.
 * (z poprawką na to że niektóre elementy `dest` nie mają znaczenia).
 * @param[in] x             - w `x[LINE]` jest `line` jak w innych funkcjach,
 *                            w `x[COL]` jest `col` jak w innych funkcjach.
 * @param[in] dest          - gdzie szukamy.
 * @param[in] legit_dest    - poprawka.
 * @param[out] dest_visited - wynik.
 */
void check_dest(uint32_t x[COORDS_COUNT],
                uint32_t dest[NEIGHBOURS_COUNT][COORDS_COUNT],
                bool legit_dest[NEIGHBOURS_COUNT],
                bool dest_visited[NEIGHBOURS_COUNT]);

/** @brief Dodaje zwiedzonych sąsiadów `x` do stosu.
 * @param[in] g   - stan gry.
 * @param[in] top - wskaźnik na indeks pierwszego pustego miejsca na stosie.
 * @param[in] x   - w `x[LINE]` jest `line` jak w innych funkcjach,
 *                  w `x[COL]` jest `col` jak w innych funkcjach.
 */
void push_neighbours_clear(gamma_t *g, uint64_t *top, uint32_t x[COORDS_COUNT]);

/** @brief Ustawia wszystkie zwiedzone komórki wokół `start` na niezwiedzone.
 * @param[in] g     - stan gry.
 * @param[in] start - współrzędne komórki startowej.
 */
void clear_visited(gamma_t *g, uint32_t start[COORDS_COUNT]);

/** @brief Reorganizuje obszar.
 * DFS startuje z pola `start`.
 * W `dest_visited[i]` zapisuje czy pole `dest[i]` było zwiedzone.
 * (Jeśli `legit_dest[i]` jest ustawione na `true`).
 * @return reprezentanta obszaru, który powstał
 */
elem_t *remake_subset(gamma_t *g, uint32_t start[COORDS_COUNT],
                      uint32_t dest[NEIGHBOURS_COUNT][COORDS_COUNT],
                      bool legit_dest[NEIGHBOURS_COUNT],
                      bool dest_visited[NEIGHBOURS_COUNT]);

/** @brief Reorganizuje obszary wokół usuwanej komórki.
 * Pomocnicza do `gamma_golden_move()`.
 * Po zamianie pionka `player` na polu (`col`, `line`) na puste pole
 * aktualizuje reprezentantów ziorów sąsiadujących obszarów
 * i umieszcza ich w `subsets`.
 * @param[in] g        - stan gry.
 * @param[in] player   - nr gracza, pionek którego usunięto.
 * @param[in] col      - kolumna `g->board` w jakiej znajduje się pole.
 * @param[in] line     - wiersz `g->board` w jakim znajduje się pole.
 * @param[out] subsets - reprezentanci powstałych obszarów.
 * @return liczbę powstałych obszarów.
 */
int make_subsets(gamma_t *g, uint32_t player,
                 uint32_t col, uint32_t line,
                 elem_t *subsets[NEIGHBOURS_COUNT]);

/**
 * Aktualizuje `free_neighbours` dla wszystkich graczy w okolicy,
 * tak jakby na polu (`col`, `line`) zamiast `former_player`
 * pojawił się pusty obszar.
 * @param[in] g             - stan gry.
 * @param[in] former_player - numer gracza, którego `free_neighbours`
 *                            muszą być zaktualizowane
 *                            inaczej niż u reszty sąsiadów.
 * @param[in] col           - kolumna `g->board` w jakiej znajduje się pole.
 * @param[in] line          - wiersz `g->board` w jakim znajduje się pole.
 */
void update_free_neighbours_golden(gamma_t *g, uint32_t former_player,
                                   uint32_t col, uint32_t line);
