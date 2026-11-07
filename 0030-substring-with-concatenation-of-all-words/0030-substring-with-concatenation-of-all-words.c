/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

unsigned long long hashWord(const char *s, int len) {
    unsigned long long h = 1469598103934665603ULL;

    for (int i = 0; i < len; i++) {
        h ^= (unsigned char)s[i];
        h *= 1099511628211ULL;
    }

    return h;
}

int findId(char *s, int pos, int len,
           char **words, int *table, int size,
           int capacity) {

    unsigned long long h = hashWord(s + pos, len);
    int slot = (int)(h & (capacity - 1));

    while (table[slot] != 0) {
        int id = table[slot] - 1;

        if (strncmp(words[id], s + pos, len) == 0)
            return id;

        slot = (slot + 1) & (capacity - 1);
    }

    return -1;
}

int* findSubstring(char* s, char** words, int wordsSize,
                   int* returnSize) {

    *returnSize = 0;

    int n = strlen(s);

    if (wordsSize == 0)
        return NULL;

    int len = strlen(words[0]);
    int total = len * wordsSize;

    int *ans = malloc((n + 1) * sizeof(int));

    if (total > n)
        return ans;

    int capacity = 1;
    while (capacity < wordsSize * 2)
        capacity *= 2;

    int *table = calloc(capacity, sizeof(int));
    int *need = calloc(wordsSize, sizeof(int));
    int *have = calloc(wordsSize, sizeof(int));

    // Build the word hash table
    for (int i = 0; i < wordsSize; i++) {
        unsigned long long h = hashWord(words[i], len);
        int slot = (int)(h & (capacity - 1));

        while (table[slot] != 0) {
            int id = table[slot] - 1;

            if (strcmp(words[id], words[i]) == 0)
                break;

            slot = (slot + 1) & (capacity - 1);
        }

        if (table[slot] == 0)
            table[slot] = i + 1;

        need[table[slot] - 1]++;
    }

    // Sliding window
    for (int offset = 0; offset < len; offset++) {

        memset(have, 0, wordsSize * sizeof(int));

        int left = offset;
        int count = 0;

        for (int right = offset; right + len <= n; right += len) {

            int id = findId(s, right, len, words,
                            table, wordsSize, capacity);

            if (id == -1) {
                memset(have, 0, wordsSize * sizeof(int));
                count = 0;
                left = right + len;
                continue;
            }

            have[id]++;
            count++;

            while (have[id] > need[id]) {
                int old = findId(s, left, len, words,
                                 table, wordsSize, capacity);

                have[old]--;
                count--;
                left += len;
            }

            if (count == wordsSize) {
                ans[(*returnSize)++] = left;

                int old = findId(s, left, len, words,
                                 table, wordsSize, capacity);

                have[old]--;
                count--;
                left += len;
            }
        }
    }

    free(table);
    free(need);
    free(have);

    return ans;
}
