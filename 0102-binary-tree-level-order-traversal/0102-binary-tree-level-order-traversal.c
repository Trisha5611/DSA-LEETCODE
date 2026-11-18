/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
*returnColumnSizes = NULL;

if (root == NULL)
return NULL;

int** result = malloc(2000 * sizeof(int*));
*returnColumnSizes = malloc(2000 * sizeof(int));

struct TreeNode* queue[2000];
int front = 0, rear = 0;

queue[rear++] = root;

while (front < rear) {

 int size = rear - front;

 int* level = malloc(size * sizeof(int));

 for (int i = 0; i < size; i++) {

     struct TreeNode* curr = queue[front++];

     level[i] = curr->val;

     if (curr->left != NULL)
         queue[rear++] = curr->left;

     if (curr->right != NULL)
         queue[rear++] = curr->right;
 }

 result[*returnSize] = level;
 (*returnColumnSizes)[*returnSize] = size;

 (*returnSize)++;

}

return result;
}