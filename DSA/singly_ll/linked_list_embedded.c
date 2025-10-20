/*
File: linked_list_embedded.c
Description: Simple singly-linked list for embedded use (no malloc: static pool).
*/


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define POOL_SIZE 6


typedef struct node {
int data;
struct node *next;
} node_t;


static node_t pool[POOL_SIZE];
static node_t *free_list;


void pool_init(void) {
for (int i=0;i<POOL_SIZE-1;i++) pool[i].next = &pool[i+1];
pool[POOL_SIZE-1].next = NULL;
free_list = &pool[0];
}


node_t *alloc_node(void) {
if (!free_list) return NULL;
node_t *n = free_list;
free_list = free_list->next;
n->next = NULL;
return n;
}


void free_node(node_t *n) {
n->next = free_list;
free_list = n;
}


int main(void) {
pool_init();
node_t *head = NULL;
// push 3 nodes
for (int i=1;i<=3;i++) {
node_t *n = alloc_node();
if (!n) break;
n->data = i*10;
n->next = head;
head = n;
}
// traverse
for (node_t *p = head; p; p = p->next) printf("%d ", p->data);
printf("\n");
// free all
while (head) { node_t *t = head; head = head->next; free_node(t); }
return 0;
}
