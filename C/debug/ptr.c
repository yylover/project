#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode ** findLeastOne(struct ListNode ** lists, int listSize) {
    struct ListNode **node = NULL;
    for (int i = 0; i< listSize; i++) {
        if (lists[i] != NULL) {
            if (node == NULL) {
                *node = lists[i];
            }else if (lists[i]->val < (*node)->val) {
                *node = lists[i];
            }
        }
    }

    return node;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    int num = 0;
    struct ListNode *head = NULL;
    struct ListNode *ptr = NULL;
    while (1) { // 长度不可知，所以while循环
        struct ListNode **t = findLeastOne(lists, listsSize);
        // printf("%d \n", *t);
        if (t == NULL || *t == NULL) {//退出条件
            break;
        }
        printf("%d ", (*t)->val);

        //为什么返回数组中的坐标，因为返回指针不能改变原来的值，返回坐标或
        struct ListNode *temp = (struct ListNode *) malloc(sizeof(*temp));
        temp->val = (*t)->val;
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
            ptr = temp;
        } else {
            ptr->next = temp;
            ptr = ptr->next;
        }
        *t = (*t)->next;
        num++;
    }

    return head;
}

int ** test(int *b) {
    int **c = NULL;
    // *c = b;
    c = &b;
    return c;
}

int main() {
    int b = 1;
    int d = 2;
    int *a = &b;
    // int **c = test(a);
    // int **c = &a;
    int **c = NULL;
    *c = a;
    *c = &d;

    printf("%d\n", *a);
    printf("%d\n", **c);


    return 0;

}
