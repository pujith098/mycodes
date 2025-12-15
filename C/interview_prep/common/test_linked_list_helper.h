#ifndef TEST_LINKED_LIST_HELPER_H
#define TEST_LINKED_LIST_HELPER_H

#include "../RE_ARRANGE_ODD_EVEN_POSITION/rearrange_ll.h"

typedef struct node node;

node* create_linked_list(int *arr, int n);
void free_linked_list(node *head);
void print_linked_list(node *head);
int compare_linked_list_with_array(node *head, int *arr, int n);

#endif

