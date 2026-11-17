/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 int **res;
int *colSizes;
int path[40];
int count;

void solve(int *candidates, int n, int target,
int start, int depth) {

if (target == 0) {

    res[count] = malloc(depth * sizeof(int));

    for (int i = 0; i < depth; i++) {
        res[count][i] = path[i];
    }

    colSizes[count] = depth;
    count++;
    return;
}

for (int i = start; i < n; i++) {

    if (candidates[i] > target)
        continue;

    path[depth] = candidates[i];

    // Pass i again because repetition is allowed
    solve(candidates, n, target - candidates[i],
          i, depth + 1);
}

}
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    res = malloc(150 * sizeof(int*));
colSizes = malloc(150 * sizeof(int));

count = 0;

solve(candidates, candidatesSize, target, 0, 0);

*returnSize = count;
*returnColumnSizes = colSizes;

return res;
}