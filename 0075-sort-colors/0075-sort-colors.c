void sortColors(int* nums, int numsSize) {
     int count0 = 0, count1 = 0, count2 = 0;
    int i;

    // Count the number of 0s, 1s and 2s
    for (i = 0; i < numsSize; i++) {
        if (nums[i] == 0)
            count0++;
        else if (nums[i] == 1)
            count1++;
        else
            count2++;
    }

    // Replace the array elements
    i = 0;

    while (count0--)
        nums[i++] = 0;

    while (count1--)
        nums[i++] = 1;

    while (count2--)
        nums[i++] = 2;

}