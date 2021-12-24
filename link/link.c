#include <stdio.h>
#include <stdlib.h>
#include "link.h"


const struct lelement sentinel = {-1, (struct lelement *) &sentinel};

// returns an empty linked list
struct link lnk__empty(void)
{
    struct link l;
    l.head = SENTINEL;
    return l;
}

// adds cell e at the head of linked list l
void lnk__add_head(struct link * l, struct lelement * e)
{
    e->next = l->head;
    l->head = e;
}

// removes and returns the first cell of linked list l
// returns NULL on failure
struct lelement * lnk__remove_head(struct link * l)
{
    if (l == NULL || l->head == SENTINEL)
        return NULL;
    struct lelement *toDelete = l->head;
    l->head = l->head->next;
    toDelete->next = NULL;
    return toDelete;
}
// 15 ; 10 ; 7 : .08
// 12 ; 10 ; 7 ; .08
// adds cell b after cell e in liked list l
// we assume that e is a cell in l.
// returns 0 on success, another value on failure
int lnk__add_after(struct link * l, struct lelement *e, struct lelement * b) 
{
    if (l == NULL || e == SENTINEL || b == SENTINEL)
    {
        printf("Impossible insertion\n");
        return 1;
    }

    b->next = e->next;
    e->next = b;
    //while(currentCell->data != e->data)
    //{
    //    currentCell = currentCell->next;
    //}
    //currentCell->data = e->data
    //b->next = currentCell->next;
    //currentCell->next = b;
    return 0;
}

// removes and returns the cell after b in linked list l
// we assume that b is a cell of linked list l
// returns NULL on failure, a valid cell address on success
struct lelement * lnk__remove_after(struct link * l, struct lelement * b)
{
    if (l==NULL || l->head == SENTINEL)
        return NULL;
    //struct lelement *currentElement = l->head;
    //while(currentElement->data != b->data )
    //{
    //    currentElement = currentElement->next;
    //}
     // currentElement -> data == b->data
     //currentElement = b
     if (b->next == SENTINEL)
        return NULL;
    struct lelement *toDelete = b->next;
    b->next = toDelete->next;
    toDelete->next = NULL;
    return toDelete;
    //if (currentElement->next == SENTINEL)
    //    return NULL;
    //struct lelement *toDelete = currentElement->next;
    //currentElement->next = toDelete->next;
    //toDelete->next = NULL;
    //return toDelete;
    
}

// returns a pointer to the first cell in linked list l
struct lelement * lnk__first(const struct link * l)
{
    return l->head;
}

// returns non-zero if e is the sentinel, zero otherwise
int llm__is_end_mark(const struct lelement *e)
{
    return e == SENTINEL;
} 

// returns a pointer to the next cell of cell e
struct lelement * llm__next(const struct lelement *e )
{
    return e->next;
}
/*
int main()
{
    struct link l = lnk__empty();
    struct lelement e1 = {.data=12};
    struct lelement e2 = {.data=14};
    struct lelement e3 = {.data=16};
    struct lelement e4 = {.data=18};
    lnk__add_head(&l,&e1);
    lnk__add_after(&l,&e2,&e1);
    lnk__add_after(&l,&e3,&e2);
    lnk__add_after(&l,&e4,&e3);
    struct lelement *currentElement = l.head;
    while(currentElement!=SENTINEL)
    {
        printf(" %d ->",currentElement->data);
        currentElement = currentElement->next;
    }
    printf("\n");

    return 0;
}
*/