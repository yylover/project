/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* insertionSortList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct ListNode *ptr = NULL, *pre = NULL, *temp = NULL;
    ptr = head;
    while (ptr->next != NULL) {
        pre = head;
        if (pre->val > ptr->next->val) {
            temp = ptr->next;
            ptr->next = temp->next;

            temp->next = head;
            head = temp;
        } else {
            while (pre->next->val < ptr->next->val && pre != ptr) {
                pre = pre->next;
            }
            if (pre != ptr) {
                temp = ptr->next;
                ptr->next = temp->next;

                temp->next = pre->next;
                pre->next = temp;
            } else {
                ptr = ptr->next;
            }
        }
    }
    return head;
}
