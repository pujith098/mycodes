#include <stdio.h>
#include "median.h"

void run_test(int testNo, int *nums1, int size1, int *nums2, int size2) {
    double median = findMedianSortedArrays(nums1, size1, nums2, size2);
    printf("=== TEST %d ===\n", testNo);
    printf("Array 1: ");
    for (int i = 0; i < size1; i++) printf("%d ", nums1[i]);
    printf("\nArray 2: ");
    for (int i = 0; i < size2; i++) printf("%d ", nums2[i]);
    printf("\nMedian: %.2f\n", median);
    printf("=================\n\n");
}

int main() {
    // Test cases
    int arr1[] = {1, 3};
    int arr2[] = {2};
    run_test(1, arr1, 2, arr2, 1);

    int arr3[] = {1, 2};
    int arr4[] = {3, 4};
    run_test(2, arr3, 2, arr4, 2);

    int arr5[] = {};
    int arr6[] = {1};
    run_test(3, arr5, 0, arr6, 1);

    int arr7[] = {0, 0};
    int arr8[] = {0, 0};
    run_test(4, arr7, 2, arr8, 2);

    int arr9[] = {};
    int arr10[] = {};
    run_test(5, arr9, 0, arr10, 0);

    // Manual input example (optional)
    printf("Manual test example skipped for brevity.\n");

    return 0;
}

