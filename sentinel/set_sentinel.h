#ifndef SET_SENTINEL_H
#define SET_SENTINEL_H

#ifndef SET__SIZE
#define SET__SIZE 10
#endif

#define SET__BOUND (-1)  // sentinel

struct set {
  int s[SET__SIZE];
};

#include "set.h"
#include <stdlib.h>

// returns the expected position of c in sorted array s. The returned value
// p is such that either s[p]==c, or s does not contain c and c should be
// inserted in position p to keep s sorted
int find(int const s[], int c);

// translates elements in s[begin..end] to s[begin+1..end+1] assuming all
// the indices are valid. The value in s[begin] is left unchanged.
// The index end is the position of the sentinel SET__BOUND in s
void shift_right(int s[], int begin);

// translates elements in s[begin..end] to [begin-1..end-1] assuming all
// the indices are valid. The value in s[end] is left unchanged
// The index end is the position of the sentinel SET__BOUND in s
void shift_left(int s[], int begin);

#endif
