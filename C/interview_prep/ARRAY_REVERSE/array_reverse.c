#include "array_reverse.h"

void reverse_array_inplace(int *a, int size)
{
    if (a == NULL || size <= 1)
        return;

    int start = 0;
    int end = size - 1;
    int temp;

    printf("LOG: Starting in-place reversal, size = %d\n", size);

    while (start < end)
    {
        printf("LOG: Swap index %d (%d) with index %d (%d)\n", start, a[start], end, a[end]);

        if (a[start] != a[end])
        {
            temp = a[start];
            a[start] = a[end];
            a[end] = temp;
        }

        start++;
        end--;
    }

    printf("LOG: Reversal completed.\n");
}

void print_array(int *a, int size)
{
    if (!a || size <= 0) { printf("NULL\n"); return; }

    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

