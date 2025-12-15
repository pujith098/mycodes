#include <stdio.h>
#include "../common/logger.h"
#include "../common/test_common.h"
#include "../common/test_linked_list_helper.h"
#include "rearrange_ll.h"

// Log input, output, expected
static void log_io(node *input, node *output, int *exp, int len) {
    logger_info("Input   :");
    print_linked_list(input);
    logger_info("Output  :");
    print_linked_list(output);
    logger_info("Expected:");
    print_array(exp, len);
}

// Test 1: Empty list
static int test_empty_list(void) {
    node *head = NULL;
    int exp[] = {};
    rearrange_odd_even(&head);
    log_io(head, head, exp, 0);
    return compare_linked_list_with_array(head, exp, 0);
}

// Test 2: Single node
static int test_single_node(void) {
    int arr[] = {1};
    int exp[] = {1};
    node *head = create_linked_list(arr, 1);
    rearrange_odd_even(&head);
    log_io(head, head, exp, 1);
    int pass = compare_linked_list_with_array(head, exp, 1);
    free_linked_list(head);
    return pass;
}

// Test 3: Two nodes
static int test_two_nodes(void) {
    int arr[] = {1, 2};
    int exp[] = {1, 2};
    node *head = create_linked_list(arr, 2);
    rearrange_odd_even(&head);
    log_io(head, head, exp, 2);
    int pass = compare_linked_list_with_array(head, exp, 2);
    free_linked_list(head);
    return pass;
}

// Test 4: Odd number of nodes
static int test_odd_nodes(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int exp[] = {1, 3, 5, 2, 4};
    node *head = create_linked_list(arr, 5);
    rearrange_odd_even(&head);
    log_io(head, head, exp, 5);
    int pass = compare_linked_list_with_array(head, exp, 5);
    free_linked_list(head);
    return pass;
}

// Test 5: Even number of nodes
static int test_even_nodes(void) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int exp[] = {1, 3, 5, 2, 4, 6};
    node *head = create_linked_list(arr, 6);
    rearrange_odd_even(&head);
    log_io(head, head, exp, 6);
    int pass = compare_linked_list_with_array(head, exp, 6);
    free_linked_list(head);
    return pass;
}

// Test 6: All same values
static int test_all_same_values(void) {
    int arr[] = {7, 7, 7, 7, 7};
    int exp[] = {7, 7, 7, 7, 7};
    node *head = create_linked_list(arr, 5);
    rearrange_odd_even(&head);
    log_io(head, head, exp, 5);
    int pass = compare_linked_list_with_array(head, exp, 5);
    free_linked_list(head);
    return pass;
}

// Test 7: Already rearranged
static int test_already_rearranged(void) {
    int arr[] = {1, 3, 5, 2, 4};
    int exp[] = {1, 5, 4, 3, 2};
    node *head = create_linked_list(arr, 5);
    rearrange_odd_even(&head);
    log_io(head, head, exp, 5);
    int pass = compare_linked_list_with_array(head, exp, 5);
    free_linked_list(head);
    return pass;
}

// Test 8: Large integer values
static int test_large_values(void) {
    int arr[] = {100000, 500000, 999999, 123456, 987654};
    int exp[] = {100000, 999999, 987654, 500000, 123456};
    node *head = create_linked_list(arr, 5);
    rearrange_odd_even(&head);
    log_io(head, head, exp, 5);
    int pass = compare_linked_list_with_array(head, exp, 5);
    free_linked_list(head);
    return pass;
}

// Test 9: Large sequential list
static int test_large_list(void) {
    #define N 10
    int arr[N], exp[N];
    for (int i = 0; i < N; i++) arr[i] = i + 1;
    int idx = 0;
    for (int i = 0; i < N; i += 2) exp[idx++] = i + 1;
    for (int i = 1; i < N; i += 2) exp[idx++] = i + 1;

    node *head = create_linked_list(arr, N);
    rearrange_odd_even(&head);
    log_io(head, head, exp, N);
    int pass = compare_linked_list_with_array(head, exp, N);
    free_linked_list(head);
    return pass;
}

// Test 10: Random list
static int test_random_list(void) {
    int arr[] = {4, 1, 7, 3, 6, 2, 5};
    int exp[] = {4, 7, 6, 5, 1, 3, 2};
    node *head = create_linked_list(arr, 7);
    rearrange_odd_even(&head);
    log_io(head, head, exp, 7);
    int pass = compare_linked_list_with_array(head, exp, 7);
    free_linked_list(head);
    return pass;
}

// Test 11: Repeated runs
static int test_repeated_runs(void) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int exp[] = {1, 3, 5, 2, 4, 6};
    int pass = 1;
    for (int i = 0; i < 5; i++) {
        node *head = create_linked_list(arr, 6);
        rearrange_odd_even(&head);
        log_io(head, head, exp, 6);
        if (!compare_linked_list_with_array(head, exp, 6)) pass = 0;
        free_linked_list(head);
    }
    return pass;
}

// Main
int main() {
    logger_init();
    run_test("Empty list", test_empty_list);
    run_test("Single node", test_single_node);
    run_test("Two nodes", test_two_nodes);
    run_test("Odd nodes", test_odd_nodes);
    run_test("Even nodes", test_even_nodes);
    run_test("All same values", test_all_same_values);
    run_test("Already rearranged", test_already_rearranged);
    run_test("Large values", test_large_values);
    run_test("Large list", test_large_list);
    run_test("Random list", test_random_list);
    run_test("Repeated runs", test_repeated_runs);

    print_test_summary();
    return 0;
}

