#include<assert.h>
#include<stdio.h>

#include"set_dynamic.h"

static void test_find(void)
{
  printf("%s",__func__);
  int s[5]={1,2,3,4,5};
  assert(find(s,5,3)==2);
  assert(find(s,5,8)==5);
  int t[5]={2};
  assert(find(t,1,1)==0);
  assert(find(t,1,3)==1);
  printf("\tPASSED\n");
}

static void test_shift_right(void)
{
  printf("%s",__func__);
  int s[5]={1,2,3,4,5};
  shift_right(s,1,3);
  assert(s[0]==1);
  assert(s[1]==2);
  assert(s[2]==2);
  assert(s[3]==3);
  assert(s[4]==4);
  printf("\tPASSED\n");
}

static void test_shift_left(void)
{
  printf("%s",__func__);
  int s[5]={1,2,3,4,5};
  shift_left(s,1,3);
  assert(s[0]==2);
  assert(s[1]==3);
  assert(s[2]==4);
  assert(s[3]==4);
  assert(s[4]==5);
  printf("\tPASSED\n");
}

static void test_set__is_empty(struct set *s)
{
  printf("%s",__func__);
  assert(set__is_empty(s)==1);
  assert(set__find(s,5)==0);
  set__add(s,5);
  assert(set__is_empty(s)==0);
  printf("\tPASSED\n");
}

static void test_set__find(struct set *s)
{
  printf("%s",__func__);  
  assert(set__find(s,5)==1);
  printf("\tPASSED\n");
}

static void test_set__add(struct set *s)
{
  printf("%s",__func__);    
  set__add(s,2);
  set__add(s,8);
  set__add(s,4);
  assert(s->capacity==4);
  assert(set__size(s)==4);
  assert(set__find(s,8)==1);
  printf("\tPASSED\n");
}

static void test_set__remove(struct set *s)
{
  printf("%s",__func__);    
  set__remove(s,2);  
  assert(set__find(s,2)==0);
  assert(set__find(s,4)==1);
  assert(set__size(s)==3);
  set__remove(s,8);
  printf("\tPASSED\n");
}


static void test_set__filtrer_pair()
{
  printf("%s",__func__);
  struct set *s=set__empty();
  set__add(s,1);
  set__add(s,2);
  set__add(s,3);
  set__add(s,4);
  struct set *n=set__filter(is_pair,s);
  assert(n->size==2);
  assert(n->s[0]==2);
  assert(n->s[1]==4);
  printf("\tPASSED\n");
  set__free(s);
  set__free(n);
}

static void test_set_filtrer_impair()
{
 printf("%s",__func__);
  struct set *s=set__empty();
  set__add(s,1);
  set__add(s,2);
  set__add(s,3);
  set__add(s,4);
  struct set *n=set__filter(impair,s);
  assert(n->size==2);
  assert(n->s[0]==1);
  assert(n->s[1]==3);
  printf("\tPASSED\n");
  set__free(s);
  set__free(n);
} 
  
static void test_set_filtrer_copy()
{
  printf("%s",__func__);
  struct set *s=set__empty();
  set__add(s,1);
  set__add(s,2);
  struct set *n=set__filter(copy,s);
  assert(n->size==2);
  assert(n->s[0]==1);
  assert(n->s[1]==2);
  printf("\tPASSED\n");
  set__free(s);
  set__free(n);
} 
  
static void test_set__debug_data()
{
  printf("%s\n",__func__);
  struct set *s=set__empty();
  set__add(s,1);
  set__add(s,2);
  set__debug_data(print_espace,s);
  printf("\n");
  set__debug_data(print_virgule,s);
  printf("\n");
  set__debug_data(print_retour_ligne,s);
  printf("\n");
  set__free(s); 
}

int main()
{
  printf("%s\n",__FILE__);
  test_find();
  test_shift_right();
  test_shift_left();
  struct set *s=set__empty();
  test_set__is_empty(s);
  test_set__find(s);
  test_set__add(s);
  test_set__remove(s);
  set__free(s);
  test_set__filtrer_pair();
  test_set_filtrer_impair();
  test_set_filtrer_copy();
  test_set__debug_data();
  return 0;
}
