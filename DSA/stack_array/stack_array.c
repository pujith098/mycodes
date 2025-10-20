#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;           // index of the top element, -1 when empty
} Stack;

/* Initialize stack */
void stack_init(Stack *s) {
    s->top = -1;
}

/* Check if stack is empty */
bool stack_is_empty(const Stack *s) {
    return (s->top == -1);
}

/* Check if stack is full */
bool stack_is_full(const Stack *s) {
    return (s->top == MAX_STACK_SIZE - 1);
}

/* Push value onto stack. Returns true on success, false if overflow. */
bool stack_push(Stack *s, int value) {
    if (stack_is_full(s)) {
        return false; // overflow
    }
    s->data[++(s->top)] = value;
    return true;
}

/* Pop value from stack. Returns true on success, false if underflow.
   Popped value is stored into *out. */
bool stack_pop(Stack *s, int *out) {
    if (stack_is_empty(s)) {
        return false; // underflow
    }
    if (out) *out = s->data[(s->top)--];
    else (s->top)--; // still pop if caller doesn't want value
    return true;
}

/* Peek top element without popping. Returns true on success, false if empty. */
bool stack_peek(const Stack *s, int *out) {
    if (stack_is_empty(s)) return false;
    if (out) *out = s->data[s->top];
    return true;
}

/* Utility: print stack contents (top first) */
void stack_print(const Stack *s) {
    if (stack_is_empty(s)) {
        printf("[empty]\n");
        return;
    }
    printf("Stack (top -> bottom): ");
    for (int i = s->top; i >= 0; --i)
        printf("%d%s", s->data[i], (i==0) ? "\n" : " ");
}

/* Example usage */
int main(void) {
    Stack s;
    stack_init(&s);

    printf("Pushing 10, 20, 30\n");
    stack_push(&s, 10);
    stack_push(&s, 20);
    stack_push(&s, 30);
    stack_print(&s);

    int v;
    if (stack_peek(&s, &v))
        printf("Top element (peek): %d\n", v);

    if (stack_pop(&s, &v))
        printf("Popped: %d\n", v);
    stack_print(&s);

    printf("Popping remaining elements:\n");
    while (stack_pop(&s, &v)) {
        printf("  %d\n", v);
    }

    if (!stack_pop(&s, &v))
        printf("Cannot pop: stack is empty (underflow)\n");

    /* Fill stack to test overflow */
    for (int i = 0; i < MAX_STACK_SIZE; ++i) stack_push(&s, i);
    if (!stack_push(&s, 12345))
        printf("Cannot push: stack is full (overflow)\n");

    return 0;
}

