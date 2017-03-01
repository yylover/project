#include <stdio.h>
#include <stdlib.h>

/*
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

 */

/**
 * 1. 内存分配函数:calloc
 *  int *a = calloc(2, sizeof(int));
 *  a[0], a[1]
 * 2.
 */


int* twoSum(int* nums, int numsSize, int target) {
    if (numsSize <= 1) {
        return NULL;
    }

    // int *a = calloc(2, sizeof(int));
    int *a = malloc(2 * sizeof(int));

    int i  = 0, j = 1;
    for (; i < numsSize-1; i++) {
        for (j = i+1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                a[0] = i;
                a[1] = j;
            }
        }
    }
    return a;
}


int main() {
    // int t[] = {2, 7, 11, 15};
    int t[] = {3, 2, 4};

    int *res = twoSum(t, 3, 6);
    for (size_t i = 0; i < 2; i++) {
        printf("%d\n", res[i]);
    }


    return 0;
}
