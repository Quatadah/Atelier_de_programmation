#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "set_link.h"

#define TESTFUNC(msg,testFunction) printf("%s ... %s\n",msg,testFunction() ? "PASSED" : "FAILED")

void print_set(struct set *se)
{
    struct lelement *currentElement = lnk__first(se->l);
    while(currentElement != SENTINEL)
    {
        printf(" %d -> ",currentElement->data);
        currentElement = currentElement->next;
    }
    printf("SENTINEL\n");
}

int test_lnk__empty(void)
{
    struct link l = lnk__empty();
    if (l.head == &sentinel)
        return 1;
    return 0;
}


int test_lnk__add_head()
{
    struct lelement e = {.data=5};
    struct lelement ee = {.data=6};
    struct link l = lnk__empty();
    lnk__add_head(&l,&e);
    lnk__add_head(&l,&ee);
    if (l.head->data == ee.data && l.head->next->data == e.data)
            return 1;
    return 0;
}

int test_lnk__remove_head()
{
    struct link l = lnk__empty();
    struct lelement e = {.data=10} ;
    lnk__add_head(&l,&e);
    struct lelement ele = *lnk__remove_head(&l);
    return ele.data==e.data && l.head == &sentinel;
}

int test_lnk__add_after()
{
    struct link l = lnk__empty();
    struct lelement e ={.data = 20};
    struct lelement a ={.data = 30}; // {20,SENTINEL}
    struct lelement b ={.data = 40};
    
    lnk__add_head(&l,&e);
    lnk__add_after(&l,&e,&a);
    lnk__add_after(&l,&a,&b);
    return l.head->next == &a;
}

int test_lnk__remove_after()
{
    struct link l = lnk__empty();
    struct lelement e={.data = 30};
    struct lelement ee={.data = 40};
    lnk__add_head(&l,&e);
    lnk__add_head(&l,&ee);
    return lnk__remove_after(&l,&ee) == &e && l.head->next == &sentinel ;

}

int test_lnk__first()
{
    struct link l = lnk__empty();
    struct link m = lnk__empty();
    struct lelement e;
    lnk__add_head(&l,&e);
    return lnk__first(&l) == &e && lnk__first(&m) ==&sentinel;
}

int test_llm__is_end_mark()
{
    struct link l = lnk__empty();
    return llm__is_end_mark(l.head);
}

int test_llm__next()
{
    struct link l = lnk__empty();
    struct lelement e,ee;
    lnk__add_head(&l,&e);
    lnk__add_head(&l,&ee);
    return llm__next(&ee)==&e && llm__next(&e)==&sentinel;
}

int test__find()
{
    struct link l1 = lnk__empty();
    struct lelement e1 = {.data=30};
    struct lelement e2 = {.data=20};
    struct lelement e3 = {.data=10};
    lnk__add_head(&l1,&e1);  //{30}
    lnk__add_head(&l1,&e2);  //{20,30}
    lnk__add_head(&l1,&e3); // {10,20,30}
    return (find(&l1,15) == &e3 && find(&l1,20) == &e3 && find(&l1,5)==NULL) && find(&l1,35)==&e1;
}


int test__is_empty_on_empty_set(){
  struct set *se = set__empty();
  int x = set__is_empty(se);
  set__free(se);
  return x;
}


int test__is_empty_on_non_empty_set(){
    struct set *se = set__empty();
    set__add(se,1);
    int x = set__is_empty(se) == 0;
    set__free(se);
    return x;
}


int test__find_on_positive_case(){
    struct set *empty = set__empty();
    set__add(empty,4);
    //return find(empty.l,4)==NULL;
    //return empty.l->head->data == 4;
    int x= set__find(empty,4);
    set__free(empty);
    return x;
}

int test__find_on_negative_case(){
  struct set *empty = set__empty();
  set__add(empty,1);
  int x = !set__find(empty,2);
  set__free(empty);
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



int test__set__remove()
{
    struct set *se = set__empty();
    set__add(se,10);
    set__add(se,329);
    set__add(se,10);
    set__add(se,20);
    set__add(se,30);
    set__add(se,40);
    int x= set__remove(se,10) == 0  && set__remove(se,20) == 0 && set__remove(se,15) == -1;
    set__free(se);
    return x;
}

int test__set__free()
{
    struct set *se = set__empty();
    set__add(se,10);
    set__add(se,30);
    set__add(se,40);
    set__free(se);
    return 1;
}

int test__set__filter__pair()
{
    struct set *s = set__empty();
    for(int i = 0;i<100;i++)
        set__add(s,i);
    struct set *se = set__filter(is_pair,s);
    int bool = 1;
    for(int i = 0 ;i<100 ; i = i+2)
        bool = bool && set__find(se,i) && !set__find(se,i+1);
    set__free(s);
    set__free(se);
    return bool;
}

int test__set__filter__impair(){
    struct set *s = set__empty();
    for(int i=0; i<100;i++)
        set__add(s,i);
    struct set *se = set__filter(is_impair,s);
    int bool = 1;
    for(int i =0;i<100;i=i+2)
        bool = bool && set__find(se,i+1) && !set__find(se,i);
    set__free(s);
    set__free(se);
    return bool;
}

int test__set__debug_data(){
    struct set *se = set__empty();
    set__add(se,10);
    set__add(se,20);
    set__add(se,30);
    set__debug_data(se,print_line);
    set__debug_data(se,print_space);
    set__free(se);
    return 1;
}

int main()
{
    TESTFUNC("testing lnk__empty() function",test_lnk__empty);
    TESTFUNC("testing lnk__add_head() function",test_lnk__add_head);
    TESTFUNC("testing lnk__remove_head() function",test_lnk__remove_head);
    TESTFUNC("testing lnk__add_after() function",test_lnk__add_after);
    TESTFUNC("testing lnk__remove_after() function",test_lnk__remove_after);
    TESTFUNC("testing lnk__first() function",test_lnk__first);
    TESTFUNC("testing llm__is_end_mark() function",test_llm__is_end_mark);
    TESTFUNC("testing llm__next() function",test_llm__next);
    TESTFUNC("testing set__is_empty() function on an empty set",test__is_empty_on_empty_set);
    TESTFUNC("testing set__is_empty() function on a non-empty set",test__is_empty_on_non_empty_set);
    TESTFUNC("testing find function()",test__find);
    TESTFUNC("testing set__add() function",test_set__add);
    TESTFUNC("testing set__find() function in a positive case",test__find_on_positive_case);
    TESTFUNC("testing set__find() function in a negative case",test__find_on_negative_case);
    TESTFUNC("testing set__remove() function",test__set__remove);
    TESTFUNC("testing set__free() function",test__set__free);
    TESTFUNC("testing set__filter() function with pair filter",test__set__filter__pair);
    TESTFUNC("testing set__filter() function with impair filter",test__set__filter__impair);
    TESTFUNC("testing set__debug_data() function",test__set__debug_data );
    
    return 0;
}
