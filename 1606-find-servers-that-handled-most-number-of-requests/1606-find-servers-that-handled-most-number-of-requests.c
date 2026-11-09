/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 #define MAX 100005

int tree[4 * MAX];

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = val;
        return;
    }

    int mid = (start + end) / 2;

    if (idx <= mid)
        update(node * 2, start, mid, idx, val);
    else
        update(node * 2 + 1, mid + 1, end, idx, val);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int query(int node, int start, int end, int l, int r) {
    if (start > r || end < l || tree[node] == 0)
        return -1;

    if (start == end)
        return start;

    int mid = (start + end) / 2;

    int ans = query(node * 2, start, mid, l, r);

    if (ans != -1)
        return ans;

    return query(node * 2 + 1, mid + 1, end, l, r);
}
int* busiestServers(int k, int* arrival, int arrivalSize, int* load, int loadSize, int* returnSize) {
     int count[MAX] = {0};

    int *busyServer = malloc(MAX * sizeof(int));
    long long *finish = malloc(MAX * sizeof(long long));

    int heapSize = 0;

    for (int i = 0; i < 4 * k; i++)
        tree[i] = 0;

    for (int i = 0; i < k; i++)
        update(1, 0, k - 1, i, 1);

    for (int i = 0; i < arrivalSize; i++) {

        // Release servers that have finished their requests
        while (heapSize > 0 && finish[0] <= arrival[i]) {

            int server = busyServer[0];

            update(1, 0, k - 1, server, 1);

            long long lastFinish = finish[--heapSize];
            int lastServer = busyServer[heapSize];

            int pos = 0;

            while (1) {
                int child = pos * 2 + 1;

                if (child >= heapSize)
                    break;

                if (child + 1 < heapSize &&
                    finish[child + 1] < finish[child])
                    child++;

                if (lastFinish <= finish[child])
                    break;

                finish[pos] = finish[child];
                busyServer[pos] = busyServer[child];

                pos = child;
            }

            finish[pos] = lastFinish;
            busyServer[pos] = lastServer;
        }

        // Find the next available server
        int start = i % k;

        int server = query(1, 0, k - 1, start, k - 1);

        if (server == -1)
            server = query(1, 0, k - 1, 0, start - 1);

        // Drop request if no server is available
        if (server == -1)
            continue;

        count[server]++;

        update(1, 0, k - 1, server, 0);

        // Insert server into min heap
        long long endTime = (long long)arrival[i] + load[i];

        int pos = heapSize++;

        while (pos > 0) {
            int parent = (pos - 1) / 2;

            if (finish[parent] <= endTime)
                break;

            finish[pos] = finish[parent];
            busyServer[pos] = busyServer[parent];

            pos = parent;
        }

        finish[pos] = endTime;
        busyServer[pos] = server;
    }

    // Find maximum number of requests
    int maxCount = 0;

    for (int i = 0; i < k; i++) {
        if (count[i] > maxCount)
            maxCount = count[i];
    }

    // Store busiest servers
    int *result = malloc(k * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < k; i++) {
        if (count[i] == maxCount)
            result[(*returnSize)++] = i;
    }

    free(busyServer);
    free(finish);

    return result;
}