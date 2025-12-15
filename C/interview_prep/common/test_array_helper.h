#ifndef TEST_ARRAY_HELPER_H
#define TEST_ARRAY_HELPER_H

#include <stdlib.h>

/**
 * @brief Generate a random array with given size and value range.
 * @param size Number of elements
 * @param min_val Minimum value
 * @param max_val Maximum value
 * @return Pointer to allocated array or NULL on failure
 */
int* generate_random_array(int size, int min_val, int max_val);

/**
 * @brief Generate an empty array (NULL pointer).
 * @return NULL pointer
 */
int* generate_edge_case_array_empty();

/**
 * @brief Generate a single-element array.
 * @param val Value of the element
 * @return Pointer to allocated array
 */
int* generate_edge_case_array_single(int val);

/**
 * @brief Generate an array with all elements the same.
 * @param size Number of elements
 * @param val Value for all elements
 * @return Pointer to allocated array
 */
int* generate_edge_case_array_all_same(int size, int val);

/**
 * @brief Free allocated array memory.
 * @param arr Pointer to the array
 */
void free_array(int* arr);

/**
 * @brief Compare two arrays for equality.
 * @param a First array
 * @param b Second array
 * @param size Number of elements
 * @return 1 if equal, 0 otherwise
 */
int compare_arrays(int *a, int *b, int size);

#endif // TEST_ARRAY_HELPER_H
