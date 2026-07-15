/** @file
 * Implementacja @ref gamma.h.
 *
 * @author Mykhailo Shevchenko <ms420826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.04.2020
 */

#include "gamma.h"
#include "gamma-struct.h"
#include "gamma-delete.h"
#include "gamma-moves-assistant-functions.h"
#include "find-union.h"
#include "../UI/text_lib/strings.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

/** @brief Wstępnie alokuje pamięć i ustawia wartości.
 * @param[in] g       - wskaźnik na planszę jaką alokuje funkcja.
 * @param[in] width   - szerokość planszy, liczba dodatnia,
 * @param[in] height  - wysokość planszy, liczba dodatnia,
 * @param[in] players - liczba graczy, liczba dodatnia,
 * @param[in] areas   - maksymalna liczba obszarów,
 *                      jakie może zająć jeden gracz.
 * @return 1 jeśli się powiodło i 0 jeśli zabrakło pamięci
 * albo dane są niepoprawne.
 */
static bool initial_init(gamma_t **g, uint32_t width, uint32_t height,
                         uint32_t players, uint32_t areas)
{
    if (width <= 0 || height <= 0 || players <= 0 || areas <= 0)
        return false;

    *g = malloc(sizeof **g);
    if (*g == NULL)
        return false;

    (*g)->width = width;
    (*g)->height = height;
    (*g)->areas_number = areas;
    (*g)->players_number = players;

// żeby właściwie pomnożyć w razie wyjścia poza zakres.
    (*g)->free_fields = (*g)->width;
    (*g)->free_fields *= (*g)->height;

    (*g)->free_neighbours = NULL;
    (*g)->busy_fields = NULL;
    (*g)->areas = NULL;
    (*g)->golden_not_used = NULL;
    (*g)->board = NULL;
    (*g)->visited = NULL;
    (*g)->stack = NULL;
    return true;
}

/** @brief Alokuje pamięć dla informacji o graczach i ustawia początkowe wartości.
 * @param[in] g - stan gry.
 * @return 1 jeśli się udało i 0 jeśli zabrakło pamięci.
 */
static bool init_players(gamma_t *g)
{
    g->free_neighbours = malloc(g->players_number *
                                sizeof *(g->free_neighbours));
    if (g->free_neighbours == NULL) {
        gamma_delete(g);
        return false;
    }

    g->busy_fields = malloc(g->players_number * sizeof *(g->busy_fields));
    if (g->busy_fields == NULL) {
        gamma_delete(g);
        return false;
    }

    g->areas = malloc(g->players_number * sizeof *(g->areas));
    if (g->areas == NULL) {
        gamma_delete(g);
        return false;
    }

    g->golden_not_used = malloc(g->players_number *
                                sizeof *(g->golden_not_used));
    if (g->golden_not_used == NULL) {
        gamma_delete(g);
        return false;
    }

    for (uint32_t i = 0; i < g->players_number; ++i) {
        g->free_neighbours[i] = 0;
        g->busy_fields[i] = 0;
        g->areas[i] = 0;
        g->golden_not_used[i] = true;
    }
    return true;
}

/** @brief Alokuje planszę i ustawia wszystkie pola na puste.
 * @return 1 jeśli się powiodło i 0 jeśli zabrakło pamięci.
 */
static bool init_board(gamma_t *g)
{
    g->board = malloc(g->height * sizeof *(g->board));
    if (g->board == NULL) {
        gamma_delete(g);
        return false;
    }

    for (uint32_t i = 0; i < g->height; ++i)
        g->board[i] = NULL;

    for (uint32_t i = 0; i < g->height; ++i) {
        g->board[i] = malloc(g->width * sizeof *(g->board[i]));
        if (g->board[i] == NULL) {
            gamma_delete(g);
            return false;
        }

        for (uint32_t j = 0; j < g->width; ++j)
            g->board[i][j] = NULL;

        for (uint32_t j = 0; j < g->width; ++j) {
            g->board[i][j] = malloc(sizeof *(g->board[i][j]));
            if (g->board[i][j] == NULL) {
                gamma_delete(g);
                return false;
            }

            make_set(g->board[i][j], 0);
        }
    }
    return true;
}

/** @brief Alokacja i inicjalizacja 'visited'.
 * Alokuje i inicjuje tablicę,
 * która przechowuje informacje o przetworzonych komórkach planszy
 * podczas wykonywania algorytmu DFS.
 * @return 1 jeśli się powiodło i 0 jeśli zabrakło pamięci.
 */
static bool init_visited(gamma_t *g)
{
    g->visited = malloc(g->height * sizeof *(g->visited));
    if (g->visited == NULL) {
        gamma_delete(g);
        return false;
    }

    for (uint32_t i = 0; i < g->height; ++i)
        g->visited[i] = NULL;

    for (uint32_t i = 0; i < g->height; ++i) {
	g->visited[i] = malloc(g->width * sizeof *(g->visited[i]));
        if (g->visited[i] == NULL) {
            gamma_delete(g);
            return false;
        }

	for (uint32_t j = 0; j < g->width; ++j)
	    g->visited[i][j] = false;
    }
    return true;
}

/** @brief Alokuje stos na potrzeby DFS przy @ref gamma_golden_move.
 * @return 1 jeśli się powiodło i 0 jeśli zabrakło pamięci.
 */
static bool init_stack(gamma_t *g)
{
    g->stack = malloc(g->free_fields * sizeof *(g->stack));
    if (g->stack == NULL) {
        gamma_delete(g);
        return false;
    }
    return true;
}

