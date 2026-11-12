/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h>
#include <string.h>

char *mapping[] = {
    "", "", "abc", "def", "ghi",
    "jkl", "mno", "pqrs", "tuv", "wxyz"
};

char **result;
int count;

void backtrack(char *digits, int index, char *current, int len) {

    if (index == len) {
        result[count] = (char *)malloc((len + 1) * sizeof(char));
        strcpy(result[count], current);
        count++;
        return;
    }

    int digit = digits[index] - '0';
    char *letters = mapping[digit];

    for (int i = 0; letters[i] != '\0'; i++) {
        current[index] = letters[i];

        backtrack(digits, index + 1, current, len);
    }
}

char** letterCombinations(char* digits, int* returnSize) {
     int len = strlen(digits);

    count = 0;
    *returnSize = 0;

    int total = 1;

    for (int i = 0; i < len; i++) {
        total *= strlen(mapping[digits[i] - '0']);
    }

    result = (char **)malloc(total * sizeof(char *));

    char *current = (char *)malloc((len + 1) * sizeof(char));
    current[len] = '\0';

    backtrack(digits, 0, current, len);

    free(current);

    *returnSize = count;

    return result;
}