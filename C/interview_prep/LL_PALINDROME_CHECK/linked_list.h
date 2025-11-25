#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Core linked list functions
Node* createNode(int data);
void appendNode(Node **head, int data);
void printList(Node *head);
void createLoop(Node *head, int pos);
Node* buildListFromString(const char *str);

// Palindrome logic
int isPalindrome(Node *head);

#endif

