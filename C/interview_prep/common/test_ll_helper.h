#ifndef TEST_LL_HELPER_H
#define TEST_LL_HELPER_H

/**
 * @brief Linked list node.
 */
typedef struct Node {
    int data;
    struct Node* next;
} Node;

/**
 * @brief Generate linked list from array.
 * @param arr Input array
 * @param size Number of elements
 * @return Head of linked list
 */
Node* generate_ll_from_array(int *arr, int size);

/**
 * @brief Free linked list memory.
 * @param head Head node
 */
void free_ll(Node *head);

#endif
