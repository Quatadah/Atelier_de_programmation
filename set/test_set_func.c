#include <stdio.h>

#if defined SENTINEL
#include "set_sentinel.h"
#elif defined DYNAMIC
#include "set_dynamic.h"
#elif defined LINK
#include "set_link.h"
#else
#error "A set implementation has to be defined"
// -Wfatal-errors
#endif

#define TESTCASE(msg, f) printf("%s...%s\n", msg, f() ? "PASSED" : "FAILED")

int test__set__is_empty_on_empty_set()
{
  struct set *s1 = set__empty();
  int x = set__is_empty(s1);
  set__free(s1);
  return x;
}

int test__set__is_empty_on_non_empty_set()
{
  struct set *s2 = set__empty();
  set__add(s2, 1);
  set__add(s2, 17);
  int x =! set__is_empty(s2);
  set__free(s2);
  return x;
}


int test_set__add()
{
  struct set *se=set__empty();
  set__add(se,2);
  set__add(se,3);
  int x = (set__find(se,2) && set__find(se,3) && set__add(se,2)==-1);
  set__free(se);
  return x;  
}



int main()
{
  TESTCASE("Test de set__is_empty on empty set",
            test__set__is_empty_on_empty_set);
  TESTCASE("Test de set__is_empty on non empty set",
            test__set__is_empty_on_non_empty_set);
  TESTCASE("Test de set__add",test_set__add);
  return 0;
}
