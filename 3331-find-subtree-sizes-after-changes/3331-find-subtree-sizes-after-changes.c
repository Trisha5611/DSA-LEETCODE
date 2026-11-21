/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* findSubtreeSizes(int* parent, int parentSize, char* s, int* returnSize) {
    int n = parentSize;
    *returnSize = n;

    int *head = malloc(n * sizeof(int));
    int *next = malloc(n * sizeof(int));
    int *newParent = malloc(n * sizeof(int));
    int *ans = malloc(n * sizeof(int));
    int *oldLast = malloc(n * sizeof(int));
    int *order = malloc(n * sizeof(int));
    int *stack = malloc(2 * n * sizeof(int));

    for (int i = 0; i < n; i++) {
        head[i] = -1;
        newParent[i] = parent[i];
        ans[i] = 1;
    }

    // Build original tree
    for (int i = 1; i < n; i++) {
        next[i] = head[parent[i]];
        head[parent[i]] = i;
    }

    int last[26];
    for (int i = 0; i < 26; i++)
        last[i] = -1;

    int top = 0, count = 0;
    stack[top++] = 0;

    // Iterative DFS: positive = enter, negative = exit
    while (top > 0) {
        int state = stack[--top];

        if (state >= 0) {
            int node = state;
            int c = s[node] - 'a';

            oldLast[node] = last[c];

            if (last[c] != -1)
                newParent[node] = last[c];

            last[c] = node;

            order[count++] = node;

            stack[top++] = ~node;

            for (int i = head[node]; i != -1; i = next[i])
                stack[top++] = i;

        } else {
            int node = ~state;
            int c = s[node] - 'a';

            last[c] = oldLast[node];
        }
    }

    // Build modified tree
    for (int i = 0; i < n; i++)
        head[i] = -1;

    for (int i = 1; i < n; i++) {
        next[i] = head[newParent[i]];
        head[newParent[i]] = i;
    }

    // Calculate subtree sizes
    for (int i = n - 1; i >= 0; i--) {
        int node = order[i];

        if (node != 0)
            ans[newParent[node]] += ans[node];
    }

    free(head);
    free(next);
    free(newParent);
    free(oldLast);
    free(order);
    free(stack);

    return ans;
}