/** @file
 * Implementacja @ref batch-mode.h
 *
 * @author Mykhailo Shevchenko <ms420826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.05.2020
 */

/** @brief To dla getline.
 */
#define _GNU_SOURCE

#include "batch-mode.h"
#include "../../game_engine/gamma.h"
#include "../error-handling.h"
#include "../text_lib/strings.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

/** @brief Możliwe polecenia w trybie wsadowym.
 */
enum Command {
    NO_COMMAND,
    INVALID_COMMAND,
    GAMMA_MOVE,
    GAMMA_GOLDEN_MOVE,
    GAMMA_BUSY_FIELDS,
    GAMMA_FREE_FIELDS,
    GAMMA_GOLDEN_POSSIBLE,
    GAMMA_BOARD
};

/** @brief Liczba poleceń dla trybu wsadowego.
 */
#define POSSIBLE_COMMANDS 8

/** @brief Liczba parametrów dla polecenia NO_COMMAND.
 */
#define NO_COMMAND_PARAMS 0
/** @brief Liczba parametrów dla polecenia INVALID_COMMAND.
 */
#define INVALID_COMMAND_PARAMS 0
/** @brief Liczba parametrów dla polecenia GAMMA_MOVE.
 */
#define GAMMA_MOVE_PARAMS 3
/** @brief Liczba parametrów dla polecenia GAMMA_GOLDEN_MOVE.
 */
#define GAMMA_GOLDEN_MOVE_PARAMS 3
/** @brief Liczba parametrów dla polecenia GAMMA_BUSY_FIELDS.
 */
#define GAMMA_BUSY_FIELDS_PARAMS 1
/** @brief Liczba parametrów dla polecenia GAMMA_FREE_FIELDS.
 */
#define GAMMA_FREE_FIELDS_PARAMS 1
/** @brief Liczba parametrów dla polecenia GAMMA_GOLDEN_POSSIBLE.
 */
#define GAMMA_GOLDEN_POSSIBLE_PARAMS 1
/** @brief Liczba parametrów dla polecenia GAMMA_BOARD.
 */
#define GAMMA_BOARD_PARAMS 0

/** @brief Indeks odpowiedniego parametra w tablicy parametrów.
 */
#define PLAYER 0
/** @brief Indeks odpowiedniego parametra w tablicy parametrów.
 */
#define X 1
/** @brief Indeks odpowiedniego parametra w tablicy parametrów.
 */
#define Y 2

/** @brief W params_number[i] liczba parametrów dla polecenia `i`.
 */
static const int params_number[POSSIBLE_COMMANDS] = {
    NO_COMMAND_PARAMS,
    INVALID_COMMAND_PARAMS,
    GAMMA_MOVE_PARAMS,
    GAMMA_GOLDEN_MOVE_PARAMS,
    GAMMA_BUSY_FIELDS_PARAMS,
    GAMMA_FREE_FIELDS_PARAMS,
    GAMMA_GOLDEN_POSSIBLE_PARAMS,
    GAMMA_BOARD_PARAMS
};

/** @brief Przetwarza polecenie 'm'.
 */
static void process_gamma_move(gamma_t *g, uint32_t params[])
{
    printf("%d\n", (int) gamma_move(g, params[PLAYER], params[X], params[Y]));
}

/** @brief Przetwarza polecenie 'g'.
 */
static void process_gamma_golden_move(gamma_t *g, uint32_t params[])
{
    printf("%d\n",
           (int) gamma_golden_move(g, params[PLAYER], params[X], params[Y]));
}

/** @brief Przetwarza polecenie 'b'.
 */
static void process_gamma_busy_fields(gamma_t *g, uint32_t params[])
{
    printf("%" PRIu64 "\n", gamma_busy_fields(g, params[PLAYER]));
}

/** @brief Przetwarza polecenie 'f'.
 */
static void process_gamma_free_fields(gamma_t *g, uint32_t params[])
{
    printf("%" PRIu64 "\n", gamma_free_fields(g, params[PLAYER]));
}

/** @brief Przetwarza polecenie 'q'.
 */
static void process_gamma_golden_possible(gamma_t *g, uint32_t params[])
{
    printf("%d\n", (int) gamma_golden_possible(g, params[PLAYER]));
}

/** @brief Przetwarza polecenie 'p'.
 */
static void process_gamma_board(gamma_t *g)
{
    char *board = gamma_board(g);
    if (board == NULL)
        puts("0");
    else
        printf("%s", board);
    free(board);
}

/** @brief Przetwarza polecenie `com` z zadanymi parametrami.
 */
