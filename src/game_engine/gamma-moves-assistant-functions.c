/** @file
 * Implementacja @ref gamma-moves-assistant-functions.h.
 *
 * @author Mykhailo Shevchenko <ms420826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 18.04.2020
 */

#include "gamma-struct.h"
#include "gamma-moves-assistant-functions.h"
#include "find-union.h"
#include "strings.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/** @brief konwencja co do numeracji sąsiadów.
 */
#define LEFT 0
/** @brief konwencja co do numeracji sąsiadów.
 */
#define DOWN 1
/** @brief konwencja co do numeracji sąsiadów.
 */
#define UP 2
/** @brief konwencja co do numeracji sąsiadów.
 */
#define RIGHT 3

/**
 * Jeśli komórka przechowywana w uint32_t x[COORDS_COUNT]
 * to x[COL] == col
 */
#define COL 0
/**
 * Jeśli komórka przechowywana w uint32_t x[COORDS_COUNT]
 * to x[LINE] == line
 */
#define LINE 1

bool player_is_ok(gamma_t *g, uint32_t player)
{
    return (g != NULL) && (0 < player) && (player <= g->players_number);
}

bool coords_are_ok(gamma_t *g, uint32_t col, uint32_t line)
{
    return (g != NULL) && (col < g->width) && (line < g->height);
}

bool exists_neighbour(gamma_t *g, uint32_t player,
                      uint32_t col, uint32_t line)
{
    return (col > 0 && g->board[line][col - 1]->player == player) ||
    (line > 0 && g->board[line - 1][col]->player == player) ||
    (line + 1 < g->height && g->board[line + 1][col]->player == player) ||
    (col + 1 < g->width && g->board[line][col + 1]->player == player);
}

void set_neighbours(gamma_t *g, uint32_t player,
                    uint32_t col, uint32_t line,
                    elem_t *neighbours[NEIGHBOURS_COUNT])
{
    for (int i = 0; i < NEIGHBOURS_COUNT; ++i)
        neighbours[i] = NULL;

    if (col > 0) {
        neighbours[LEFT] = find(g->board[line][col - 1]);
        if (neighbours[LEFT]->player != player)
            neighbours[LEFT] = NULL;
    }
    if (line + 1 < g->height) {
        neighbours[DOWN] = find(g->board[line + 1][col]);
        if (neighbours[DOWN]->player != player)
            neighbours[DOWN] = NULL;
    }
    if (line > 0) {
        neighbours[UP] = find(g->board[line - 1][col]);
        if (neighbours[UP]->player != player)
            neighbours[UP] = NULL;
    }
    if (col + 1 < g->width) {
        neighbours[RIGHT] = find(g->board[line][col + 1]);
        if (neighbours[RIGHT]->player != player)
            neighbours[RIGHT] = NULL;
    }
}

bool gamma_move_possible(gamma_t *g, uint32_t player,
                         uint32_t col, uint32_t line)
{
    return player_is_ok(g, player) &&

    coords_are_ok(g, col, line) &&

    g->board[line][col]->player == 0 &&

    (exists_neighbour(g, player, col, line) ||
    g->areas[player - 1] < g->areas_number);
}

/** @brief Sprawdza, czy jest w tablicy.
 * Sprawdza, czy `e` jest w tablicy `arr` o rozmiarze `size`.
 * @param[in] e    - puszukiwany klucz.
 * @param[in] arr  - tablica, gdzie jest poszukiwany klucz.
 * @param[in] size - rozmiar tablicy.
 * @return 1 jeśli `e` jest w tablicy i 0 w przeciwnym przypadku.
 */
static bool elem_is_in_array(elem_t *e, elem_t **arr, int size)
{
    for (int i = 0; i < size; ++i) {
        if (arr[i] == e)
            return true;
    }
    return false;
}

void unite_with_neighbours(gamma_t *g, elem_t *neighbours[NEIGHBOURS_COUNT],
                           elem_t *e)
{
    elem_t *result = e;
    g->areas[e->player - 1]++; // bo w drugiej pętli odjęłoby za dużo
    elem_t *different_neighbours[NEIGHBOURS_COUNT] = {NULL, NULL, NULL, NULL};
    for (int i = 0; i < NEIGHBOURS_COUNT; ++i) {
        if (!elem_is_in_array(neighbours[i], different_neighbours,
                              NEIGHBOURS_COUNT)) {
            different_neighbours[i] = neighbours[i];
        }
    }

    for (int i = 0; i < NEIGHBOURS_COUNT; ++i) {
        if (different_neighbours[i]) {
            if (result != different_neighbours[i]) 
                g->areas[result->player - 1]--;

            result = unite(result, different_neighbours[i]);
        }
    }
}

