

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    if (l1 == NULL || l2 == NULL) {
        return NULL;
    }

    struct ListNode *res = NULL, *p = NULL;
    int t = 0;
    while (l1 != NULL && l2 != NULL) {
        struct ListNode *l = malloc(sizeof(*l));
        l->next = NULL;
        l->val = (l1->val + l2->val + t) % 10;
        t = (l1->val + l2->val + t) / 10;

        if (res == NULL) {
            res = l;
        } else {
            p->next = l;
        }
        p = l;
        l1 = l1->next;
        l2 = l2->next;
    }

    struct ListNode *lp1 = (l1 != NULL) ? l1 : l2;
    while (lp1 != NULL) {
        struct ListNode *l = malloc(sizeof(*l));
        l->next = NULL;
        l->val = (lp1->val + t) %10;
        t = (lp1->val+ t) / 10;

        p->next = l;
        p = l;
        lp1 = lp1->next;
    }

    if (t != 0) {
        struct ListNode *l = malloc(sizeof(*l));
        l->next = NULL;
        l->val = t;
        p->next = l;
    }

    return res;
}
