#include "set_sentinel.h"

int find(int const s[], int c){

  int i=0;
  int position=0;
  
  
  while (s[i] != SET__BOUND){
    
    if (s[i] == c){
      return i;
    }

    if (c > s[i]){
      position = i+1;
    }

    ++i;

  }

  return position;
}

void shift_right(int s[], int begin){

  int k = 0;

  while (s[k] != SET__BOUND){
    ++k;
  }
  
  for (int i=k+1 ; i > begin ; --i){
    s[i] = s[i-1];
  }
  
}

void shift_left(int s[],int begin){

  int i=0;

  while (s[i] != SET__BOUND){
    ++i;
  }

  //i now contains the position of the set_bound in s

  for (int k=begin-1 ; k < i ; ++k){
    s[k] = s[k + 1];
  }

  s[i] = -2;
  
}

struct set* set__empty(){

  struct set* empty = malloc(sizeof(*empty));
  empty->s[0] = -1;

  for (int i=1 ; i < SET__SIZE ; ++i){
    //-2 is an arbitrary value to distinguish with the sentinel
    empty->s[i] = -2;
  }
 
  return empty;

}

int set__is_empty(const struct set*se){

  return ( (se->s)[0] == -1 );
  
}

int set__find(const struct set* se, int c){

  size_t position = find( (se->s), c );

  return ( (se->s)[position] == c );
  
}

size_t set__size(const struct set* se){

  int i=0;

  while ( (se->s)[i] != -1 ){
    ++i;
  }

  return i;
  
}

int set__add(struct set* se, int c){
  
  if ( (c<0) || ( (se->s)[SET__SIZE - 1] == -1 ) ){
    return -1;
  }
  
  size_t position = find( (se->s),c );
  
  if ( (se->s)[position] != c ){
    shift_right( (se->s),position);
    (se->s)[position] = c;
    return 0;
  }
  
  return -1;
  
}

int set__remove(struct set* se, int c){

  if ( (c < 0) || set__is_empty(se) ){ 
    return -1;
  }
  
  size_t position = find( (se->s),c );

  if ( (se->s)[position] == c ){
      shift_left( (se->s),position+1 );
      return 0;
  }
  
  return -1;
  
}

void set__free(struct set* se){

  free(se);
  
}

struct set* set__filter(const struct set* s, pf_t f){

  struct set* s_res = set__empty();

  int i = 0;

  while (s->s[i] != SET__BOUND){
    if ( f(s->s[i]) ) {
      set__add(s_res,s->s[i]);
    }
    ++i;
  }

  return s_res;
  
}