void calc_neighbours(gamma_t *g,
                     uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT],
                     bool legit_neighbours[NEIGHBOURS_COUNT],
                     uint32_t x[COORDS_COUNT])
{
    for (int i = 0; i < NEIGHBOURS_COUNT; ++i)
        legit_neighbours[i] = false;

    if (x[COL] > 0) {
        neighbours[LEFT][COL] = x[COL] - 1;
        neighbours[LEFT][LINE] = x[LINE];
        legit_neighbours[LEFT] = true;
    }
    if (x[LINE] + 1 < g->height) {
        neighbours[DOWN][COL] = x[COL];
        neighbours[DOWN][LINE] = x[LINE] + 1;
        legit_neighbours[DOWN] = true;
    }
    if (x[LINE] > 0) {
        neighbours[UP][COL] = x[COL];
        neighbours[UP][LINE] = x[LINE] - 1;
        legit_neighbours[UP] = true;
    }
    if (x[COL] + 1 < g->width) {
        neighbours[RIGHT][COL] = x[COL] + 1;
        neighbours[RIGHT][LINE] = x[LINE];
        legit_neighbours[RIGHT] = true;
    }
}

bool is_in_array(uint32_t x, uint32_t* arr, uint64_t size)
{
    for (uint64_t i = 0; i < size; ++i) {
        if (x == arr[i])
            return true;
    }
    return false;
}

void update_free_neighbours(gamma_t *g, uint32_t player,
                            uint32_t col, uint32_t line)
{
    uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT], x[COORDS_COUNT];
    x[COL] = col;
    x[LINE] = line;
    bool legit_neighbours[NEIGHBOURS_COUNT];
    calc_neighbours(g, neighbours, legit_neighbours, x);

// Przyrost wolnych pól.
    for (int i = 0; i < NEIGHBOURS_COUNT; ++i) {
        if (legit_neighbours[i] &&
        g->board[neighbours[i][LINE]][neighbours[i][COL]]->player == 0 &&
        !exists_neighbour(g, player, neighbours[i][COL], neighbours[i][LINE]))
            g->free_neighbours[player - 1]++;
    }

// Zmniejszenie wolnych pól u sąsiadów.
    uint32_t decremented_free_neighbours_for_this_player[NEIGHBOURS_COUNT] =
    {0, 0, 0, 0};

    for (int i = 0; i < NEIGHBOURS_COUNT; ++i) {
        if (legit_neighbours[i] &&
        g->board[neighbours[i][LINE]][neighbours[i][COL]]->player != 0 &&
        !is_in_array(g->board[neighbours[i][LINE]][neighbours[i][COL]]->player,
        decremented_free_neighbours_for_this_player, NEIGHBOURS_COUNT)) {

            decremented_free_neighbours_for_this_player[i] =
            g->board[neighbours[i][LINE]][neighbours[i][COL]]->player;

            g->free_neighbours
            [g->board[neighbours[i][LINE]][neighbours[i][COL]]->player - 1]--;

        }
    }
}

void push(gamma_t *g, uint64_t *top, uint32_t x[COORDS_COUNT])
{
    for (int i = 0; i < COORDS_COUNT; ++i)
        g->stack[*top][i] = x[i];
    (*top)++;
}

void pop(gamma_t *g, uint64_t *top, uint32_t x[COORDS_COUNT])
{
    (*top)--;
    for (int i = 0; i < COORDS_COUNT; ++i)
        x[i] = g->stack[*top][i];
}

void push_neighbours(gamma_t *g, uint64_t *top, uint32_t x[COORDS_COUNT])
{
    uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT];
    bool legit_neighbours[NEIGHBOURS_COUNT];
    calc_neighbours(g, neighbours, legit_neighbours, x);

    for (int i = 0; i < NEIGHBOURS_COUNT; ++i) {
        if (legit_neighbours[i] &&

            !(g->visited[neighbours[i][LINE]][neighbours[i][COL]]) &&

            g->board[neighbours[i][LINE]][neighbours[i][COL]]->player ==
            g->board[x[LINE]][x[COL]]->player) {

            g->visited[neighbours[i][LINE]][neighbours[i][COL]] = true;
            push(g, top, neighbours[i]);
        }
    }
}

void check_dest(uint32_t x[COORDS_COUNT],
                uint32_t dest[NEIGHBOURS_COUNT][COORDS_COUNT],
                bool legit_dest[NEIGHBOURS_COUNT],
                bool dest_visited[NEIGHBOURS_COUNT])
{
    for (int i = 0; i < NEIGHBOURS_COUNT; ++i) {
        if (legit_dest[i] &&
            dest[i][LINE] == x[LINE] && dest[i][COL] == x[COL])

            dest_visited[i] = true;
    }
}

