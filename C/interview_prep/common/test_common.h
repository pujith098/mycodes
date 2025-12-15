#ifndef TEST_COMMON_H
#define TEST_COMMON_H

typedef int (*test_func_t)(void);

void run_test(const char *name, test_func_t func);
void print_test_summary(void);
void print_array(int *arr, int n);

#endif

