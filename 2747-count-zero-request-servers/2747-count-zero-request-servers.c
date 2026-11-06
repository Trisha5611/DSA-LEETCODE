/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 typedef struct {
    int server;
    int time;
} Log;

typedef struct {
    int time;
    int index;
} Query;

int cmpLog(const void *a, const void *b) {
    return ((Log*)a)->time - ((Log*)b)->time;
}

int cmpQuery(const void *a, const void *b) {
    return ((Query*)a)->time - ((Query*)b)->time;
}
int* countServers(int n, int** logs, int logsSize, int* logsColSize, int x, int* queries, int queriesSize, int* returnSize) {
     Log *L = malloc(logsSize * sizeof(Log));
    Query *Q = malloc(queriesSize * sizeof(Query));

    int *ans = calloc(queriesSize, sizeof(int));
    int *freq = calloc(n + 1, sizeof(int));

    *returnSize = queriesSize;

    for (int i = 0; i < logsSize; i++) {
        L[i].server = logs[i][0];
        L[i].time = logs[i][1];
    }

    for (int i = 0; i < queriesSize; i++) {
        Q[i].time = queries[i];
        Q[i].index = i;
    }

    qsort(L, logsSize, sizeof(Log), cmpLog);
    qsort(Q, queriesSize, sizeof(Query), cmpQuery);

    int left = 0, right = 0, active = 0;

    for (int i = 0; i < queriesSize; i++) {

        int start = Q[i].time - x;
        int end = Q[i].time;

        while (right < logsSize && L[right].time <= end) {
            int s = L[right].server;

            if (freq[s] == 0)
                active++;

            freq[s]++;
            right++;
        }

        while (left < right && L[left].time < start) {
            int s = L[left].server;

            freq[s]--;

            if (freq[s] == 0)
                active--;

            left++;
        }

        ans[Q[i].index] = n - active;
    }

    free(L);
    free(Q);
    free(freq);

    return ans;
    
}