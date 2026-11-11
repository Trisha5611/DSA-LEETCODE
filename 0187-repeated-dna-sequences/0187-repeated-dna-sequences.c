/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 
#include <stdlib.h>
#include <string.h>

char** findRepeatedDnaSequences(char* s, int* returnSize) {
    int n = strlen(s);
    *returnSize = 0;

    if (n < 10)
        return NULL;

    // Each nucleotide uses 2 bits.
    // 10 characters = 20 bits.
    int size = 1 << 20;

    // 0 = never seen, 1 = seen once, 2 = repeated
    unsigned char* seen = calloc(size, sizeof(unsigned char));

    char** result = malloc((n - 9) * sizeof(char*));

    int hash = 0;
    int mask = (1 << 20) - 1;

    for (int i = 0; i < n; i++) {

        int val;

        switch (s[i]) {
            case 'A': val = 0; break;
            case 'C': val = 1; break;
            case 'G': val = 2; break;
            case 'T': val = 3; break;
        }

        // Shift left by 2 bits and add new character
        hash = ((hash << 2) | val) & mask;

        if (i >= 9) {

            if (seen[hash] == 0) {
                seen[hash] = 1;
            }

            else if (seen[hash] == 1) {

                seen[hash] = 2;

                result[*returnSize] = malloc(11);
                strncpy(result[*returnSize], s + i - 9, 10);
                result[*returnSize][10] = '\0';

                (*returnSize)++;
            }
        }
    }

    free(seen);

    return result;
}
