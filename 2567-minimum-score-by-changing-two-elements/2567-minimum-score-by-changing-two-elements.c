int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
int minimizeSum(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);

    int n = numsSize;

    int a = nums[n-1] - nums[2];
    int b = nums[n-2] - nums[1];
    int c = nums[n-3] - nums[0];

    int ans = a;

    if (b < ans)
        ans = b;

    if (c < ans)
        ans = c;

    return ans;
}