#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int maxSelectedElements(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), compare);

    int dp[1000003] = {0};
    int ans = 0;

    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];

        dp[x + 1] = (dp[x + 1] > dp[x] + 1)
                    ? dp[x + 1] : dp[x] + 1;

        dp[x] = (dp[x] > dp[x - 1] + 1)
                ? dp[x] : dp[x - 1] + 1;

        if (dp[x] > ans)
            ans = dp[x];

        if (dp[x + 1] > ans)
            ans = dp[x + 1];
    }

    return ans;
}