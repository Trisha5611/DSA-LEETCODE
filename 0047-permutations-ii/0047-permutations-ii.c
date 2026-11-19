/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 #include <stdlib.h>

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void backtrack(int* nums, int n, int* temp, int* visited,
               int** result, int* returnSize) {

    if (*returnSize >= 40320)
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

        if (visited[i])
            continue;

        if (i > 0 && nums[i] == nums[i-1] && !visited[i-1])
            continue;

        visited[i] = 1;
        temp[count] = nums[i];

        backtrack(nums, n, temp, visited,
                  result, returnSize);

        visited[i] = 0;
    }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
     *returnSize = 0;

    qsort(nums, numsSize, sizeof(int), cmp);

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