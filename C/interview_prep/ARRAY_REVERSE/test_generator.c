#include "array_reverse.h"
#include <time.h>

#define MAX_SIZE 50

// ==================== GENERATORS ====================

// Generate random array with values 0-99
void generate_random_array(int *a, int size)
{
    for (int i = 0; i < size; i++)
        a[i] = rand() % 100;
    printf("LOG: Generated Random Array: ");
    print_array(a, size);
}

// Generate palindrome-like array
void generate_palindrome_array(int *a, int size)
{
    int half = size / 2;
    for (int i = 0; i < half; i++)
    {
        int val = rand() % 100;
        a[i] = a[size - 1 - i] = val;
    }
    if (size % 2 == 1)
        a[half] = rand() % 100;

    printf("LOG: Generated Palindrome-like Array: ");
    print_array(a, size);
}

// Generate repeated pattern array
void generate_pattern_array(int *a, int size)
{
    int val1 = rand() % 100;
    int val2 = rand() % 100;
    for (int i = 0; i < size; i++)
        a[i] = (i % 2 == 0) ? val1 : val2;

    printf("LOG: Generated Patterned Array: ");
    print_array(a, size);
}

// Generate single value array
void generate_single_array(int *a, int size)
{
    int val = rand() % 100;
    for (int i = 0; i < size; i++)
        a[i] = val;

    printf("LOG: Generated Single-value Array: ");
    print_array(a, size);
}

// ==================== TEST FUNCTION ====================

void test_array(int test_no, int *a, int size, const char *input_type)
{
    printf("\n==============================\n");
    printf("TEST %d\n", test_no);
    printf("Input Type: %s\n", input_type);
    printf("Input Array: ");
    print_array(a, size);

    reverse_array_inplace(a, size);

    printf("Reversed Array: ");
    print_array(a, size);
    printf("==============================\n");
}

// ==================== MAIN ====================

int main()
{
    srand(time(NULL));
    int a[MAX_SIZE];
    int total_tests = 50;

    for (int t = 1; t <= total_tests; t++)
    {
        int size = rand() % MAX_SIZE + 1;
        int type = rand() % 4;
        const char *input_type;

        switch(type)
        {
            case 0:
                generate_random_array(a, size);
                input_type = "Random Array";
                break;
            case 1:
                generate_palindrome_array(a, size);
                input_type = "Palindrome-like Array";
                break;
            case 2:
                generate_pattern_array(a, size);
                input_type = "Patterned Array";
                break;
            case 3:
                generate_single_array(a, size);
                input_type = "Single-value Array";
                break;
        }

        test_array(t, a, size, input_type);
    }

    return 0;
}

