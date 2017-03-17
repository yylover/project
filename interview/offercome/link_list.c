#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int m_nValue;
    struct ListNode *m_pNext;
} ;

int main() {
    return 0;
}



//归并排序
struct ListNode * mergeList(struct ListNode *p1, struct ListNode *p2) {
    struct ListNode *phead = NULL;
    struct ListNode *ptr = NULL;
    while (p1 != NULL && p2 != NULL) {
        if (p1->val < p2->val) {
            if (phead == NULL) {
                phead = p1;
                ptr = p1;
            } else {
                ptr->next = p1;
                ptr =  ptr->next;
            }
            p1 = p1->next;
        } else {
            if (phead == NULL) {
                phead = p2;
                ptr = p2;
            } else {
                ptr->next = p2;
                ptr =  ptr->next;
            }
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        ptr->next = p1;
        p1 = p1->next;
        ptr = ptr->next;
    }

    while (p2 != NULL) {
        ptr->next = p2;
        p2 = p2->next;
        ptr = ptr->next;
    }

    return phead;
}

struct ListNode * findHalf(struct ListNode *head) {
    struct ListNode *p1 = head, *p2 = head;
    while (p2 != NULL) {
        p2 = p2->next;
        if (p2 != NULL) {
            p2 = p2->next;
        }

        if (p2 != NULL) {
            p1 = p1->next;
        }
    }
    return p1;
}



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* sortList(struct ListNode* head) {
     if (head != NULL && head->next != NULL) {
        struct ListNode *ptr = findHalf(head);
        struct ListNode *p2 = ptr->next;
        ptr->next = NULL;

        head = sortList(head);
        p2   = sortList(p2);

        head = mergeList(head, p2);

    }
    return head;
}
