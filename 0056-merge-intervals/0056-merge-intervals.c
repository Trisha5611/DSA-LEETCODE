/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int compare(const void *a, const void *b) {
    int *x = *(int **)a;
    int *y = *(int **)b;

    return x[0] - y[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes) {

    qsort(intervals, intervalsSize, sizeof(int *), compare);

    int **result = malloc(intervalsSize * sizeof(int *));
    *returnColumnSizes = malloc(intervalsSize * sizeof(int));

    int count = 0;

    for (int i = 0; i < intervalsSize; i++) {

        if (count == 0 || intervals[i][0] > result[count - 1][1]) {

            result[count] = malloc(2 * sizeof(int));

            result[count][0] = intervals[i][0];
            result[count][1] = intervals[i][1];

            (*returnColumnSizes)[count] = 2;
            count++;

        } else {

            if (intervals[i][1] > result[count - 1][1]) {
                result[count - 1][1] = intervals[i][1];
            }
        }
    }

    *returnSize = count;

    return result;
}