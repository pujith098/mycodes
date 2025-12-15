#include "rearrange_ll.h"
#include "../common/logger.h"

void rearrange_odd_even(struct node **head) {
    if (!head || !(*head)) {
        logger_warn("Received NULL list");
        return;
    }
    if (!(*head)->next) {
        logger_info("Single node list, nothing to rearrange");
        return;
    }

    struct node *odd = *head;
    struct node *even = (*head)->next;
    struct node *even_head = even;

    while (odd && even && even->next) {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    odd->next = even_head;

    logger_info("Rearrange completed");
}

