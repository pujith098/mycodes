#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// ==================== INSERTION OPERATIONS ====================

// Insert at beginning - Adds a new node at the start of the list
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Insert at end - Adds a new node at the end of the list
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Insert at specific position - Adds a new node at a given index/position
void insertAtPosition(Node** head, int data, int position) {
    if (position == 0) {
        insertAtBeginning(head, data);
        return;
    }
    Node* newNode = createNode(data);
    Node* temp = *head;
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds\n");
        free(newNode);
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// Insert after a given node - Adds a new node immediately after a specified node
void insertAfterNode(Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}

// Insert before a given node - Adds a new node immediately before a specified node
void insertBeforeNode(Node** head, Node* nextNode, int data) {
    if (*head == NULL || nextNode == NULL) {
        printf("Invalid operation\n");
        return;
    }
    if (*head == nextNode) {
        insertAtBeginning(head, data);
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL && temp->next != nextNode) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Node not found\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = nextNode;
    temp->next = newNode;
}

// Insert in sorted order - Adds a new node while maintaining sorted order
void insertSorted(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL || (*head)->data >= data) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL && temp->next->data < data) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// ==================== DELETION OPERATIONS ====================

// Delete from beginning - Removes the first node from the list
void deleteFromBeginning(Node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Delete from end - Removes the last node from the list
void deleteFromEnd(Node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

// Delete at specific position - Removes the node at a given index/position
void deleteAtPosition(Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if (position == 0) {
        deleteFromBeginning(head);
        return;
    }
    Node* temp = *head;
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds\n");
        return;
    }
    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    free(nodeToDelete);
}

// Delete a node with given value - Removes the first node containing a specific value
void deleteByValue(Node** head, int value) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    if ((*head)->data == value) {
        deleteFromBeginning(head);
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Value not found\n");
        return;
    }
    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    free(nodeToDelete);
}

// Delete a given node - Removes a node when you have a direct reference to it
void deleteNode(Node** head, Node* nodeToDelete) {
    if (*head == NULL || nodeToDelete == NULL) {
        printf("Invalid operation\n");
        return;
    }
    if (*head == nodeToDelete) {
        *head = (*head)->next;
        free(nodeToDelete);
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL && temp->next != nodeToDelete) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Node not found\n");
        return;
    }
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
}

