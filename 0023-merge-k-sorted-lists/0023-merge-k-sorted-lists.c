/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {

    struct ListNode dummy;
    struct ListNode* tail = &dummy;

    dummy.next = NULL;

    while (l1 != NULL && l2 != NULL) {

        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        }
        else {
            tail->next = l2;
            l2 = l2->next;
        }

        tail = tail->next;
    }

    if (l1 != NULL)
        tail->next = l1;
    else
        tail->next = l2;

    return dummy.next;
}
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0)
        return NULL;

    while (listsSize > 1) {

        int index = 0;

        for (int i = 0; i < listsSize; i += 2) {

            if (i + 1 < listsSize)
                lists[index++] = mergeTwoLists(lists[i], lists[i + 1]);
            else
                lists[index++] = lists[i];
        }

        listsSize = index;
    }

    return lists[0];
}