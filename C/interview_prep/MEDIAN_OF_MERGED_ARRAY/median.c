#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "median.h"

/* Comparison function for qsort */
int cmp_int(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y;
}

/* 
 * Finds median of two sorted arrays (merged). 
 * Returns double median.
 */
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int merged_size = nums1Size + nums2Size;
    int *merged = malloc(sizeof(int) * merged_size);
    if (!merged) return 0.0; // handle malloc fail

    memcpy(merged, nums1, nums1Size * sizeof(int));
    memcpy(merged + nums1Size, nums2, nums2Size * sizeof(int));

    qsort(merged, merged_size, sizeof(int), cmp_int);

    double median;
    int mid = merged_size / 2;
    if (merged_size % 2 == 1) {
        median = merged[mid];
    } else {
        median = ((double)(merged[mid - 1] + merged[mid])) / 2.0;
    }

    free(merged);
    return median;
}

