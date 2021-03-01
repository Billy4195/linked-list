#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
{ 
    node_t->next = *list;
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

#define MAX_STACK_SIZE 300

static void __quicksort(node_t **list, int size)
{
    if (!*list)
        return;

    int left_stk[MAX_STACK_SIZE], right_stk[MAX_STACK_SIZE];
    int stk_size = 0;
    int left_idx, right_idx, swap;
    node_t *pivot;

    left_stk[stk_size] = 0, right_stk[stk_size] = size;
    while (stk_size >= 0) {
        left_idx = left_stk[stk_size];
        right_idx = right_stk[stk_size] - 1; if (left_idx < right_idx) { pivot = list[left_idx];
            while (left_idx < right_idx) {
                while (left_idx < right_idx && list[right_idx]->value >= pivot->value) {
                    right_idx--;
                }
                if (left_idx < right_idx) list[left_idx++] = list[right_idx];
                while (left_idx < right_idx && list[left_idx]->value <= pivot->value) {
                    left_idx++;
                }
                if (left_idx < right_idx) list[right_idx--] = list[left_idx];
            }
            list[left_idx] = pivot;
            left_stk[stk_size+1] = left_idx+1;
            right_stk[stk_size+1] = right_stk[stk_size];
            right_stk[stk_size] = left_idx;

            if ((right_stk[stk_size] - left_stk[stk_size]) < (right_stk[stk_size+1] - left_stk[stk_size+1])) {
                swap = left_stk[stk_size];
                left_stk[stk_size] = left_stk[stk_size+1];
                left_stk[stk_size+1] = swap;
                swap = right_stk[stk_size];
                right_stk[stk_size] = right_stk[stk_size+1];
                right_stk[stk_size+1] = swap;
            }
            stk_size++;
        } else {
            stk_size--;
        }
    }
}

void quicksort(node_t **list)
{
    int capacity = 0, size = 0, i;
    node_t *cur = *list;
    node_t **list_arr = malloc(sizeof(node_t*) * 16);

    if (NULL == list_arr)
        goto malloc_err;
    capacity = 16;

    while (cur) {
        if (size == capacity) {
            node_t **new_arr = malloc(sizeof(node_t*) * capacity * 2);
            if (NULL == new_arr)
                goto malloc_err;

            memcpy((void*)new_arr, (void*)list_arr, sizeof(node_t*)*capacity);
            free(list_arr);
            list_arr = new_arr;
            capacity *= 2;
        }
        list_arr[size] = cur;
        cur = cur->next;
        list_arr[size]->next = NULL;
        size++;
    }
    __quicksort(list_arr, size);
    for (i=0; i < size; i++) {
        *list = list_arr[i];
        list = &((*list)->next);
    }
    free(list_arr);
    return;
malloc_err:
    printf("Error: malloc fail capacity:%d!\n", capacity);
    return;
}
