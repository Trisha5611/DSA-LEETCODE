/**
 * Note: The returned array must be malloced, assume caller calls free().
 */


#include <stdlib.h>

typedef struct {
    int weight, index;
} Available;

typedef struct {
    long long time;
    int weight, index;
} Busy;

// Available heap: smallest weight, then smallest index
int lessA(Available a, Available b) {
    if (a.weight != b.weight)
        return a.weight < b.weight;
    return a.index < b.index;
}

void pushA(Available h[], int *n, Available x) {
    int i = (*n)++;
    while (i > 0 && lessA(x, h[(i - 1) / 2])) {
        h[i] = h[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h[i] = x;
}

Available popA(Available h[], int *n) {
    Available ans = h[0], x = h[--(*n)];
    int i = 0, c;

    while ((c = 2 * i + 1) < *n) {
        if (c + 1 < *n && lessA(h[c + 1], h[c]))
            c++;

        if (!lessA(h[c], x)) break;

        h[i] = h[c];
        i = c;
    }
    if (*n > 0) h[i] = x;
    return ans;
}

// Busy heap: earliest finish time first
int lessB(Busy a, Busy b) {
    if (a.time != b.time) return a.time < b.time;
    if (a.weight != b.weight) return a.weight < b.weight;
    return a.index < b.index;
}

void pushB(Busy h[], int *n, Busy x) {
    int i = (*n)++;
    while (i > 0 && lessB(x, h[(i - 1) / 2])) {
        h[i] = h[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h[i] = x;
}

Busy popB(Busy h[], int *n) {
    Busy ans = h[0], x = h[--(*n)];
    int i = 0, c;

    while ((c = 2 * i + 1) < *n) {
        if (c + 1 < *n && lessB(h[c + 1], h[c]))
            c++;

        if (!lessB(h[c], x)) break;

        h[i] = h[c];
        i = c;
    }
    if (*n > 0) h[i] = x;
    return ans;
}

int* assignTasks(int* servers, int serversSize,
                 int* tasks, int tasksSize,
                 int* returnSize) {

    Available *available = malloc(serversSize * sizeof(Available));
    Busy *busy = malloc(serversSize * sizeof(Busy));

    int a = 0, b = 0;

    for (int i = 0; i < serversSize; i++) {
        Available x = {servers[i], i};
        pushA(available, &a, x);
    }

    int *result = malloc(tasksSize * sizeof(int));
    *returnSize = tasksSize;

    long long time = 0;

    for (int i = 0; i < tasksSize; i++) {

        if (time < i)
            time = i;

        // Move all completed servers to available
        while (b > 0 && busy[0].time <= time) {
            Busy x = popB(busy, &b);
            Available y = {x.weight, x.index};
            pushA(available, &a, y);
        }

        // If no server is free, wait
        if (a == 0) {
            time = busy[0].time;

            while (b > 0 && busy[0].time <= time) {
                Busy x = popB(busy, &b);
                Available y = {x.weight, x.index};
                pushA(available, &a, y);
            }
        }

        // Choose the best available server
        Available x = popA(available, &a);

        result[i] = x.index;

        // Mark server as busy
        Busy y = {time + tasks[i], x.weight, x.index};
        pushB(busy, &b, y);
    }

    free(available);
    free(busy);

    return result;
}