void push_neighbours_clear(gamma_t *g, uint64_t *top, uint32_t x[COORDS_COUNT])
{
    uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT];
    bool legit_neighbours[NEIGHBOURS_COUNT];
    calc_neighbours(g, neighbours, legit_neighbours, x);

    for (int i = 0; i < NEIGHBOURS_COUNT; ++i) {
        if (legit_neighbours[i] &&
            g->visited[neighbours[i][LINE]][neighbours[i][COL]]) {

            g->visited[neighbours[i][LINE]][neighbours[i][COL]] = false;
            push(g, top, neighbours[i]);
        }
    }
}

void clear_visited(gamma_t *g, uint32_t start[COORDS_COUNT])
{
    uint64_t top = 0;
    g->visited[start[LINE]][start[COL]] = false;
    push(g, &top, start);
    while (top != 0) {
        uint32_t current[COORDS_COUNT];
        pop(g, &top, current);
        push_neighbours_clear(g, &top, current);
    }
}

elem_t *remake_subset(gamma_t *g, uint32_t start[COORDS_COUNT],
                      uint32_t dest[NEIGHBOURS_COUNT][COORDS_COUNT],
                      bool legit_dest[NEIGHBOURS_COUNT],
                      bool dest_visited[NEIGHBOURS_COUNT])
{
    elem_t *new_area = make_set(g->board[start[LINE]][start[COL]],
                                g->board[start[LINE]][start[COL]]->player);
    uint64_t top = 0;
    push(g, &top, start);
    g->visited[start[LINE]][start[COL]] = true;
    while (top != 0) {
        uint32_t current[COORDS_COUNT];
	pop(g, &top, current);
        check_dest(current, dest, legit_dest, dest_visited);

        new_area = unite(new_area,
        make_set(g->board[current[LINE]][current[COL]],
                 g->board[current[LINE]][current[COL]]->player));

        push_neighbours(g, &top, current);
    }
    clear_visited(g, start);
    return new_area;
}

int make_subsets(gamma_t *g, uint32_t player,
                 uint32_t col, uint32_t line, elem_t *subsets[NEIGHBOURS_COUNT])
{
    for (int i = 0; i < NEIGHBOURS_COUNT; ++i)
        subsets[i] = NULL;
    uint32_t x[COORDS_COUNT], dest[NEIGHBOURS_COUNT][COORDS_COUNT];
    x[LINE] = line;
    x[COL] = col;
    bool legit_dest[NEIGHBOURS_COUNT], dest_visited[NEIGHBOURS_COUNT];
    for (int i = 0; i < NEIGHBOURS_COUNT; ++i)
        dest_visited[i] = false;
    calc_neighbours(g, dest, legit_dest, x);

    for (int i = 0; i < NEIGHBOURS_COUNT; ++i) {
        if (legit_dest[i] &&
            g->board[dest[i][LINE]][dest[i][COL]]->player != player)
            legit_dest[i] = false;
    }

    int ans = 0;
    for (int i = 0; i < NEIGHBOURS_COUNT; ++i) {
        if (legit_dest[i] && !dest_visited[i]) {

            subsets[i] =
            remake_subset(g, dest[i], dest, legit_dest, dest_visited);

            ans++;
        }
    }
    return ans;
}

void update_free_neighbours_golden(gamma_t *g, uint32_t former_player,
                                   uint32_t col, uint32_t line)
{
    uint32_t neighbours[NEIGHBOURS_COUNT][COORDS_COUNT], x[COORDS_COUNT];
    x[LINE] = line;
    x[COL] = col;
    bool legit_neighbours[NEIGHBOURS_COUNT];
    calc_neighbours(g, neighbours, legit_neighbours, x);

// zmniejszenie free_neighbours dla former_player
    for (int i = 0; i < NEIGHBOURS_COUNT; ++i) {
        if (legit_neighbours[i] &&

        g->board[neighbours[i][LINE]][neighbours[i][COL]]->player == 0 &&

        !exists_neighbour(g, former_player,
                          neighbours[i][COL], neighbours[i][LINE]))

            g->free_neighbours[former_player - 1]--;
    }

// przyrost dla sasiadow w zwiazku z pojawieniem sie pustego pola
    uint32_t incremented_free_neighbours_for_this_player[NEIGHBOURS_COUNT] =
    {0, 0, 0, 0};
    for (int i = 0; i < NEIGHBOURS_COUNT; ++i) {
        if (legit_neighbours[i] &&
        g->board[neighbours[i][LINE]][neighbours[i][COL]]->player != 0 &&
        !is_in_array(g->board[neighbours[i][LINE]][neighbours[i][COL]]->player,
        incremented_free_neighbours_for_this_player, NEIGHBOURS_COUNT)) {

            incremented_free_neighbours_for_this_player[i] =
            g->board[neighbours[i][LINE]][neighbours[i][COL]]->player;

            g->free_neighbours
            [g->board[neighbours[i][LINE]][neighbours[i][COL]]->player - 1]++;

        }
    }
}
