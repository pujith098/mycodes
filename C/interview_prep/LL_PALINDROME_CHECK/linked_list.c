#include "linked_list.h"

Node* createNode(int data) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void appendNode(Node **head, int data) {
    Node* newnode = createNode(data);

    if (*head == NULL) {
        *head = newnode;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newnode;
}

void printList(Node *head) {
    Node *temp = head;
    int count = 0;

    while (temp != NULL && count < 30) {
        printf("%c -> ", temp->data);
        temp = temp->next;
        count++;
    }

    if (temp != NULL)
        printf("...(loop detected)\n");
    else
        printf("NULL\n");
}

void createLoop(Node *head, int pos) {
    if (pos < 0) return;

    Node *loopNode = NULL, *temp = head;
    int index = 0;

    while (temp && temp->next != NULL) {
        if (index == pos)
            loopNode = temp;
        temp = temp->next;
        index++;
    }

    if (loopNode)
        temp->next = loopNode;
}

int isPalindrome(Node *head) {
    printf("LOG: Starting palindrome check...\n");

    if (head == NULL || head->next == NULL) {
        printf("LOG: Single node / empty. Auto palindrome.\n");
        return 1;
    }

    Node *slow = head, *fast = head;
    int index = 0;

    printf("LOG: Finding middle point...\n");

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        printf("LOG: slow at index %d, data '%c'\n", index, slow->data);
        index++;

        if (fast == slow) {
            printf("LOG: LOOP DETECTED!\n");
            return -1;
        }
    }

    printf("LOG: Middle node found '%c'\n", slow->data);
    printf("LOG: Reversing second half...\n");

    Node *prev = NULL, *current = slow, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    printf("LOG: Reverse completed.\n");
    printf("LOG: Starting comparison...\n");

    Node *first = head;
    Node *second = prev;

    while (second != NULL) {
        printf("LOG: Compare '%c' with '%c'\n", first->data, second->data);

        if (first->data != second->data) {
            printf("LOG: Mismatch found.\n");
            return 0;
        }

        first = first->next;
        second = second->next;
    }

    printf("LOG: Comparison complete. Palindrome!\n");
    return 1;
}

Node* buildListFromString(const char *str) {
    Node *head = NULL;
    for (int i = 0; str[i] != '\0'; i++)
        appendNode(&head, str[i]);
    return head;
}

