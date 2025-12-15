#include "test_ll_helper.h"
#include <stdlib.h>

Node* generate_ll_from_array(int *arr, int size)
{
    if (!arr || size <= 0) return NULL;

    Node *head = malloc(sizeof(Node));
    if (!head) return NULL;
    head->data = arr[0];
    head->next = NULL;

    Node *current = head;

    for (int i = 1; i < size; i++)
    {
        Node *new_node = malloc(sizeof(Node));
        if (!new_node) return head;
        new_node->data = arr[i];
        new_node->next = NULL;

        current->next = new_node;
        current = new_node;
    }

    return head;
}

void free_ll(Node *head)
{
    Node *current = head;
    while (current)
    {
        Node *tmp = current;
        current = current->next;
        free(tmp);
    }
}
