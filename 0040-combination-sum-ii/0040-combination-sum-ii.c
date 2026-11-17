/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 #include<stdlib.h>
 int res[1000][30];
int colSizes[1000];
int path[30];
int count;

int cmp(const void*a, const void*b) {
return (*(int*)a - *(int*)b);
}

void solve(int *candidates, int n, int target,
int start, int depth) {

if (target == 0) {

    for (int i = 0; i < depth; i++) {
        res[count][i] = path[i];
    }

    colSizes[count] = depth;
    count++;
    return;
}

for (int i = start; i < n; i++) {

    // Skip duplicate elements at the same level
    if (i > start && candidates[i] == candidates[i - 1])
        continue;

    if (candidates[i] > target)
        break;

    path[depth] = candidates[i];

    // i + 1 because each element can be used only once
    solve(candidates, n, target - candidates[i],
          i + 1, depth + 1);
}

}
int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    qsort(candidates, candidatesSize, sizeof(int), cmp);

count = 0;

solve(candidates, candidatesSize, target, 0, 0);

int **answer = malloc(count * sizeof(int*));

for (int i = 0; i < count; i++) {

    answer[i] = malloc(colSizes[i] * sizeof(int));

    for (int j = 0; j < colSizes[i]; j++) {
        answer[i][j] = res[i][j];
    }
}

*returnSize = count;
*returnColumnSizes = malloc(count * sizeof(int));

for (int i = 0; i < count; i++) {
    (*returnColumnSizes)[i] = colSizes[i];
}
return answer;
}