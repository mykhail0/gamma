/** @file
 * Implementacja @ref interactive-mode.h
 *
 * @author Mykhailo Shevchenko <ms420826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.05.2020
 */

#include "interactive-mode.h"
#include "../../game_engine/gamma.h"
#include "../text_lib/strings.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

/** @brief Rekord opisujący położenie kursora.
 */
struct cursor {
    unsigned long line; ///< Linijka, gdzie jest kursor.
    unsigned long col; ///< Kolumna, gdzie jest kursor.
};

/** @brief Współrzędne kursora.
 */
static struct cursor cursor;

/** @brief Liczba współrzędnych na planszy, kursora.
 */
#define COORDS_COUNT 2

/** @brief Wysokość planszy.
 */
static unsigned long HEIGHT;

/** @brief Szerokość planszy.
 */
static unsigned long WIDTH;

/** @brief Szerokość kolumny.
 */
static unsigned COLUMN_WIDTH;

/** @brief Pomocniczy buforek do nadpisywania komórek planszy.
 */
char *buffer;

/** @brief Przesuwa kursor na daną pozycję na ekranie.
 */
static inline void move_cursor(struct cursor x)
{
    printf("\033[%lu;%luH", x.line, x.col);
}

/** @brief Konwertuje współrzędne kursora na
 * współrzędne planszy dla @ref gamma_move.
 */
static void cursor_to_pos(uint32_t *x, uint32_t *y)
{
    *y = HEIGHT - cursor.line;
    *x = cursor.col / COLUMN_WIDTH - 1;
}

/** @brief Przesuwa kursor do tyłu.
 */
static void cursorBack()
{
    if (cursor.col == COLUMN_WIDTH)
        return;
    cursor.col -= COLUMN_WIDTH;
}

/** @brief Przesuwa kursor w dół.
 */
static void cursorDown()
{
    if (cursor.line == HEIGHT)
        return;
    cursor.line++;
}

/** @brief Przesuwa kursor do góry.
 */
static inline void cursorUp()
{
    if (cursor.line == 1)
        return;
    cursor.line--;
}

/** @brief Przesuwa kursor do przodu.
 */
static void cursorForward()
{
    if (cursor.col == WIDTH)
        return;
    cursor.col += COLUMN_WIDTH;
}

/** @brief Aktualizuje linijkę zachęcającą do grania.
 * @return `true` wtw gdy linijka zaktualizowana,
 * czyli gracza `player` może wykonać ruch.
 */
static bool update_player(gamma_t *g, uint32_t player)
{
    return gamma_golden_possible(g, player) || gamma_free_fields(g, player);
}

/** @brief Zwraca numer następnego gracza.
 */
static inline int increment_player(gamma_t *g, uint32_t player)
{
    return player == g->players_number ? 1 : player + 1;
}

/** @brief Ustawia stałe dla danej instancji planszy.
 */
static void initialize_seq(gamma_t *g)
{
    // Wyłącza miganie kursora.
    printf("\033[?25l");
    // Wyłącza możliwość skrolowania w terminalu dla użytkownika.
    printf("\033[?1049h");

    COLUMN_WIDTH = count_digits((unsigned long) g->players_number);
    if (COLUMN_WIDTH > 1)
        COLUMN_WIDTH += 1;

    HEIGHT = g->height;
    WIDTH = COLUMN_WIDTH * g->width;

    buffer = malloc((COLUMN_WIDTH + 1) * sizeof *buffer);
    if (buffer == NULL) {
        errno = ENOMEM;
        return;
    }

    unsigned long width = g->width == 1 ? 1 : g->width / 2;
    cursor.col = COLUMN_WIDTH * width;
    cursor.line = HEIGHT == 1 ? 1 : HEIGHT / 2;
}

/** @brief Wypisuje statystykę gracza.
 */
static void print_player_stats(gamma_t *g, uint32_t player)
{
    printf("PLAYER %" PRIu32 ": ", player);
    printf("busy fields - %" PRIu64, gamma_busy_fields(g, player));

    printf(", areas - ");
    if (g->areas[player - 1] == g->areas_number)
    //na czerwono
        printf("\033[31m");
    printf("%" PRIu32 "/%" PRIu32, g->areas[player - 1], g->areas_number);
    if (g->areas[player - 1] == g->areas_number)
        printf("\033[m");

    if (g->golden_not_used[player - 1])
        printf(" and did not use golden move");
}

/** @brief Wypisuje planszę i zachętę dla gracza `player`.
 */
static void print_board(gamma_t *g, uint32_t player)
{
    if (g == NULL)
        return;

    uint32_t cursorX, cursorY;
    cursor_to_pos(&cursorX, &cursorY);

// Czyść ekran, przesuń się w lewy górny róg.
    printf("\033[2J\033[H");
    for (uint32_t i = 0; i < g->height; ++i) {
        for (uint32_t j = 0; j < g->width; ++j) {
            sprintf(buffer, "%*" PRIu32, COLUMN_WIDTH, g->board[i][j]->player);
            if (g->board[i][j]->player == 0)
                buffer[COLUMN_WIDTH - 1] = '.';

            if (g->height - i - 1 == cursorY && j == cursorX)
                printf("\033[7m"); // jeśli tam jest kursor to reverse video
            if (g->board[i][j]->player == player)
                printf("\033[32m"); // na zielono

            printf("%s", buffer);

            if (g->height - i - 1 == cursorY && j == cursorX)
                printf("\033[m");
            if (g->board[i][j]->player == player)
                printf("\033[m");
        }
        printf("\n");
    }
    print_player_stats(g, player);
    move_cursor(cursor);
}

