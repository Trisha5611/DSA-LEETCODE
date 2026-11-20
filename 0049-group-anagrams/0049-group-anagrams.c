/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

char* sortString(char* s) {
    char *temp = malloc(strlen(s) + 1);
    strcpy(temp, s);

    int n = strlen(temp);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temp[i] > temp[j]) {
                char t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    return temp;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize,
                      int** returnColumnSizes) {

    char ***result = malloc(strsSize * sizeof(char**));
    char **keys = malloc(strsSize * sizeof(char*));

    *returnColumnSizes = malloc(strsSize * sizeof(int));

    *returnSize = 0;

    for (int i = 0; i < strsSize; i++) {

        char *key = sortString(strs[i]);

        int found = -1;

        for (int j = 0; j < *returnSize; j++) {
            if (strcmp(keys[j], key) == 0) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            found = (*returnSize)++;

            result[found] = malloc(strsSize * sizeof(char*));
            keys[found] = key;

            (*returnColumnSizes)[found] = 0;
        } else {
            free(key);
        }

        int count = (*returnColumnSizes)[found];

        result[found][count] = strs[i];

        (*returnColumnSizes)[found]++;
    }

    free(keys);

    return result;
}