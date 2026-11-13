void nextPermutation(int* nums, int numsSize) {
    int i, j, temp;

    
    i = numsSize - 2;

    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }

    
    if (i >= 0) {
        j = numsSize - 1;

        while (nums[j] <= nums[i]) {
            j--;
        }

        
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    
    int left = i + 1;
    int right = numsSize - 1;

    while (left < right) {
        temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;

        left++;
        right--;
    }
}