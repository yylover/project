/**



*/



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
int findLeastOne(struct ListNode ** lists, int listSize) {
    struct ListNode *node = NULL;
    int t = -1;
    for (int i = 0; i< listSize; i++) {
        if (lists[i] != NULL) {
            if (node == NULL) {
                node = lists[i];
                t = i;
            }else if (lists[i]->val < node->val) {
                node = lists[i];
                t = i;
            }
        }
    }
    return t;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    int num = 0;
    struct ListNode *head = NULL;
    struct ListNode *ptr = NULL;
    while (true) { // 长度不可知，所以while循环
        int t = findLeastOne(lists, listsSize);
        printf("%d\n", t);
        if (t == -1) {//退出条件
            break;
        }

        //为什么返回数组中的坐标，因为返回指针不能改变原来的值，返回坐标或
        struct ListNode *temp = (struct ListNode *) malloc(sizeof(*temp));
        temp->val = lists[t]->val;
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
            ptr = temp;
        } else {
            ptr->next = temp;
            ptr = ptr->next;
        }
        lists[t] = lists[t]->next;
        // node = node->next;
        num++;
    }

    return head;
}


/**
 * 指针处理方式
 * @param  lists    [description]
 * @param  listSize [description]
 * @return          [description]
 */
struct ListNode ** findLeastOne(struct ListNode ** lists, int listSize) {
    struct ListNode **node = NULL;
    for (int i = 0; i< listSize; i++) {
        if (lists[i] != NULL) {
            if (node == NULL) {
                node = &lists[i];
            } else if (lists[i]->val < (*node) ->val) {
                node = &lists[i];
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
        if (t == NULL) {//退出条件
            break;
        }

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
