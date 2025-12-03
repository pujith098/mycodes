#include <stdio.h>

void fabinoci(int limit); // forward declaration

// Helper: run one test
void run_test(int limit) {
    printf("\n=== TEST (limit = %d) ===\n", limit);
    fabinoci(limit);
    printf("=========================\n");
}

int main()
{
    // --- Automatic Tests ---
    printf("Running automatic tests...\n");

    // Edge cases
    run_test(-5);
    run_test(0);
    run_test(1);
    run_test(2);

    // Small values
    run_test(10);
    run_test(50);

    // Larger values
    run_test(1000);

    // --- Manual User Input ---
    int num;
    printf("\nManual mode: Enter a number: ");
    if (scanf("%d", &num) == 1) {
        fabinoci(num);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}

