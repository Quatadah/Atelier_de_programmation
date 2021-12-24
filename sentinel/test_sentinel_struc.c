#include "set_sentinel.h"
#include <stdio.h>

int is_even(int x){
  return ( (x%2) == 0);
}

int always_true(){
  return 1;
}

int test__find_positive_case(){

  int const s[5] = {1,2,5,-1,-185};

  return find(s,2);
  
}

int test__find_negative_case(){

  int const s[5] = {1,2,5,-1,-185};

  return find(s,3);
  
}

int test__shift_left(){

  int s[5] = {1,2,5,-1,-2}; 

  shift_left(s,1);

  return ( (s[0] == 2) && (s[1] == 5) && (s[2] == -1) && (s[3] == -2) );
  
}

int test__shift_right(){

  int s[5] = {1,2,5,-1,-185}; 

  shift_right(s,0);

  return ( (s[0] == 1) && (s[1] == 1) && (s[2] == 2) && (s[3] == 5) && (s[4] == -1) );
  
}

int test__is_empty_on_empty_set(){

  struct set* empty = set__empty();
  
  int test_result = set__is_empty(empty);

  set__free(empty);
    
  return test_result;
    
}

int test__is_empty_on_non_empty_set(){

  struct set* empty = set__empty();
  
  set__add(empty,7);

  int test_result = set__is_empty(empty);

  set__free(empty);
  
  return test_result;

}

int test__find_in_a_positive_case(){

  struct set* s = set__empty();

  set__add(s,1);
  set__add(s,2);

  int test_result = set__find(s,2);

  set__free(s);
  
  return test_result;
  
}

int test__find_in_a_negative_case(){

  struct set* s = set__empty();

  set__add(s,1);
  set__add(s,2);

  int test_result = set__find(s,3);

  set__free(s);
  
  return test_result;
  
}

int test__set_add_with_negative_integer(){

  struct set* se = set__empty();

  int is_added = set__add(se,-5);

  int test_result = ((se->s)[0] == -1) && (is_added == -1);

  set__free(se);

  return test_result;
  
}

int test__set_add_twice(){

  struct set* se = set__empty();

  int is_added_1 = set__add(se,5);
  int is_added_2 = set__add(se,5);

  int test_result = (is_added_1 == 0) && (is_added_2 == -1) && (se->s[1] == -1);

  set__free(se);
  
  return test_result;
}

int test__set_remove_on_empty_set(){

  struct set* empty = set__empty();

  int is_removed = set__remove(empty,1);

  int test_result = (is_removed == -1) && set__is_empty(empty);

  set__free(empty);

  return test_result;
  
}

int test__set_remove_negative_integer(){

  struct set* se = set__empty();

  set__add(se,1);
  set__add(se,2);
  
  int is_removed = set__remove(se,-2);

  int test_result = (is_removed == -1) && (set__find(se,1)) && (set__find(se,2)) && ((se->s)[2] == -1);

  set__free(se);
  
  return test_result;
  
}

int test__set_remove_non_member_integer(){

  struct set* se = set__empty();

  set__add(se,1);
  set__add(se,2);
  
  int is_removed = set__remove(se,3);

  int test_result = (is_removed == -1) && (set__find(se,1)) && (set__find(se,2)) && ((se->s)[2] == -1);

  set__free(se);
  
  return test_result;
  
}

int test__set_remove_one_element(){

  struct set* se = set__empty();

  set__add(se,1);

  set__remove(se,1);

  int test_result = set__is_empty(se);

  set__free(se);
  
  return test_result;
  
}

int test__set_find_after_removing(){

  struct set* se = set__empty();

  set__add(se,1);
  set__add(se,2);
  set__add(se,3);
    
  set__remove(se,2);

  int test_result = (set__find(se,1) == 1) && (set__find(se,2) == 0) && (set__find(se,3) == 1);

  set__free(se);
  
  return test_result;
  
}


int test__set_filter_even_function(){

  struct set* se = set__empty();

  set__add(se,1);
  set__add(se,2);
  set__add(se,3);
  set__add(se,4);

  int (*pf)(int);
  pf = is_even;
  
  struct set* set_filtered = set__filter(se,pf);

  int test_result = (set__find(set_filtered,2) == 1) && (set__find(set_filtered,4) == 1);

  set__free(se);
  set__free(set_filtered);
  
  return test_result;
  
}

