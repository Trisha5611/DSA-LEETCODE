
#include <stdlib.h>

#define LOG 18

long long getCost(
    int l, int r,
    int* nums,
    long long* prefix,
    int* up,
    long long* sum,
    int n
) {
    long long maxSum = 0;
    int p = l;

    for (int j = LOG - 1; j >= 0; j--) {
        int next = up[p * LOG + j];

        if (next <= r) {
            maxSum += sum[p * LOG + j];
            p = next;
        }
    }

    maxSum += (long long)nums[p] * (r - p + 1);

    return maxSum - (prefix[r + 1] - prefix[l]);
}

long long countNonDecreasingSubarrays(
    int* nums, int numsSize, long long k
) {
    int n = numsSize;

    int* next = malloc((n + 1) * sizeof(int));
    int* st = malloc((n + 1) * sizeof(int));

    long long* prefix = calloc(n + 1, sizeof(long long));

    int* up = calloc((n + 1) * LOG, sizeof(int));
    long long* sum = calloc((n + 1) * LOG, sizeof(long long));

    // 1. Build prefix sums
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }

    // 2. Find next strictly greater element
    int top = -1;

    for (int i = n - 1; i >= 0; i--) {

        while (top >= 0 && nums[st[top]] <= nums[i]) {
            top--;
        }

        next[i] = (top == -1) ? n : st[top];

        st[++top] = i;
    }

    next[n] = n;

    // 3. Initialize binary lifting
    for (int j = 0; j < LOG; j++) {
        up[n * LOG + j] = n;
    }

    for (int i = 0; i < n; i++) {
        up[i * LOG] = next[i];

        sum[i * LOG] =
            (long long)nums[i] * (next[i] - i);
    }

    // 4. Build binary lifting tables
    for (int j = 1; j < LOG; j++) {

        for (int i = 0; i < n; i++) {

            int mid = up[i * LOG + j - 1];

            up[i * LOG + j] =
                up[mid * LOG + j - 1];

            sum[i * LOG + j] =
                sum[i * LOG + j - 1] +
                sum[mid * LOG + j - 1];
        }
    }

    // 5. Sliding window
    int left = 0;
    long long answer = 0;

    for (int right = 0; right < n; right++) {

        while (left <= right &&
               getCost(left, right, nums, prefix,
                       up, sum, n) > k) {

            left++;
        }

        answer += right - left + 1;
    }

    free(next);
    free(st);
    free(prefix);
    free(up);
    free(sum);

    return answer;
}
