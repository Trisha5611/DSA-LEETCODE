int minimumSumSubarray(int* nums, int numsSize, int l, int r) {
    int min = 1000000;

    for (int i = 0; i < numsSize; i++) {
        int sum = 0;

        for (int j = i; j < numsSize; j++) {
            sum += nums[j];

            int len = j - i + 1;

            if (len >= l && len <= r && sum > 0) {
                if (sum < min) {
                    min = sum;
                }
            }

            if (len >= r) {
                break;
            }
        }
    }

    return min == 1000000 ? -1 : min;
}