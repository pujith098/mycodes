#include "test_linked_list_helper.h"
#include <stdio.h>
#include <stdlib.h>

node* create_linked_list(int *arr, int n) {
    if (n <= 0) return NULL;
    node *head = malloc(sizeof(node));
    head->data = arr[0];
    head->next = NULL;
    node *curr = head;
    for (int i = 1; i < n; i++) {
        curr->next = malloc(sizeof(node));
        curr = curr->next;
        curr->data = arr[i];
        curr->next = NULL;
    }
    return head;
}

void free_linked_list(node *head) {
    while (head) {
        node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_linked_list(node *head) {
    printf("[");
    while (head) {
        printf("%d", head->data);
        if (head->next) printf(", ");
        head = head->next;
    }
    printf("]\n");
}

int compare_linked_list_with_array(node *head, int *arr, int n) {
    for (int i = 0; i < n; i++) {
        if (!head || head->data != arr[i]) return 0;
        head = head->next;
    }
    return head == NULL;
}

