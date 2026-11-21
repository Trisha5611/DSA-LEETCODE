/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

char ***result;
int count;
int n;

int col[10], diag1[20], diag2[20];
char board[10][11];

void backtrack(int row) {
    if (row == n) {
        result[count] = (char **)malloc(n * sizeof(char *));

        for (int i = 0; i < n; i++) {
            result[count][i] = (char *)malloc((n + 1) * sizeof(char));
            strcpy(result[count][i], board[i]);
        }

        count++;
        return;
    }

    for (int c = 0; c < n; c++) {
        int d1 = row - c + n - 1;
        int d2 = row + c;

        if (col[c] || diag1[d1] || diag2[d2])
            continue;

        board[row][c] = 'Q';
        col[c] = 1;
        diag1[d1] = 1;
        diag2[d2] = 1;

        backtrack(row + 1);

        board[row][c] = '.';
        col[c] = 0;
        diag1[d1] = 0;
        diag2[d2] = 0;
    }
}

char*** solveNQueens(int N, int* returnSize, int** returnColumnSizes) {
    n = N;
    count = 0;

    result = (char ***)malloc(1000 * sizeof(char **));

    memset(col, 0, sizeof(col));
    memset(diag1, 0, sizeof(diag1));
    memset(diag2, 0, sizeof(diag2));

    for (int i = 0; i < n; i++) {
        memset(board[i], '.', n);
        board[i][n] = '\0';
    }

    backtrack(0);

    *returnSize = count;

    *returnColumnSizes = (int *)malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        (*returnColumnSizes)[i] = n;
    }

    return result;
}