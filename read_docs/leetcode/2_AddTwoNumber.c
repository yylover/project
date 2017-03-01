
/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

 */


/*
    思路: 向后循环直到l1 == NULL && l2 == NULL && 进位 == 0
 */

int lengthOfLongestSubstring(char* s) {
unsigned char set[256];
memset(set, 0);
}



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *lp1 = l1, *lp2 = l2;
    struct ListNode *head = NULL, *p = NULL;

    int mod = 0;
    while (l1 != NULL || l2 != NULL || mod != 0) {

        if (l1 != NULL) {
            mod += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            mod += l2->val;
            l2 = l2->next;
        }

        struct ListNode *temp = (struct ListNode *) malloc(sizeof(*p));
        temp->val = mod % 10;
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
        } else {
            p->next = temp;
        }
        p = temp;

        mod /= 10;

    }

    return head;

}
