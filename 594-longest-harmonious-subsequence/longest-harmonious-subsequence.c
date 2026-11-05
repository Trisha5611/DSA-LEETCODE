#include<stdlib.h>
int compare(const void *a, const void *b)
{
    return(*(int*)a>*(int*)b)-(*(int*)a<*(int*)b);
}
int findLHS(int* nums, int numsSize) {
    qsort(nums,numsSize,sizeof(int),compare);
    int left=0,max=0;
    for(int right=0; right<numsSize; right++)
    {
        while (nums[right]-nums[left]>1)
        {
            left++;
        }
         if (nums[right] - nums[left] == 1)
        {
            int len = right - left + 1;

            if (len > max)
                max = len;
        }

    }
    return max;

}