gamma_t *gamma_new(uint32_t width, uint32_t height,
                   uint32_t players, uint32_t areas)
{
    gamma_t *g;
    if (!initial_init(&g, width, height, players, areas))
        return NULL;
    if (!init_players(g))
        return NULL;
    if (!init_board(g))
        return NULL;
    if (!init_visited(g))
        return NULL;
    if (!init_stack(g))
        return NULL;
    return g;
}

void gamma_delete(gamma_t *g)
{
    if (g) {
        free(g->free_neighbours);
        free(g->busy_fields);
        free(g->areas);
        free(g->golden_not_used);
        board_delete(g);
        visited_delete(g);
        free(g->stack);
        free(g);
    }
}

bool gamma_move(gamma_t *g, uint32_t player, uint32_t col, uint32_t line)
{
    if (g == NULL)
        return false;

    line = g->height - line - 1;
    if (!gamma_move_possible(g, player, col, line))
        return false;

    bool no_neighbours = !exists_neighbour(g, player, col, line);
    if (no_neighbours)
        g->areas[player - 1]++;

    g->busy_fields[player - 1]++;
    g->free_fields--;
    update_free_neighbours(g, player, col, line);
    make_set(g->board[line][col], player);

    if (!no_neighbours) {
        elem_t *neighbours[NEIGHBOURS_COUNT];
        set_neighbours(g, player, col, line, neighbours);
        unite_with_neighbours(g, neighbours, g->board[line][col]);
    }
    return true;
}

bool gamma_golden_move(gamma_t *g, uint32_t player, uint32_t col, uint32_t line)
{
    if (!player_is_ok(g, player))
        return false;

    line = g->height - line - 1;
    if (!coords_are_ok(g, col, line))
        return false;

    elem_t former = *(g->board[line][col]);
    make_set(g->board[line][col], 0);

    if (!gamma_move_possible(g, player, col, line) ||
        !g->golden_not_used[player - 1] ||
        former.player == 0 ||
        former.player == player) {
        *(g->board[line][col]) = former;
        return false;
    }

    elem_t *subsets[NEIGHBOURS_COUNT];
    int areas = make_subsets(g, former.player, col, line, subsets);

// małoprawdopodobne wyjście poza zakres
    if (g->areas[former.player - 1] + areas - 1 > g->areas_number) {
        *(g->board[line][col]) = former;
        elem_t *root = g->board[line][col];
        make_set(root, g->board[line][col]->player);
        for (int i = 0; i < NEIGHBOURS_COUNT; ++i)
            root = unite(root, subsets[i]);
        return false;
    }

    g->areas[former.player - 1] += areas - 1;
    g->busy_fields[former.player - 1]--;
    g->golden_not_used[player - 1] = false;
    update_free_neighbours_golden(g, former.player, col, line);

    line = g->height - line - 1;
    g->free_fields++;
    gamma_move(g, player, col, line);
    return true;
}

uint64_t gamma_busy_fields(gamma_t *g, uint32_t player)
{
    if (!player_is_ok(g, player))
        return 0;
    return g->busy_fields[player - 1];
}

uint64_t gamma_free_fields(gamma_t *g, uint32_t player)
{
    if (!player_is_ok(g, player))
        return 0;
    uint64_t ans = g->free_fields;
    if (g->areas[player - 1] == g->areas_number)
        ans = g->free_neighbours[player - 1];
    return ans;
}

/** @brief Odwraca skutki wykonania ruchu innego gracza na pole
 * (`x`, `y`), zajęte przez gracza o numerze `player`.
 */
static void reverse_gamma_move(gamma_t *g, uint32_t player,
                               uint32_t x, uint32_t y)
{
    bool gamma_golden_not_used = g->golden_not_used[player - 1];
    g->golden_not_used[player - 1] = true;
    gamma_golden_move(g, player, x, y);
    g->golden_not_used[player - 1] = gamma_golden_not_used;
}

bool gamma_golden_possible(gamma_t *g, uint32_t player)
{
    bool ans = false;
    if (!player_is_ok(g, player))
        return ans;
    if (g->golden_not_used[player - 1] == false)
        return ans;

    if (g->areas[player - 1] != g->areas_number) {
        for (uint32_t i = 0; i < g->players_number; ++i) {
            if (i + 1 != player && g->busy_fields[i] != 0)
                return true;
        }
    } else {
        uint32_t x, y, former_player;
        for (uint32_t i = 0; i < g->height && !ans; ++i) {
            for (uint32_t j = 0; j < g->width && !ans; ++j) {
                former_player = g->board[i][j]->player;
                x = j;
                y = g->height - i - 1;
                ans = gamma_golden_move(g, player, x, y);
            }
        }
        if (ans) {
            g->golden_not_used[player - 1] = true;
            reverse_gamma_move(g, former_player, x, y);
        }
    }
    return ans;
}

char* gamma_board(gamma_t *g)
{
    if (g == NULL)
        return NULL;

    int column_width = count_digits((unsigned long) g->players_number);
    if (column_width > 1)
        column_width += 1;
    char *str = malloc((g->height * (g->width * column_width + 1) + 1) *
                       sizeof *str);
    if (str == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    char *buffer = malloc((column_width + 1) * sizeof *buffer);
    if (buffer == NULL) {
        free(str);
        errno = ENOMEM;
        return NULL;
    }
    buffer[column_width] = '\0';

    uint64_t count = 0;
    for (uint32_t i = 0; i < g->height; ++i) {

        for (uint32_t j = 0; j < g->width; ++j) {
            sprintf(buffer, "%*" PRIu32, column_width, g->board[i][j]->player);
            if (g->board[i][j]->player == 0)
                buffer[column_width - 1] = '.';

            cat_strings(str, buffer, count);
            count += column_width;
        }
        str[count] = '\n';
        count++;
    }
    str[count] = '\0';
    free(buffer);
    return str;
}