int test__set_filter_copy(){

  struct set* se = set__empty();

  set__add(se,1);
  set__add(se,2);
  set__add(se,3);
  set__add(se,4);

  int (*pf)(int);
  pf = always_true;
  
  struct set* set_copied = set__filter(se,pf);

  int test_result = (set__find(set_copied,1) == 1) && (set__find(set_copied,2) == 1) && (set__find(set_copied,3) == 1) && (set__find(set_copied,4) == 1);

  set__free(se);
  set__free(set_copied);
  return test_result;
  
}


int main(){

  int result__test_find_positive_case = test__find_positive_case();

  int result__test_find_negative_case = test__find_negative_case();

  int result__test_shift_left = test__shift_left();

  int result__test_shift_right = test__shift_right();

  int result__test_is_empty_on_empty_set = test__is_empty_on_empty_set(); 

  int result__test_is_empty_on_non_empty_set = test__is_empty_on_non_empty_set(); 

  int result__test_find_in_a_positive_case = test__find_in_a_positive_case();

  int result__test_find_in_a_negative_case = test__find_in_a_negative_case();

  int result__test_set_add_with_negative_integer = test__set_add_with_negative_integer();

  int result__test_set_add_twice = test__set_add_twice();

  int result__test_set_remove_on_empty_set = test__set_remove_on_empty_set();

  int result__test_set_remove_negative_integer = test__set_remove_negative_integer();

  int result__test_set_remove_non_member_integer = test__set_remove_non_member_integer();

  int result__test_set_remove_one_element = test__set_remove_one_element();

  int result__test_set_find_after_removing = test__set_find_after_removing();

  int result__test_set_filter_even_case = test__set_filter_even_function();

  int result__test_set_filter_copy_case = test__set_filter_copy();
  
  printf("Test de find in a positive case...%s\n",(result__test_find_positive_case == 1)? "PASSED" : "FAILED");
  
  printf("Test de find in a negative case...%s\n",(result__test_find_negative_case == 2)? "PASSED" : "FAILED");

  printf("Test de shif_left...%s\n",(result__test_shift_left)? "PASSED" : "FAILED");

  printf("Test de shift_right...%s\n",(result__test_shift_right)? "PASSED" : "FAILED");
  
  printf("Test de set__is_empty on an empty set...%s\n",(result__test_is_empty_on_empty_set)? "PASSED" : "FAILED"); 

  printf("Test de set__is_empty on a non-empty set...%s\n",(result__test_is_empty_on_non_empty_set)? "FAILED" : "PASSED");

  printf("Test de set__find in a positive case...%s\n",(result__test_find_in_a_positive_case)? "PASSED" : "FAILED");
  
  printf("Test de set__find in a negative case...%s\n",(result__test_find_in_a_negative_case)? "FAILED" : "PASSED");

  printf("Test de set__add with a negative integer...%s\n",(result__test_set_add_with_negative_integer)? "PASSED" : "FAILED");

  printf("Adding twice with set__add the same integer  ...%s\n",(result__test_set_add_twice)? "PASSED" : "FAILED");
  
  printf("Removing one element with set__remove on an empty set...%s\n",(result__test_set_remove_on_empty_set)? "PASSED" : "FAILED");

  printf("Removing a negative integer with set__remove...%s\n",(result__test_set_remove_negative_integer)? "PASSED" : "FAILED");

  printf("Removing a non_member integer with set__remove...%s\n",(result__test_set_remove_non_member_integer)? "PASSED" : "FAILED");
  
  printf("Removing one element with set__remove...%s\n",(result__test_set_remove_one_element)? "PASSED" : "FAILED");

  printf("Test set__find after removing one element...%s\n",(result__test_set_find_after_removing)? "PASSED" : "FAILED");
  
  printf("Test set__filter with an even selection...%s\n",(result__test_set_filter_even_case)? "PASSED" : "FAILED");
  
  printf("Test set__filter with a copy filter...%s\n",(result__test_set_filter_copy_case)? "PASSED" : "FAILED");
  
  return 0;
}
