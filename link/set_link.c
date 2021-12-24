#include <stdio.h>
#include <stdlib.h>
#include "set_link.h"
#include "link.h"

// returns a pointer to the cell e in l such that:
// - either the next cell of e (i.e. e->next) has data x,
// - or l does not contain x, and x should be added after cell e to keep
// the list l sorted
// returns NULL if x should be added to the head of list l to keep l sorted

struct lelement * find(struct link * l, int x) // ({2,3,SETINELL},3)
{
  if(l->head == SENTINEL ||  x <= l->head->data)
    return NULL;

  struct lelement *currentElement = l->head;
  while(currentElement->next != SENTINEL && currentElement->next->data < x) // {10,20,30,SENTINEL} , 35
    currentElement = currentElement->next;
  return currentElement;
}

struct set *set__empty()
{
    struct link *l = malloc(sizeof(*l));
    struct set *se = malloc(sizeof(*se));
    if( l == NULL || se == NULL)
    {
        printf("Error in dynamic allocation.\n");
        exit(EXIT_FAILURE);
    }
    *l = lnk__empty();
    se->l = l;
    return se;
}

int set__is_empty(const struct set* se)
{
    return se->l->head == SENTINEL;
}

// Returns non-zero if c belongs to se, 0 otherwise
int set__find(const struct set *se, int c) // set__find( &{1,sentinel},1)
{
  if (find(se->l,c) == NULL)
    return se->l->head->data == c;
  else
      return find(se->l,c)->next->data == c;
}

size_t set__size(const struct set *se)
{
  int s=0;
  struct lelement *e=se->l->head;
  while (e!=&sentinel)
    {
      s++;
      e=e->next;
    }
  return s;
}

// Adds c to se
// Returns 0 if c has been added to se, a negative value otherwise
// NB: se should not be modified if c cannot be added to se
int set__add(struct set *se, int c)
{
  if (c<0)
    return -1;
  if ( se == NULL )//|| set__find(se,c))
    return -1;
  
  struct lelement *f = malloc(sizeof(*f));
  if (f==NULL)
	{
	  printf("allocation impossible\n");
	  exit(EXIT_FAILURE);
  }

  f->data = c; 
  struct lelement *e = find(se->l,c);  //{2,3,SENTINEL}
  if(e == NULL)
  {
    if(lnk__first(se->l)->data == c)
    {
      free(f);
      return -1;
    }
  }
  else
  {
    if(e->next->data == c)
    {
      free(f);
      return -1;
    }
  }
  if (e != NULL)
  {
    lnk__add_after(se->l,e,f);
  }
  else
    lnk__add_head(se->l,f);
  return 0;
    
}

// Removes c from se
// Returns 0 if c has been removed from se, a negative value otherwise
// NB: se should not be modified if c cannot be removed from se
int set__remove(struct set* se, int c)
{
  if(set__is_empty(se))
    return -1;
  struct lelement *currentCell = find(se->l,c);
  if (currentCell==NULL)
  {
    if (lnk__first(se->l)->data != c)
      return -1;
  }
  else
  {
    if (currentCell->next->data != c)
      return -1;
  }
  struct lelement *toRemove;
  
  if(currentCell == NULL)
    toRemove = lnk__remove_head(se->l);
  else
    toRemove = lnk__remove_after(se->l,currentCell);
  free(toRemove);
  return 0;
}
int is_pair(int x){
  return x%2==0;
}

int is_impair(int x){ return x%2==1;}



struct set* set__filter(pf_t f,const struct set *s)
{
  struct set *newSet = set__empty();
  struct lelement *currentElement = s->l->head;
  while(currentElement!=SENTINEL)
  {
    if(f(currentElement->data))
      set__add(newSet,currentElement->data);
    currentElement = currentElement->next;
  }
  return newSet;
}

void print_line(int a){
  printf("%d\n",a);
}

void print_space(int a){
  printf(" %d ",a);
}



void set__crs_start(struct set* se){
  se->cursor = lnk__first(se->l);
}

void set__crs_next(struct set *se){
  if (set__crs_has_next(se))
    se->cursor = se->cursor->next;
}

int set__crs_has_next(const struct set *se){
  if (se->cursor != SENTINEL && se->cursor->next != NULL)
    return 1;
  return 0;
}

int set__crs_data(const struct set* se){
  return se->cursor->data;
}

void set__debug_data(struct set *s,print p){
  set__crs_start(s);
  while(set__crs_has_next(s)){
    p(set__crs_data(s));
    set__crs_next(s);
  }
}

void set__free(struct set *se)
{
  struct lelement *toDelete = se->l->head;
  struct lelement *next;
  while(toDelete->next != toDelete)
  {
    next = toDelete->next;
    free(toDelete);
    toDelete = next;
  }
  free(se->l);
  free(se);
}
