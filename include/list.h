#ifndef LIST_H
#define LIST_H

typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

node_t* list_make_node_t(node_t* list, int value);
void list_add_node_t(node_t **list, node_t *node_t);
void list_concat(node_t **left, node_t *right);
void list_free(node_t **list);
void quicksort(node_t **list);

#endif
