#include "find-union.h"

#include <assert.h>
#include <stdlib.h>

elem_t* make_set(elem_t* e, uint32_t player) {
  e->player = player;
  e->rank = 0;
  e->parent = e;
  return e;
}

elem_t* find(elem_t* e) {
  elem_t* ans = e;
  while (ans != ans->parent) ans = ans->parent;
  while (e != e->parent) {
    elem_t* tmp = e->parent;
    e->parent = ans;
    e = tmp;
  }
  return ans;
}

elem_t* unite(elem_t* x, elem_t* y) {
  assert(x != NULL);
  assert(y != NULL);

  elem_t* ans = x;
  if (x != y) {
    if (x->rank < y->rank) {
      x->parent = y;
      ans = y;
    } else {
      if (x->rank == y->rank) ++(x->rank);
      y->parent = x;
    }
  }
  return ans;
}

void aggregate_unite(size_t arr_size, elem_t* arr[], elem_t* e) {
  elem_t* acc = e;
  for (size_t i = 0; i < arr_size; ++i) {
    assert(arr[i] != NULL);
    acc = unite(acc, arr[i]);
  }
}
