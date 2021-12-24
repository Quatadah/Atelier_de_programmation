#include <stddef.h>
#ifndef SET_H
#define SET_H

struct set;
typedef int (*pf_t)(int);
typedef void(*print)(int);
// Return a struct set representing the empty set
struct set* set__empty(void);

// Returns non-zero if se is empty, 0 otherwise
int set__is_empty(const struct set* se);

// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, int c);

// Returns the number of elements in se
size_t set__size(const struct set *se);

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
int set__add(struct set *se, int c);

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
int set__remove(struct set *se, int c);
int is_pair(int);
int is_impair(int);

void print_line(int a);
void print_space(int a);
    
void set__debug_data(struct set *s,print p);

void set__crs_start(struct set*);
void set__crs_next(struct set*);
int set__crs_has_next(const struct set*);
int set__crs_data(const struct set*);



struct set* set__filter(pf_t f,const struct set *s);
// Frees the memory allocated for struct set se
// NB: should not free the struct set pointed by se, but only the memory
// allocated by the functions set__empty and set__add
void set__free(struct set * se);

#endif
