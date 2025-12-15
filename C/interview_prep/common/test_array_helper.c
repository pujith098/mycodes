#include "test_array_helper.h"
#include <stdlib.h>
#include <string.h>

/* Generate random array */
int* generate_random_array(int size, int min_val, int max_val)
{
    if(size <=0 || min_val > max_val) return NULL;

    int *arr = malloc(sizeof(int)*size);
    if(!arr) return NULL;

    for(int i=0;i<size;i++)
        arr[i] = rand() % (max_val - min_val + 1) + min_val;

    return arr;
}

/* Empty array */
int* generate_edge_case_array_empty() { return NULL; }

/* Single element array */
int* generate_edge_case_array_single(int val)
{
    int *arr = malloc(sizeof(int));
    if(!arr) return NULL;
    arr[0] = val;
    return arr;
}

/* All same elements */
int* generate_edge_case_array_all_same(int size, int val)
{
    if(size <=0) return NULL;
    int *arr = malloc(sizeof(int)*size);
    if(!arr) return NULL;
    for(int i=0;i<size;i++) arr[i] = val;
    return arr;
}

/* Free array */
void free_array(int* arr)
{
    if(arr) free(arr);
}

/* Compare arrays */
int compare_arrays(int *a, int *b, int size)
{
    if(!a || !b) return 0;
    for(int i=0;i<size;i++)
        if(a[i] != b[i]) return 0;
    return 1;
}
