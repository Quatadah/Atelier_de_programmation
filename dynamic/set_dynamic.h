#ifndef SET_DYNAMIC_H
#define SET_DYNAMIC_H

#include "set.h"
#include <stdlib.h>

struct set {
  int * s;
  size_t capacity;
  size_t size;
  size_t curseur;
};

// returns the expected position of x in sorted array s with size elements. The
// returned value p is such that either s[p]==x, or s does not contain x, and x
// should be inserted in position p to keep s sorted
size_t find(int s[], size_t size, int x);

// translates elements in s[begin..end] to s[begin+1..end+1] assuming all
// the indices are valid
// s[begin] is left unchanged
void shift_right(int s[], int begin, int end);

// translates elements in s[begin..end] tp [begin-1..end-1] assuming all
// the indices are valid
// s[end] is left unchanged
void shift_left(int s[], int begin, int end);

#endif
