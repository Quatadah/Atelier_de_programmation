#ifndef LINK_H
#define LINK_H

struct lelement {
  int data;
  struct lelement *next;
};

struct link {
  struct lelement *head;
};

extern const struct lelement sentinel;

#define SENTINEL ((struct lelement *) &sentinel)

// returns an empty linked list
struct link lnk__empty(void);

// adds cell e at the head of linked list l
void lnk__add_head(struct link * l, struct lelement * e);

// removes and returns the first cell of linked list l
// returns NULL on failure
struct lelement * lnk__remove_head(struct link * l);

// adds cell e after cell b in liked list l
// we assume that b is a cell in l.
// returns 0 on success, another value on failure
int lnk__add_after(struct link * l, struct lelement * b, struct lelement * e);

// removes and returns the cell after b in linked list l
// we assume that b is a cell of linked list l
// returns NULL on failure, a valid cell address on success
struct lelement * lnk__remove_after(struct link * l, struct lelement * b);

// returns a pointer to the first cell in linked list l
struct lelement * lnk__first(const struct link * l);

// returns non-zero if e is the sentinel, zero otherwise
int llm__is_end_mark(const struct lelement * e);

// returns a pointer to the next cell of cell e
struct lelement * llm__next(const struct lelement * e);

#endif
