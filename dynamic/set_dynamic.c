#include"set_dynamic.h"
#include<stdlib.h>
#include<stdio.h>

size_t find(int s[],size_t size,int x)
{
  if (size==0 || s[0]>=x)
    return 0;
  size_t d=0;
  size_t f=size-1;
  size_t m;
  while (d<=f)
    {
      m=(d+f)/2;
      if (s[m]==x)
	return m;
      else if (s[m]<x)
	d=m+1;
      else
	f=m-1;
    }
  if (s[m]<x)
    return m+1;
  else
    return m;
}

void shift_right(int s[],int begin,int end)
{
  int i;
  for (i=end+1;i>=begin+1;i--)
    s[i]=s[i-1];
}

void shift_left(int s[],int begin,int end)
{
  int i;
  for (i=begin-1;i<=end-1;i++)
    s[i]=s[i+1];
}

struct set* set__empty(void)
{
  struct set* set = malloc(sizeof(struct set));
  set->size=0;
  set->capacity=1;
  set->s=malloc(set->capacity*sizeof(int));
  if (set->s==NULL)
    {
      fprintf(stderr,"Allocation impossible");
      exit(EXIT_FAILURE);
    }
  return set;
}

int set__is_empty(const struct set* se)
{
  if (se->size==0)
    return 1;
  else
    return 0;
}

int set__find(const struct set *se, int c)
{
  if (se->size==0)
    return 0;
  return (find(se->s,se->size,c)<se->size && se->s[find(se->s,se->size,c)]==c);
}

size_t set__size(const struct set *se)
{
  return se->size;
}

int set__add(struct set *se, int c)
{
  if (se==NULL || c<0 )
    return -1;
  else
    {
      if (se->size==se->capacity)
	{
	  se->capacity*=2;
	  se->s=realloc(se->s,sizeof(int)*se->capacity);
	  if (se->s==NULL)
	    {
	      fprintf(stderr,"Reallocation impossible");
	      exit(EXIT_FAILURE);
	    }
	  
	}
      size_t i=find(se->s,se->size,c);
      if (se->size!=0 && i<se->size && se->s[i]==c)
	return -1;
      shift_right(se->s,i,se->size-1);
      se->s[i]=c;
      se->size++;
      return 0;
    }
}


int set__remove(struct set *se, int c)
{
  if (se==NULL)
    return -1;
  else
    {
      size_t i=find(se->s,se->size,c);
      if (i>=se->size || se->s[i]!=c)
	return -1;
      shift_left(se->s,i+1,se->size-1);
      se->size--;
      if (se->size<se->capacity/2)
	{
	  se->capacity/=2;
	  se->s=realloc(se->s,sizeof(int)*se->capacity);
	}
      return 0;
    }
}


 void set__free(struct set * s)
 {
   free(s->s);
   free(s);
 }

int is_pair(int i)
{
  return (i%2==0);
}

int copy(int i)
{
  if (i!=0)
    return i;
  return 1;
}

int impair(int i)
{
  return (i%2==1);
}


struct set* set__filter(pf_t pf,const struct set* s)
{
  struct set* p=set__empty();
  size_t i;
  for (i=0;i<s->size;i++)
    {
      if (pf(s->s[i]))
	set__add(p,s->s[i]);
    }
  return p;
}

void set__crs_start(struct set* s)
{
  s->curseur=0;
}
  
void set__crs_next(struct set* s)
{
  s->curseur++;
}

int set__crs_has_next(const struct set* s)
{
  return (s->curseur<s->size);
}

int set__crs_data(const struct set* s)
{
  return s->s[s->curseur];
}

void set__debug_data(void (*print)(int),struct set *s)
{
  set__crs_start(s);
  while (set__crs_has_next(s))
    {
      print(set__crs_data(s));
      set__crs_next(s);
    }
}

void print_retour_ligne(int i)
{
  printf("%d\n",i);
}

void print_espace(int i)
{
  printf("%d   ",i);
}

void print_virgule(int i)
{
  printf("%d;",i);
}
