/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 void generate(char* path, int open, int close, int n,
              char** result, int* returnSize) {

    if (open == n && close == n) {
        path[2 * n] = '\0';

        result[*returnSize] = malloc(2 * n + 1);
        strcpy(result[*returnSize], path);

        (*returnSize)++;
        return;
    }

    if (open < n) {
        path[open + close] = '(';
        generate(path, open + 1, close, n, result, returnSize);
    }

    if (close < open) {
        path[open + close] = ')';
        generate(path, open, close + 1, n, result, returnSize);
    }
}
char** generateParenthesis(int n, int* returnSize) {
     char** result = malloc(15000 * sizeof(char*));
    char path[20];

    *returnSize = 0;

    generate(path, 0, 0, n, result, returnSize);

    return result;
}