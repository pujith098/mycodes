#ifndef REARRANGE_LL_H
#define REARRANGE_LL_H

struct node {
    int data;
    struct node* next;
};

void rearrange_odd_even(struct node **head);

#endif

