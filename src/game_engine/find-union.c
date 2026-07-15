#include "find-union.h"
#include <stdint.h>
#include <stdlib.h>

elem_t *make_set(elem_t *e, uint32_t player)
{
    e->player = player;
    e->rank = 0;
    e->parent = e;
    return e;
}

elem_t* find(elem_t *e)
{
    elem_t *ans = e;
    while (ans != ans->parent)
        ans = ans->parent;
    while (e != e->parent) {
        elem_t *tmp = e->parent;
        e->parent = ans;
        e = tmp;
    }
    return ans;
}

elem_t *unite(elem_t *x, elem_t *y)
{
    if (x == NULL)
        return y;
    if (y == NULL)
        return x;

    elem_t *ans = x;
    if (x != y) {
        if (x->rank < y->rank) {
            x->parent = y;
            ans = y;
        } else {
            if (x->rank == y->rank)
                x->rank++;
            y->parent = x;
        }
    }
    return ans;
}