static void process_command(enum Command com, gamma_t *g, uint32_t params[])
{
    switch (com) {
    case GAMMA_MOVE:
        process_gamma_move(g, params);
        break;
    case GAMMA_GOLDEN_MOVE:
        process_gamma_golden_move(g, params);
        break;
    case GAMMA_BUSY_FIELDS:
        process_gamma_busy_fields(g, params);
        break;
    case GAMMA_FREE_FIELDS:
        process_gamma_free_fields(g, params);
        break;
    case GAMMA_GOLDEN_POSSIBLE:
        process_gamma_golden_possible(g, params);
        break;
    case GAMMA_BOARD:
        process_gamma_board(g);
        break;
    default:
        break;
    }
}


/** @brief Dla danej linijki zwraca to, jakim jest poleceniem.
 */
static enum Command checkCommand(char *line)
{
    if (line == NULL || line[0] == '\n' || line[0] == '#')
        return NO_COMMAND;

    enum Command ans = INVALID_COMMAND;
    char *firstWord = strtok(line, whiteSpaces);
    if (firstWord != NULL) {
// Sprawdzanie pierwszego znaku jest potrzebne dlatego, że nie może być
// białych znaków na początku polecenia.
        if (strcmp(firstWord, "m") == EQUAL && line[0] == 'm')
            ans = GAMMA_MOVE;
        if (strcmp(firstWord, "g") == EQUAL && line[0] == 'g')
            ans = GAMMA_GOLDEN_MOVE;
        if (strcmp(firstWord, "b") == EQUAL && line[0] == 'b')
            ans = GAMMA_BUSY_FIELDS;
        if (strcmp(firstWord, "f") == EQUAL && line[0] == 'f')
            ans = GAMMA_FREE_FIELDS;
        if (strcmp(firstWord, "q") == EQUAL && line[0] == 'q')
            ans = GAMMA_GOLDEN_POSSIBLE;
        if (strcmp(firstWord, "p") == EQUAL && line[0] == 'p')
            ans = GAMMA_BOARD;
    }
    return ans;
}

/** @brief Łączy parę funkcji ze "string.h" dla wygody.
 */
static bool get_uints(int uintCount, char *strings[],
                      unsigned long numbers[], uint32_t uints[])
{
    bool ans = get_strings(uintCount, strings);
    if (ans)
        ans = stringArr_to_ulArr(uintCount, strings, numbers);
    if (ans)
        ans = ulArr_to_uintArr(uintCount, numbers, uints);
    return ans;
}

/** @brief Przetwarza linijkę.
 */
static int parse_line(gamma_t *g, unsigned long long *line)
{
    (*line)++;
    char *str = NULL;
    size_t str_size = 0;
    errno = 0;
    ssize_t errsv = getline(&str, &str_size, stdin);
    int error = errno;
    if (errsv == - 1) {
        free(str);
        errno = error;
        return errsv;
    }

// Mogę zrzutować ponieważ nie jest równe - 1
    if ((size_t) errsv != strlen(str)) {
        free(str);
        printERR(*line);
        return errsv;
    }

    enum Command tmp = checkCommand(str);
    if (tmp == NO_COMMAND || tmp == INVALID_COMMAND) {
        if (tmp == INVALID_COMMAND)
            printERR(*line);
        free(str);
        return errsv;
    }
    int params_count = params_number[tmp];

    char **params_as_strings = malloc(params_count * sizeof *params_as_strings);
    unsigned long *params_as_ul = malloc(params_count * sizeof *params_as_ul);
    uint32_t *params_as_uint = malloc(params_count * sizeof *params_as_uint);
    if (params_as_strings == NULL ||
        params_as_ul == NULL ||
        params_as_uint == NULL) {
        free(params_as_strings);
        free(params_as_ul);
        free(params_as_uint);
        printERR(*line);
        errno = ENOMEM;
        return errsv;
    }

    bool params_are_correct = get_uints(params_count, params_as_strings,
                                        params_as_ul, params_as_uint);
    free(str);
    free(params_as_strings);
    free(params_as_ul);
    if (params_are_correct)
        process_command(tmp, g, params_as_uint);
    else
        printERR(*line);

    free(params_as_uint);
    return errsv;
}

/** @brief Przetwarza całość.
 */
static void parse(gamma_t *g, unsigned long long *line)
{
    bool all_is_fine = true, EOF_not_reached = true;
    while (all_is_fine && EOF_not_reached) {
        errno = 0;
        EOF_not_reached = parse_line(g, line) != - 1;
        all_is_fine = errno != ENOMEM;
    }
}

bool batch_mode(unsigned long long *line, uint32_t width, uint32_t height,
                uint32_t players, uint32_t areas)
{
    gamma_t *g = gamma_new(width, height, players, areas);
    if (!g)
        return false;
    printf("OK %llu\n", *line);

    parse(g, line);

    gamma_delete(g);
    return true;
}