// Delete all nodes with a given value - Removes every node containing a specific value
void deleteAllOccurrences(Node** head, int value) {
    while (*head != NULL && (*head)->data == value) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    if (*head == NULL) return;
    Node* current = *head;
    while (current->next != NULL) {
        if (current->next->data == value) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

// ==================== TRAVERSAL OPERATIONS ====================

// Forward traversal - Visits each node from head to tail sequentially
void traverse(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        temp = temp->next;
    }
}

// Display/print all elements - Outputs all values in the list
void display(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Count nodes - Returns the total number of nodes in the list
int countNodes(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// ==================== SEARCH OPERATIONS ====================

// Search for a value - Finds if a specific value exists in the list
bool search(Node* head, int value) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Find node at specific position - Returns the node at a given index
Node* findNodeAtPosition(Node* head, int position) {
    Node* temp = head;
    int count = 0;
    while (temp != NULL && count < position) {
        temp = temp->next;
        count++;
    }
    return temp;
}

// Find middle node - Locates the node at the center of the list
Node* findMiddle(Node* head) {
    if (head == NULL) return NULL;
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Find nth node from end - Returns the node at nth position from the tail
Node* findNthFromEnd(Node* head, int n) {
    Node* main = head;
    Node* ref = head;
    int count = 0;
    while (count < n) {
        if (ref == NULL) {
            printf("List has fewer than %d nodes\n", n);
            return NULL;
        }
        ref = ref->next;
        count++;
    }
    while (ref != NULL) {
        main = main->next;
        ref = ref->next;
    }
    return main;
}

// ==================== REVERSAL OPERATIONS ====================

// Reverse the entire list (iterative) - Reverses all links between nodes using iteration
void reverseIterative(Node** head) {
    Node* prev = NULL;
    Node* current = *head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

// Helper function for recursive reverse
Node* reverseRecursiveHelper(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    Node* rest = reverseRecursiveHelper(head->next);
    head->next->next = head;
    head->next = NULL;
    return rest;
}

// Reverse the list (recursive) - Reverses all links between nodes using recursion
void reverseRecursive(Node** head) {
    *head = reverseRecursiveHelper(*head);
}

// Reverse in groups of k nodes - Reverses every k consecutive nodes as a group
Node* reverseInGroups(Node* head, int k) {
    Node* current = head;
    Node* next = NULL;
    Node* prev = NULL;
    int count = 0;
    while (current != NULL && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    if (next != NULL) {
        head->next = reverseInGroups(next, k);
    }
    return prev;
}

// Reverse between specific positions - Reverses only the nodes between two given positions
void reverseBetween(Node** head, int left, int right) {
    if (left == right) return;
    Node* dummy = createNode(0);
    dummy->next = *head;
    Node* prev = dummy;
    for (int i = 0; i < left - 1; i++) {
        prev = prev->next;
    }
    Node* current = prev->next;
    Node* next = NULL;
    for (int i = 0; i < right - left; i++) {
        next = current->next;
        current->next = next->next;
        next->next = prev->next;
        prev->next = next;
    }
    *head = dummy->next;
    free(dummy);
}

// ==================== SORTING OPERATIONS ====================

// Bubble sort - Sorts the list by repeatedly swapping adjacent nodes if they're in wrong order
void bubbleSort(Node** head) {
    if (*head == NULL) return;
    bool swapped;
    Node* ptr1;
    Node* lptr = NULL;
    do {
        swapped = false;
        ptr1 = *head;
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Insertion sort - Sorts by building a sorted portion one node at a time
void insertionSort(Node** head) {
    Node* sorted = NULL;
    Node* current = *head;
    while (current != NULL) {
        Node* next = current->next;
        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}

// Helper functions for merge sort
Node* splitList(Node* head) {
    Node* fast = head;
    Node* slow = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* temp = slow->next;
    slow->next = NULL;
    return temp;
}

Node* mergeTwoSorted(Node* a, Node* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    Node* result = NULL;
    if (a->data <= b->data) {
        result = a;
        result->next = mergeTwoSorted(a->next, b);
    } else {
        result = b;
        result->next = mergeTwoSorted(a, b->next);
    }
    return result;
}

// Merge sort - Sorts by dividing list in half, sorting each half, then merging
void mergeSort(Node** head) {
    Node* h = *head;
    if (h == NULL || h->next == NULL) return;
    Node* second = splitList(h);
    mergeSort(&h);
    mergeSort(&second);
    *head = mergeTwoSorted(h, second);
}

// Selection sort - Sorts by repeatedly finding minimum element and placing it at the beginning
void selectionSort(Node** head) {
    Node* temp = *head;
    while (temp != NULL) {
        Node* min = temp;
        Node* r = temp->next;
        while (r != NULL) {
            if (min->data > r->data) {
                min = r;
            }
            r = r->next;
        }
        int x = temp->data;
        temp->data = min->data;
        min->data = x;
        temp = temp->next;
    }
}

// ==================== DETECTION & ANALYSIS OPERATIONS ====================

// Detect loop/cycle - Checks if the list contains a cycle where a node points back to a previous node
bool detectLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

// Find loop starting point - Identifies the first node where the cycle begins
Node* findLoopStart(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return NULL;
}

// Remove loop - Breaks the cycle by removing the link that creates it
void removeLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            if (slow == fast) {
                while (fast->next != slow) {
                    fast = fast->next;
                }
            } else {
                while (slow->next != fast->next) {
                    slow = slow->next;
                    fast = fast->next;
                }
            }
            fast->next = NULL;
            return;
        }
    }
}

// Check if list is palindrome - Determines if the list reads the same forwards and backwards
bool isPalindrome(Node* head) {
    if (head == NULL || head->next == NULL) return true;
    Node* slow = head;
    Node* fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* secondHalf = slow->next;
    slow->next = NULL;
    Node* prev = NULL;
    Node* current = secondHalf;
    while (current != NULL) {
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    secondHalf = prev;
    Node* p1 = head;
    Node* p2 = secondHalf;
    bool result = true;
    while (p2 != NULL) {
        if (p1->data != p2->data) {
            result = false;
            break;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    return result;
}

// Find intersection point of two lists - Finds the node where two linked lists merge
Node* findIntersection(Node* head1, Node* head2) {
    int len1 = countNodes(head1);
    int len2 = countNodes(head2);
    int diff = abs(len1 - len2);
    Node* ptr1 = head1;
    Node* ptr2 = head2;
    if (len1 > len2) {
        for (int i = 0; i < diff; i++) {
            ptr1 = ptr1->next;
        }
    } else {
        for (int i = 0; i < diff; i++) {
            ptr2 = ptr2->next;
        }
    }
    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1 == ptr2) {
            return ptr1;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return NULL;
}

// ==================== MODIFICATION OPERATIONS ====================

// Swap nodes - Exchanges the positions of two nodes by changing links
void swapNodes(Node** head, int x, int y) {
    if (x == y) return;
    Node *prevX = NULL, *currX = *head;
    while (currX && currX->data != x) {
        prevX = currX;
        currX = currX->next;
    }
    Node *prevY = NULL, *currY = *head;
    while (currY && currY->data != y) {
        prevY = currY;
        currY = currY->next;
    }
    if (currX == NULL || currY == NULL) return;
    if (prevX != NULL) {
        prevX->next = currY;
    } else {
        *head = currY;
    }
    if (prevY != NULL) {
        prevY->next = currX;
    } else {
        *head = currX;
    }
    Node* temp = currX->next;
    currX->next = currY->next;
    currY->next = temp;
}

// Rotate list right by k positions - Shifts all nodes k positions to the right
void rotateRight(Node** head, int k) {
    if (*head == NULL || k == 0) return;
    int len = countNodes(*head);
    k = k % len;
    if (k == 0) return;
    Node* temp = *head;
    for (int i = 1; i < len - k; i++) {
        temp = temp->next;
    }
    Node* newHead = temp->next;
    temp->next = NULL;
    temp = newHead;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = *head;
    *head = newHead;
}

// Rotate list left by k positions - Shifts all nodes k positions to the left
void rotateLeft(Node** head, int k) {
    if (*head == NULL || k == 0) return;
    int len = countNodes(*head);
    k = k % len;
    if (k == 0) return;
    Node* temp = *head;
    for (int i = 1; i < k; i++) {
        temp = temp->next;
    }
    Node* newHead = temp->next;
    temp->next = NULL;
    temp = newHead;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = *head;
    *head = newHead;
}

// Remove duplicates (sorted list) - Eliminates consecutive duplicate values from a sorted list
void removeDuplicatesSorted(Node* head) {
    Node* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

// Remove duplicates (unsorted list) - Eliminates all duplicate values from an unsorted list
void removeDuplicatesUnsorted(Node** head) {
    if (*head == NULL) return;
    Node* ptr1 = *head;
    while (ptr1 != NULL && ptr1->next != NULL) {
        Node* ptr2 = ptr1;
        while (ptr2->next != NULL) {
            if (ptr1->data == ptr2->next->data) {
                Node* temp = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(temp);
            } else {
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
}

// Partition list around a value - Rearranges nodes so smaller values come before larger values
void partition(Node** head, int x) {
    Node* lessHead = NULL;
    Node* lessTail = NULL;
    Node* greaterHead = NULL;
    Node* greaterTail = NULL;
    Node* current = *head;
    while (current != NULL) {
        Node* next = current->next;
        current->next = NULL;
        if (current->data < x) {
            if (lessHead == NULL) {
                lessHead = lessTail = current;
            } else {
                lessTail->next = current;
                lessTail = current;
            }
        } else {
            if (greaterHead == NULL) {
                greaterHead = greaterTail = current;
            } else {
                greaterTail->next = current;
                greaterTail = current;
            }
        }
        current = next;
    }
    if (lessHead == NULL) {
        *head = greaterHead;
        return;
    }
    lessTail->next = greaterHead;
    *head = lessHead;
}

// ==================== MERGING & SPLITTING OPERATIONS ====================

// Merge two sorted lists - Combines two sorted lists into one sorted list
Node* mergeTwoSortedLists(Node* l1, Node* l2) {
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;
    Node* result = NULL;
    if (l1->data <= l2->data) {
        result = l1;
        result->next = mergeTwoSortedLists(l1->next, l2);
    } else {
        result = l2;
        result->next = mergeTwoSortedLists(l1, l2->next);
    }
    return result;
}

// Merge two unsorted lists - Concatenates two lists without regard to order
void mergeTwoUnsortedLists(Node** head1, Node* head2) {
    if (*head1 == NULL) {
        *head1 = head2;
        return;
    }
    Node* temp = *head1;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = head2;
}

// Split list into two halves - Divides the list into two equal or near-equal parts
void splitIntoTwoHalves(Node* head, Node** first, Node** second) {
    Node* slow = head;
    Node* fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *first = head;
    *second = slow->next;
    slow->next = NULL;
}

// Segregate even and odd nodes - Rearranges so all even-valued nodes come before odd-valued nodes
void segregateEvenOdd(Node** head) {
    Node* evenHead = NULL;
    Node* evenTail = NULL;
    Node* oddHead = NULL;
    Node* oddTail = NULL;
    Node* current = *head;
    while (current != NULL) {
        if (current->data % 2 == 0) {
            if (evenHead == NULL) {
                evenHead = evenTail = current;
            } else {
                evenTail->next = current;
                evenTail = current;
            }
        } else {
            if (oddHead == NULL) {
                oddHead = oddTail = current;
            } else {
                oddTail->next = current;
                oddTail = current;
            }
        }
        current = current->next;
    }
    if (evenHead == NULL || oddHead == NULL) return;
    evenTail->next = oddHead;
    oddTail->next = NULL;
    *head = evenHead;
}

// ==================== MATHEMATICAL OPERATIONS ====================

// Add two numbers represented as linked lists - Performs addition where each node contains a digit
Node* addTwoNumbers(Node* l1, Node* l2) {
    Node* dummy = createNode(0);
    Node* temp = dummy;
    int carry = 0;
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int sum = carry;
        if (l1 != NULL) {
            sum += l1->data;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->data;
            l2 = l2->next;
        }
        carry = sum / 10;
        temp->next = createNode(sum % 10);
        temp = temp->next;
    }
    Node* result = dummy->next;
    free(dummy);
    return result;
}

// Helper function to reverse for subtraction
Node* reverseForMath(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

// Subtract two numbers - Performs subtraction where each node contains a digit
Node* subtractTwoNumbers(Node* l1, Node* l2) {
    l1 = reverseForMath(l1);
    l2 = reverseForMath(l2);
    Node* dummy = createNode(0);
    Node* temp = dummy;
    int borrow = 0;
    while (l1 != NULL) {
        int diff = l1->data - borrow;
        if (l2 != NULL) {
            diff -= l2->data;
            l2 = l2->next;
        }
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        temp->next = createNode(diff);
        temp = temp->next;
        l1 = l1->next;
    }
    Node* result = reverseForMath(dummy->next);
    free(dummy);
    return result;
}

// Multiply two numbers - Performs multiplication where each node contains a digit
Node* multiplyTwoNumbers(Node* l1, Node* l2) {
    if (l1 == NULL || l2 == NULL) return createNode(0);
    Node* result = createNode(0);
    Node* temp2 = l2;
    int position = 0;
    while (temp2 != NULL) {
        Node* temp1 = l1;
        int carry = 0;
        Node* tempResult = NULL;
        Node* tempTail = NULL;
        for (int i = 0; i < position; i++) {
            Node* zero = createNode(0);
            if (tempResult == NULL) {
                tempResult = tempTail = zero;
            } else {
                tempTail->next = zero;
                tempTail = zero;
            }
        }
        while (temp1 != NULL || carry != 0) {
            int prod = carry;
            if (temp1 != NULL) {
                prod += temp1->data * temp2->data;
                temp1 = temp1->next;
            }
            carry = prod / 10;
            Node* newNode = createNode(prod % 10);
            if (tempResult == NULL) {
                tempResult = tempTail = newNode;
            } else {
                tempTail->next = newNode;
                tempTail = newNode;
            }
        }
        result = addTwoNumbers(result, tempResult);
        temp2 = temp2->next;
        position++;
    }
    return result;
}

// ==================== UTILITY OPERATIONS ====================

// Clone/copy a list - Creates an exact duplicate of the entire list
Node* cloneList(Node* head) {
    if (head == NULL) return NULL;
    Node* newHead = NULL;
    Node* temp = head;
    Node* newTemp = NULL;
    while (temp != NULL) {
        Node* newNode = createNode(temp->data);
        if (newHead == NULL) {
            newHead = newTemp = newNode;
        } else {
            newTemp->next = newNode;
            newTemp = newNode;
        }
        temp = temp->next;
    }
    return newHead;
}

// Compare two lists for equality - Checks if two lists have identical values in same order
bool compareLists(Node* head1, Node* head2) {
    Node* temp1 = head1;
    Node* temp2 = head2;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data != temp2->data) {
            return false;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return (temp1 == NULL && temp2 == NULL);
}

// Clear entire list - Removes all nodes and frees memory
void clearList(Node** head) {
    Node* current = *head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Check if list is empty - Returns whether the list contains any nodes
bool isEmpty(Node* head) {
    return head == NULL;
}

// Get value at specific index - Retrieves the data stored at a given position
int getValueAtIndex(Node* head, int index) {
    Node* temp = head;
    int count = 0;
    while (temp != NULL && count < index) {
        temp = temp->next;
        count++;
    }
    if (temp == NULL) {
        printf("Index out of bounds\n");
        return -1;
    }
    return temp->data;
}

// Update value at specific index - Modifies the data stored at a given position
void updateValueAtIndex(Node* head, int index, int newValue) {
    Node* temp = head;
    int count = 0;
    while (temp != NULL && count < index) {
        temp = temp->next;
        count++;
    }
    if (temp == NULL) {
        printf("Index out of bounds\n");
        return;
    }
    temp->data = newValue;
}

// ==================== MAIN FUNCTION (DEMO OF ALL OPERATIONS) ====================

int main() {
    Node* head = NULL;
    Node* head2 = NULL;
    Node* result = NULL;
    
    printf("========== SINGLY LINKED LIST - ALL OPERATIONS DEMO ==========\n\n");
    
    // ========== INSERTION OPERATIONS ==========
    printf("========== 1. INSERTION OPERATIONS ==========\n");
    
    printf("\n1.1 Insert at Beginning:\n");
    insertAtBeginning(&head, 10);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 30);
    display(head);
    
    printf("\n1.2 Insert at End:\n");
    insertAtEnd(&head, 5);
    insertAtEnd(&head, 15);
    display(head);
    
    printf("\n1.3 Insert at Position 2:\n");
    insertAtPosition(&head, 25, 2);
    display(head);
    
    printf("\n1.4 Insert After Node (after node with value 10):\n");
    Node* nodeToFind = head;
    while (nodeToFind && nodeToFind->data != 10) nodeToFind = nodeToFind->next;
    if (nodeToFind) insertAfterNode(nodeToFind, 12);
    display(head);
    
    printf("\n1.5 Insert Before Node (before node with value 5):\n");
    nodeToFind = head;
    while (nodeToFind && nodeToFind->data != 5) nodeToFind = nodeToFind->next;
    if (nodeToFind) insertBeforeNode(&head, nodeToFind, 3);
    display(head);
    
    clearList(&head);
    printf("\n1.6 Insert in Sorted Order:\n");
    insertSorted(&head, 10);
    insertSorted(&head, 5);
    insertSorted(&head, 20);
    insertSorted(&head, 15);
    insertSorted(&head, 8);
    display(head);
    
    // ========== DELETION OPERATIONS ==========
    printf("\n\n========== 2. DELETION OPERATIONS ==========\n");
    
    printf("\n2.1 Delete from Beginning:\n");
    deleteFromBeginning(&head);
    display(head);
    
    printf("\n2.2 Delete from End:\n");
    deleteFromEnd(&head);
    display(head);
    
    printf("\n2.3 Delete at Position 1:\n");
    deleteAtPosition(&head, 1);
    display(head);
    
    printf("\n2.4 Delete by Value (delete 10):\n");
    deleteByValue(&head, 10);
    display(head);
    
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    printf("\n2.5 Delete All Occurrences (delete all 20s):\n");
    printf("Before: ");
    display(head);
    deleteAllOccurrences(&head, 20);
    printf("After: ");
    display(head);
    
    printf("\n2.6 Delete Given Node:\n");
    nodeToFind = head;
    if (nodeToFind && nodeToFind->next) {
        Node* toDelete = nodeToFind->next;
        printf("Deleting node with value: %d\n", toDelete->data);
        deleteNode(&head, toDelete);
        display(head);
    }
    
    // ========== TRAVERSAL OPERATIONS ==========
    printf("\n\n========== 3. TRAVERSAL OPERATIONS ==========\n");
    
    clearList(&head);
    for (int i = 10; i <= 50; i += 10) insertAtEnd(&head, i);
    
    printf("\n3.1 Display List:\n");
    display(head);
    
    printf("\n3.2 Count Nodes: %d\n", countNodes(head));
    
    printf("\n3.3 Traverse (iterating through list - no output, just traversal)\n");
    traverse(head);
    printf("Traversal complete!\n");
    
    // ========== SEARCH OPERATIONS ==========
    printf("\n\n========== 4. SEARCH OPERATIONS ==========\n");
    
    printf("\n4.1 Search for Value 30: %s\n", search(head, 30) ? "Found" : "Not Found");
    printf("4.2 Search for Value 100: %s\n", search(head, 100) ? "Found" : "Not Found");
    
    printf("\n4.3 Find Node at Position 2:\n");
    Node* foundNode = findNodeAtPosition(head, 2);
    if (foundNode) printf("Value at position 2: %d\n", foundNode->data);
    
    printf("\n4.4 Find Middle Node:\n");
    Node* middleNode = findMiddle(head);
    if (middleNode) printf("Middle value: %d\n", middleNode->data);
    
    printf("\n4.5 Find 2nd Node from End:\n");
    Node* nthNode = findNthFromEnd(head, 2);
    if (nthNode) printf("2nd node from end: %d\n", nthNode->data);
    
    // ========== REVERSAL OPERATIONS ==========
    printf("\n\n========== 5. REVERSAL OPERATIONS ==========\n");
    
    printf("\n5.1 Reverse Iterative:\n");
    printf("Before: ");
    display(head);
    reverseIterative(&head);
    printf("After: ");
    display(head);
    
    printf("\n5.2 Reverse Recursive:\n");
    printf("Before: ");
    display(head);
    reverseRecursive(&head);
    printf("After: ");
    display(head);
    
    printf("\n5.3 Reverse in Groups of 2:\n");
    printf("Before: ");
    display(head);
    head = reverseInGroups(head, 2);
    printf("After: ");
    display(head);
    
    reverseIterative(&head); // Reset to original order
    printf("\n5.4 Reverse Between Positions 2 and 4:\n");
    printf("Before: ");
    display(head);
    reverseBetween(&head, 2, 4);
    printf("After: ");
    display(head);
    
    // ========== SORTING OPERATIONS ==========
    printf("\n\n========== 6. SORTING OPERATIONS ==========\n");
    
    clearList(&head);
    int arr[] = {50, 20, 40, 10, 30};
    for (int i = 0; i < 5; i++) insertAtEnd(&head, arr[i]);
    
    printf("\n6.1 Bubble Sort:\n");
    printf("Before: ");
    display(head);
    bubbleSort(&head);
    printf("After: ");
    display(head);
    
    clearList(&head);
    for (int i = 0; i < 5; i++) insertAtEnd(&head, arr[i]);
    printf("\n6.2 Insertion Sort:\n");
    printf("Before: ");
    display(head);
    insertionSort(&head);
    printf("After: ");
    display(head);
    
    clearList(&head);
    for (int i = 0; i < 5; i++) insertAtEnd(&head, arr[i]);
    printf("\n6.3 Merge Sort:\n");
    printf("Before: ");
    display(head);
    mergeSort(&head);
    printf("After: ");
    display(head);
    
    clearList(&head);
    for (int i = 0; i < 5; i++) insertAtEnd(&head, arr[i]);
    printf("\n6.4 Selection Sort:\n");
    printf("Before: ");
    display(head);
    selectionSort(&head);
    printf("After: ");
    display(head);
    
    // ========== DETECTION & ANALYSIS OPERATIONS ==========
    printf("\n\n========== 7. DETECTION & ANALYSIS OPERATIONS ==========\n");
    
    clearList(&head);
    for (int i = 10; i <= 50; i += 10) insertAtEnd(&head, i);
    
    printf("\n7.1 Detect Loop:\n");
    printf("Loop detected: %s\n", detectLoop(head) ? "Yes" : "No");
    
    // Create a loop for testing
    Node* tail = head;
    while (tail->next) tail = tail->next;
    Node* loopStart = head->next->next; // Third node
    tail->next = loopStart;
    
    printf("\n7.2 Detect Loop (after creating loop):\n");
    printf("Loop detected: %s\n", detectLoop(head) ? "Yes" : "No");
    
    printf("\n7.3 Find Loop Starting Point:\n");
    Node* loopNode = findLoopStart(head);
    if (loopNode) printf("Loop starts at node with value: %d\n", loopNode->data);
    
    printf("\n7.4 Remove Loop:\n");
    removeLoop(head);
    printf("Loop removed. Loop detected: %s\n", detectLoop(head) ? "Yes" : "No");
    display(head);
    
    clearList(&head);
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 1);
    printf("\n7.5 Check if Palindrome:\n");
    display(head);
    printf("Is palindrome: %s\n", isPalindrome(head) ? "Yes" : "No");
    
    clearList(&head);
    clearList(&head2);
    for (int i = 1; i <= 5; i++) insertAtEnd(&head, i);
    for (int i = 10; i <= 12; i++) insertAtEnd(&head2, i);
    
    // Create intersection
    Node* intersectNode = createNode(100);
    intersectNode->next = createNode(200);
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = intersectNode;
    temp = head2;
    while (temp->next) temp = temp->next;
    temp->next = intersectNode;
    
    printf("\n7.6 Find Intersection Point:\n");
    Node* intersection = findIntersection(head, head2);
    if (intersection) printf("Intersection at node with value: %d\n", intersection->data);
    
    // Clean up intersection
    temp = head;
    while (temp && temp->next != intersectNode) temp = temp->next;
    if (temp) temp->next = NULL;
    temp = head2;
    while (temp && temp->next != intersectNode) temp = temp->next;
    if (temp) temp->next = NULL;
    clearList(&intersectNode);
    
    // ========== MODIFICATION OPERATIONS ==========
    printf("\n\n========== 8. MODIFICATION OPERATIONS ==========\n");
    
    clearList(&head);
    for (int i = 10; i <= 50; i += 10) insertAtEnd(&head, i);
    
    printf("\n8.1 Swap Nodes (swap 20 and 40):\n");
    printf("Before: ");
    display(head);
    swapNodes(&head, 20, 40);
    printf("After: ");
    display(head);
    
    printf("\n8.2 Rotate Right by 2:\n");
    printf("Before: ");
    display(head);
    rotateRight(&head, 2);
    printf("After: ");
    display(head);
    
    printf("\n8.3 Rotate Left by 2:\n");
    printf("Before: ");
    display(head);
    rotateLeft(&head, 2);
    printf("After: ");
    display(head);
    
    clearList(&head);
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 30);
    printf("\n8.4 Remove Duplicates (Sorted List):\n");
    printf("Before: ");
    display(head);
    removeDuplicatesSorted(head);
    printf("After: ");
    display(head);
    
    clearList(&head);
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 20);
    printf("\n8.5 Remove Duplicates (Unsorted List):\n");
    printf("Before: ");
    display(head);
    removeDuplicatesUnsorted(&head);
    printf("After: ");
    display(head);
    
    clearList(&head);
    int arr2[] = {50, 20, 80, 10, 60, 30};
    for (int i = 0; i < 6; i++) insertAtEnd(&head, arr2[i]);
    printf("\n8.6 Partition Around Value 40:\n");
    printf("Before: ");
    display(head);
    partition(&head, 40);
    printf("After (all <40 before all >=40): ");
    display(head);
    
    // ========== MERGING & SPLITTING OPERATIONS ==========
    printf("\n\n========== 9. MERGING & SPLITTING OPERATIONS ==========\n");
    
    clearList(&head);
    clearList(&head2);
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 50);
    insertAtEnd(&head2, 20);
    insertAtEnd(&head2, 40);
    insertAtEnd(&head2, 60);
    
    printf("\n9.1 Merge Two Sorted Lists:\n");
    printf("List 1: ");
    display(head);
    printf("List 2: ");
    display(head2);
    result = mergeTwoSortedLists(head, head2);
    printf("Merged: ");
    display(result);
    head = head2 = NULL;
    
    clearList(&result);
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head2, 30);
    insertAtEnd(&head2, 40);
    printf("\n9.2 Merge Two Unsorted Lists:\n");
    printf("List 1: ");
    display(head);
    printf("List 2: ");
    display(head2);
    mergeTwoUnsortedLists(&head, head2);
    printf("Merged: ");
    display(head);
    head2 = NULL;
    
    clearList(&head);
    for (int i = 10; i <= 60; i += 10) insertAtEnd(&head, i);
    printf("\n9.3 Split List into Two Halves:\n");
    printf("Original: ");
    display(head);
    Node *first = NULL, *second = NULL;
    splitIntoTwoHalves(head, &first, &second);
    printf("First half: ");
    display(first);
    printf("Second half: ");
    display(second);
    
    clearList(&first);
    clearList(&second);
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 4);
    insertAtEnd(&head, 5);
    printf("\n9.4 Segregate Even and Odd:\n");
    printf("Before: ");
    display(head);
    segregateEvenOdd(&head);
    printf("After: ");
    display(head);
    
    // ========== MATHEMATICAL OPERATIONS ==========
    printf("\n\n========== 10. MATHEMATICAL OPERATIONS ==========\n");
    
    clearList(&head);
    clearList(&head2);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 4);
    insertAtEnd(&head, 3);
    insertAtEnd(&head2, 5);
    insertAtEnd(&head2, 6);
    insertAtEnd(&head2, 4);
    
    printf("\n10.1 Add Two Numbers (342 + 465 = 807):\n");
    printf("Number 1 (reversed): ");
    display(head);
    printf("Number 2 (reversed): ");
    display(head2);
    result = addTwoNumbers(head, head2);
    printf("Sum (reversed): ");
    display(result);
    
    clearList(&head);
    clearList(&head2);
    clearList(&result);
    insertAtEnd(&head, 5);
    insertAtEnd(&head, 0);
    insertAtEnd(&head, 3);
    insertAtEnd(&head2, 2);
    insertAtEnd(&head2, 1);
    
    printf("\n10.2 Subtract Two Numbers (305 - 12 = 293):\n");
    printf("Number 1 (reversed): ");
    display(head);
    printf("Number 2 (reversed): ");
    display(head2);
    result = subtractTwoNumbers(head, head2);
    printf("Difference (reversed): ");
    display(result);
    
    clearList(&head);
    clearList(&head2);
    clearList(&result);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 2);
    insertAtEnd(&head2, 4);
    
    printf("\n10.3 Multiply Two Numbers (23 * 4 = 92):\n");
    printf("Number 1 (reversed): ");
    display(head);
    printf("Number 2 (reversed): ");
    display(head2);
    result = multiplyTwoNumbers(head, head2);
    printf("Product (reversed): ");
    display(result);
    
    // ========== UTILITY OPERATIONS ==========
    printf("\n\n========== 11. UTILITY OPERATIONS ==========\n");
    
    clearList(&head);
    clearList(&head2);
    clearList(&result);
    for (int i = 10; i <= 50; i += 10) insertAtEnd(&head, i);
    
    printf("\n11.1 Clone List:\n");
    printf("Original: ");
    display(head);
    Node* cloned = cloneList(head);
    printf("Cloned: ");
    display(cloned);
    
    printf("\n11.2 Compare Lists:\n");
    printf("Original and Cloned equal: %s\n", compareLists(head, cloned) ? "Yes" : "No");
    insertAtEnd(&cloned, 60);
    printf("After adding 60 to cloned, equal: %s\n", compareLists(head, cloned) ? "Yes" : "No");
    
    printf("\n11.3 Check if Empty:\n");
    printf("Is head empty: %s\n", isEmpty(head) ? "Yes" : "No");
    printf("Is head2 empty: %s\n", isEmpty(head2) ? "Yes" : "No");
    
    printf("\n11.4 Get Value at Index 2: %d\n", getValueAtIndex(head, 2));
    
    printf("\n11.5 Update Value at Index 2 to 99:\n");
    printf("Before: ");
    display(head);
    updateValueAtIndex(head, 2, 99);
    printf("After: ");
    display(head);
    
    printf("\n11.6 Clear List:\n");
    clearList(&head);
    clearList(&cloned);
    printf("Lists cleared. Is head empty: %s\n", isEmpty(head) ? "Yes" : "No");
    
    printf("\n\n========== ALL OPERATIONS DEMO COMPLETE! ==========\n");
    
    return 0;
}
