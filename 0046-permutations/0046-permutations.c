/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 void backtrack(int* nums, int n, int* temp, int* visited,
               int** result, int* returnSize) {

    if (*returnSize >= 720)
        return;

    int count = 0;

    for (int i = 0; i < n; i++) {
        if (visited[i])
            count++;
    }

    if (count == n) {
        result[*returnSize] = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            result[*returnSize][i] = temp[i];
        }

        (*returnSize)++;
        return;
    }

    for (int i = 0; i < n; i++) {

        if (!visited[i]) {

            visited[i] = 1;
            temp[count] = nums[i];

            backtrack(nums, n, temp, visited,
                      result, returnSize);

            visited[i] = 0;
        }
    }
}
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
      *returnSize = 0;

    int total = 1;

    for (int i = 1; i <= numsSize; i++)
        total *= i;

    int** result = malloc(total * sizeof(int*));

    int* temp = malloc(numsSize * sizeof(int));
    int* visited = calloc(numsSize, sizeof(int));

    backtrack(nums, numsSize, temp, visited,
              result, returnSize);

    *returnColumnSizes = malloc(*returnSize * sizeof(int));

    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = numsSize;
    }

    free(temp);
    free(visited);

    return result;
}