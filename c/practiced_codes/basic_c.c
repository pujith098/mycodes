//This program is about basics of C programming 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Typedef for structure
typedef struct
{
    int data1;
    float data2;
    void *pointer;
} type1_t;

// Typedef for union
typedef union
{
    type1_t var;
    char data;
    double data2;
} type2_t;

// Function prototype
void print_array(int *arr, int size);
void modify_value(int *ptr);

int main(void)
{
    // Basic data types
    char symbol = '&';
    short int num1 = 2478;
    int num2 = 45779;
    float num3 = 652.6465f;
    double num4 = 7837.8929;
    void *pointer = &symbol;

    // Array and string
    int array[5] = {1, 3, 9, 8, 24};
    char string[10] = "rocky";

    // Structure initialization
    type1_t var1 = {
        .data1 = num2,
        .data2 = num3,
        .pointer = &array};

    // Union initialization
    type2_t instance;
    instance.var = var1;
    instance.data = symbol;
    instance.data2 = num4;

    // Dynamic memory allocation
    int *dyn_mem = (int *)malloc(5 * sizeof(int));
    if (dyn_mem == NULL)
    {
        printf("Memory allocation failed!\n");
        return -1;
    }
    for (int i = 0; i < 5; i++)
        dyn_mem[i] = i * 2;

    // Printing info
    printf("===== BASIC DATA TYPES =====\n");
    printf("char var - %c | sizeof(char) = %ld bytes\n", symbol, sizeof(symbol));
    printf("short int var - %hd | sizeof(short int) = %ld bytes\n", num1, sizeof(num1));
    printf("int var - %d | sizeof(int) = %ld bytes\n", num2, sizeof(num2));
    printf("float var - %.3f | sizeof(float) = %ld bytes\n", num3, sizeof(num3));
    printf("double var - %.3lf | sizeof(double) = %ld bytes\n", num4, sizeof(num4));
    printf("pointer var - %p | sizeof(pointer) = %ld bytes\n", pointer, sizeof(pointer));

    printf("\n===== ARRAY & STRING =====\n");
    printf("Array size = %ld bytes\n", sizeof(array));
    print_array(array, sizeof(array) / sizeof(array[0]));
    printf("String = %s | Length = %ld | sizeof(string) = %ld bytes\n", string, strlen(string), sizeof(string));

    printf("\n===== STRUCTURE =====\n");
    printf("sizeof(struct) = %ld bytes\n", sizeof(var1));
    printf("member1: %d\nmember2: %.2f\nmember3: %p\n", var1.data1, var1.data2, var1.pointer);

    printf("\n===== UNION =====\n");
    printf("sizeof(union) = %ld bytes\n", sizeof(instance));
    printf("member data = %c\nmember data2 = %.2lf\n", instance.data, instance.data2);

    printf("\n===== POINTER FUNCTION =====\n");
    int value = 10;
    printf("Before modify: %d\n", value);
    modify_value(&value);
    printf("After modify: %d\n", value);

    printf("\n===== DYNAMIC MEMORY =====\n");
    print_array(dyn_mem, 5);
    free(dyn_mem);

    return 0;
}

// Function to print array elements
void print_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("Element[%d] = %d\n", i, arr[i]);
}

// Function to modify variable using pointer
void modify_value(int *ptr)
{
    *ptr += 5;
}

