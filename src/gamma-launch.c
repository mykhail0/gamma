/** @file
 * Implementacja @ref gamma-launch.h.
 *
 * @author Mykhailo Shevchenko <ms420826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.05.2020
 */

/** @brief To dla getline
 */
#define _GNU_SOURCE

#include "gamma-launch.h"
#include "UI/error-handling.h"
#include "UI/batch_mode/batch-mode.h"
#include "UI/interactive_mode/interactive-mode.h"
#include "UI/text_lib/strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/** @brief Liczba parametrów dla trybu gry.
 */
#define PARAMS_COUNT 4

/** @brief Możliwe tryby gry.
 */
enum Mode {
    NOMODE,
    BATCH,
    INTERACTIVE
};

/** @brief Przeprowadza rozgrywkę.
 * @param[in] mode    - tryb gry,
 * @param[in] line    - wskaźnik na linijkę, jeśli jest grany `batch`
 *                      to wartość jest aktualizowana,
 * @param[in] width   - szerokość planszy,
 * @param[in] height  - wysokość planszy,
 * @param[in] players - liczba graczy,
 * @param[in] areas   - liczba dozwolonych obszarów.
 * @return `true` wtw gdy rozgrywka została przeprowadzona.
 */
static bool play_game(enum Mode mode, unsigned long long *line,
                      uint32_t width, uint32_t height,
                      uint32_t players, uint32_t areas)
{
    switch (mode) {
    case NOMODE:
        return false;
        break;
    case BATCH:
        return batch_mode(line, width, height, players, areas);
        break;
    case INTERACTIVE:
        return interactive_mode(width, height, players, areas);
        break;
    }
    return false;
}

/** @brief Analizuje parametry dla podanego trybu.
 * Przeprowadza rozgrywkę, jeśli parametry są poprawne.
 * @param[in] mode    - tryb gry,
 * @param[in] line    - wskaźnik na linijkę, jeśli jest grany `batch`
 *                      to wartość jest aktualizowana,
 * @return `true` wtw gdy rozgrywka została przeprowadzona.
 */
static bool load_game(enum Mode mode, unsigned long long *line) {
    char *params_as_strings[PARAMS_COUNT];
    unsigned long params_as_ul[PARAMS_COUNT];
    uint32_t params_as_uint[PARAMS_COUNT];

    bool ans = get_strings(PARAMS_COUNT, params_as_strings);
    if (ans)
        ans = stringArr_to_ulArr(PARAMS_COUNT, params_as_strings, params_as_ul);
    if (ans)
        ans = ulArr_to_uintArr(PARAMS_COUNT, params_as_ul, params_as_uint);
    if (ans)
        ans = play_game(mode, line,
                        params_as_uint[0], params_as_uint[1],
                        params_as_uint[2], params_as_uint[3]);

    if (!ans)
        printERR(*line);
    return ans;
}

void launch_game() {
    bool game_played = false;
    unsigned long long line_number = 1;
    char *line = NULL;
    size_t line_size = 0;
    ssize_t errsv = getline(&line, &line_size, stdin);

    while (errsv != - 1 && !game_played) {
        int mode = NOMODE;

// Mogę zcastować bo errsv != -1
        if ((size_t) errsv == strlen(line)) {
            char *firstWord = strtok(line, whiteSpaces);
            if (firstWord != NULL) {
                if (strcmp(firstWord, "B") == EQUAL && line[0] == 'B')
                    mode = BATCH;
                if (strcmp(firstWord, "I") == EQUAL && line[0] == 'I')
                    mode = INTERACTIVE;
            }
            if (mode == NOMODE && line[0] != '#' && line[0] != '\n')
                printERR(line_number);
        } else {
            printERR(line_number);
        }

        if (mode != NOMODE) {
            errno = 0;
            game_played = load_game(mode, &line_number);
            if (errno) {
                free(line);
                exit(1);
            }
        }

        if (!game_played)
            errsv = getline(&line, &line_size, stdin);
        line_number++;
    }

    free(line);
}
