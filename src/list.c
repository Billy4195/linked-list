#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

node_t* list_make_node_t(node_t* list, int value)
{
    node_t *nnode = malloc(sizeof(node_t));
    if (nnode) {
        nnode->value = value;
        nnode->next = list;
        list = nnode;
    }
    return list;
}

void list_add_node_t(node_t **list, node_t *node_t)
{ node_t->next = *list;
    *list = node_t;
}

void list_concat(node_t **left, node_t *right)
{
    while (*left) {
        // LLL;
        left = &((*left)->next);
    }
    *left = right;
}

void list_free(node_t **list)
{
    node_t *p = *list;
    while (p) {
        node_t *n = p;
        p = p->next;
        free(n);
    }
}

void quicksort(node_t **list)
{
    if (!*list)
        return;

    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        //list_add_node_t(n->value > value ? AAA : BBB, n);
        list_add_node_t(n->value > value ? &right : &left, n);
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    // CCC;
    list_concat(&result, pivot);
    list_concat(&result, right);
    *list = result;
}
