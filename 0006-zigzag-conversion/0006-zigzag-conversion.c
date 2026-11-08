#include <string.h>
#include <stdlib.h>

char* convert(char* s, int numRows) {
      int n = strlen(s);

    if (numRows == 1 || numRows >= n)
        return s;

    char** rows = (char**)malloc(numRows * sizeof(char*));
    int* count = (int*)calloc(numRows, sizeof(int));

    for (int i = 0; i < numRows; i++) {
        rows[i] = (char*)malloc((n + 1) * sizeof(char));
    }

    int currRow = 0;
    int direction = 1;

    // Arrange characters in zigzag pattern
    for (int i = 0; i < n; i++) {
        rows[currRow][count[currRow]++] = s[i];

        if (currRow == 0)
            direction = 1;
        else if (currRow == numRows - 1)
            direction = -1;

        currRow += direction;
    }

    // Combine all rows
    char* result = (char*)malloc((n + 1) * sizeof(char));
    int index = 0;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < count[i]; j++) {
            result[index++] = rows[i][j];
        }
        free(rows[i]);
    }

    result[index] = '\0';

    free(rows);
    free(count);

    return result;
}