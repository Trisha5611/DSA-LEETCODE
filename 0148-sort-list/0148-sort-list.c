/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* merge(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;

    dummy.next = NULL;

    while (l1 != NULL && l2 != NULL) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
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

struct ListNode* sortList(struct ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;

    struct ListNode* slow = head;
    struct ListNode* fast = head->next;

    // Find middle of linked list
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    struct ListNode* mid = slow->next;
    slow->next = NULL;

    // Sort both halves
    struct ListNode* left = sortList(head);
    struct ListNode* right = sortList(mid);

    // Merge sorted halves
    return merge(left, right);
}