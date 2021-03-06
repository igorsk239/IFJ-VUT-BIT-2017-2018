#ifndef SETINT_H
#define SETINT_H

#include "llist.h"

typedef struct {
    LListBaseItem base;
    int value;
} SetIntItem;


typedef LList SetInt;

typedef struct {
    LListBaseItem base;
    SetInt* set;
} LListItemSet;

void llist_set_int_init(LListBaseItem* item);

void llist_set_int_free(LListBaseItem* item);

SetInt* set_int_init();

SetInt* set_int_copy(SetInt* other);

void set_int_free(SetInt** set);

bool set_int_contains(SetInt* set, int value);

bool set_int_is_empty(SetInt* set);

size_t set_int_size(SetInt* set);

void set_int_add(SetInt* set, int value);

void set_int_remove(SetInt* set, int value);

void set_int_clear(SetInt* set);

void set_int_print(SetInt* set);

// TODO test
void set_int_union(SetInt* set, SetInt* other);

// TODO test
void set_int_difference(SetInt* set, SetInt* other);

bool set_int_difference_is_empty(SetInt* set, SetInt* other);

#endif // SETINT_H
