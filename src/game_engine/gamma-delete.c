#include "gamma-struct.h"
#include "gamma-delete.h"
#include <stdlib.h>
#include <stdint.h>

void visited_delete(gamma_t *g)
{
    if (g->visited == NULL)
        return;
    for (uint32_t i = 0; i < g->height; ++i)
	free(g->visited[i]);
    free(g->visited);
}

void board_delete(gamma_t *g)
{
    if (g->board == NULL)
        return;
    for (uint32_t i = 0; i < g->height; ++i) {
        if (g->board[i] != NULL) {
            for (uint32_t j = 0; j < g->width; ++j)
                free(g->board[i][j]);
            free(g->board[i]);
        }
    }
    free(g->board);
}
