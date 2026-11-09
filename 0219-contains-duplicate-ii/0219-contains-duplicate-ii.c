#include <stdbool.h>
#include <stdlib.h>

#define SIZE 200003

typedef struct Node {
    int value;
    int index;
    struct Node* next;
} Node;

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {

    if (k == 0)
        return false;

    Node* table[SIZE] = {NULL};

    for (int i = 0; i < numsSize; i++) {

        int hash = ((unsigned int)nums[i]) % SIZE;

        Node* temp = table[hash];

        while (temp != NULL) {

            if (temp->value == nums[i]) {

                if (i - temp->index <= k)
                    return true;

                temp->index = i;
                break;
            }

            temp = temp->next;
        }

        if (temp == NULL) {

            Node* newNode = malloc(sizeof(Node));

            newNode->value = nums[i];
            newNode->index = i;
            newNode->next = table[hash];

            table[hash] = newNode;
        }
    }

    return false;
}