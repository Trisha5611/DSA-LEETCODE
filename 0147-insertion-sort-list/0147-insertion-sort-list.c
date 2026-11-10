/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* insertionSortList(struct ListNode* head) {
    struct ListNode dummy;
    dummy.next = NULL;

    struct ListNode* curr = head;

    while (curr != NULL) {
        struct ListNode* next = curr->next;

        struct ListNode* prev = &dummy;

        // Find correct position
        while (prev->next != NULL && prev->next->val < curr->val) {
            prev = prev->next;
        }

        // Insert current node
        curr->next = prev->next;
        prev->next = curr;

        curr = next;
    }

    return dummy.next;
}
