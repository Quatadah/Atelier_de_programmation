#ifndef SET_LINK_H
#define SET_LINK_H

#include "link.h"

struct set {
  struct link * l;
  struct lelement *cursor;
};

#include "set.h"

// returns a pointer to the cell e in l such that:
// - either the next cell of e (i.e. e->next) has data x,
// - or l does not contain x, and x should be added after cell e to keep
// the list l sorted
// returns NULL if x should be added to the head of list l to keep l sorted
struct lelement * find(struct link * l, int x);

#endif