/** @brief Obsługuje strzałkę, albo inne polecenie od gracza.
 * @param[in] g              - stan gry,
 * @param[in] player         - wskaźnik na numer gracza wykonującego ruch,
 * @param[in] ch             - wskaźnik na kod znaku, który trzeba zinterpretować,
 * @param[in] EOT_reached    - tu zapisywana informacja, czy ctrl+D zostało napotkane,
 * @param[in] unfinishedANSI - tu zapisywana informacja, czy `ch` trzeba aktualizować,
 *                             po wywołaniu `make_move`.
 * @return `true` wtw gdy zaktualizowany po wywołaniu tej funkcji `player`
 * może wykonać ruch.
 */
static bool make_move(gamma_t *g, uint32_t *player, int *ch, bool *EOT_reached,
                      bool *unfinishedANSI)
{
    *unfinishedANSI = false;
    bool ans = true;
    uint32_t x, y;
    cursor_to_pos(&x, &y);
    if (*ch == '\4') {
        *EOT_reached = true;
        return false;
    }
    if (*ch == 'c' || *ch == 'C') {
        *player = increment_player(g, *player);
        return update_player(g, *player);
    }
    if (*ch == 'g' || *ch == 'G') {
        if (gamma_golden_move(g, *player, x, y)) {
            *player = increment_player(g, *player);
            ans = update_player(g, *player);
        }
        return ans;
    }
    if (*ch == ' ') {
        if (gamma_move(g, *player, x, y)) {
            *player = increment_player(g, *player);
            ans = update_player(g, *player);
        }
        return ans;
    }

    if (*ch == '\033') {
        *ch = getchar();
        if (*ch == EOF) {
            errno = EINVAL;
            return false;
        }

        if (*ch ==  '[') {
            *ch = getchar();
            if (*ch == EOF) {
                errno = EINVAL;
                return false;
            }

            if (*ch == 'A')
                cursorUp();
            if (*ch == 'B')
                cursorDown();
            if (*ch == 'C')
                cursorForward();
            if (*ch == 'D')
                cursorBack();
            if (*ch < 'A' || 'D' < *ch)
                *unfinishedANSI = true;
        } else {
            *unfinishedANSI = true;
        }
    }
    return ans;
}

/** @brief Obsługa kolejnych znaków ze strony graczy.
 */
static void play(gamma_t *g)
{
    uint32_t player = 1, last_player = 0;
    bool player_can_move = update_player(g, player);
    bool EOT_reached = false, game_finished = false, unfinishedANSI = false;
    int c;
    print_board(g, player);

    while (!EOT_reached && !game_finished) {
        if (player_can_move) {
            last_player = player;
            if (!unfinishedANSI) {
                c = getchar();
                if (c == EOF) {
                    errno = EINVAL;
                    return;
                }
            }

            player_can_move = make_move(g, &player, &c, &EOT_reached, &unfinishedANSI);
            if (errno == EINVAL) {
                errno = EINVAL;
                return;
            }
        } else {
            player = increment_player(g, player);
            player_can_move = update_player(g, player);
        }

        print_board(g, player);
        game_finished = !player_can_move && player == last_player - 1;
    }
}

/** @brief Wypisuje statystyki graczy na koniec rozgrywki.
 */
static void print_summary(gamma_t *g)
{
    // Czyść ekran, przesuń się w lewy górny róg.
    printf("\033[2J\033[H");

    // Jeśli zabraknie pamięci, to najwyżej nie wypisze planszy.
    char *s = gamma_board(g);
    printf("%s", s);
    free(s);

    printf("\033[2K");
    for (uint32_t player = 0; player++ < g->players_number;) {
        print_player_stats(g, player);
        printf("\n");
    }
}

/** @brief Zwalnia pamięć po trybie interaktywnym
 */
static void free_memory(gamma_t *g)
{
    free(buffer);
    gamma_delete(g);
}

/** @brief Przywraca kilka drobnych rzeczy terminalowi.
 */
static void finishing_seq()
{
    // Włącza z powrotem możliwość skrolowania w terminalu dla użytkownika.
    printf("\033[?1049l");
    // Przywraca kursor.
    printf("\033[?25h");
}

/** @brief Uruchamia `interactive`.
 * @return `true` wtw gdy się udało przeprowadzić rozgrywkę.
 */
static bool interact(gamma_t *g)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    errno = 0;
    initialize_seq(g);
    int errsv = errno;
    if (errsv == ENOMEM || w.ws_row < HEIGHT || w.ws_col < WIDTH) {
        finishing_seq();
        free_memory(g);
        if (w.ws_row < HEIGHT || w.ws_col < WIDTH)
            puts("Please, resize your terminal window and make it bigger.");
        errno = errsv;
        return false;
    }

    errno = 0;
    play(g);
    if (errno == EINVAL) {
        finishing_seq();
        free_memory(g);
        errno = EINVAL;
        return false;
    }

    finishing_seq();
    print_summary(g);
    free_memory(g);
    return true;
}

bool interactive_mode(uint32_t width, uint32_t height,
                      uint32_t players, uint32_t areas)
{
    gamma_t *g = gamma_new(width, height, players, areas);
    if (!g)
        return false;

    struct termios oldt, newt;
    if (tcgetattr(STDIN_FILENO, &oldt) == - 1) {
        gamma_delete(g);
        return false;
    }

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) == - 1) {
        gamma_delete(g);
        return false;
    }

    errno = 0;
    interact(g);
    int errsv = errno;

    if (errsv) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        errno = errsv;
        return false;
    }

    if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) == - 1)
        return false;
    return true;
}
