/**
 *
 There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
 */




/**
 * 各种各样的边界条件。
 * i 有没有到边界
 * j 有没有到边界
 * i+1 有没有到边界
 * j+1 有没有到边界
 */

 double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
     if (nums1 == NULL && nums2 == NULL) {
         return 0.0;
     }

     int mediaNum = (nums1Size + nums2Size + 1) / 2;
     int i = 0, j = 0, index = 1;
     while (index < mediaNum) {
         if (i == nums1Size) {
             j++;
         } else if (j == nums2Size) {
             i++;
         } else if (nums1[i] < nums2[j]) {
             i ++;
         } else {
             j++;
         }
         index ++;
     }

     if ((nums1Size + nums2Size) % 2 == 1) {
         if (i == nums1Size) {
             return nums2[j];
         } else if (j == nums2Size) {
             return nums1[i];
         } else if (nums1[i] < nums2[j]) {
             return nums1[i];
         } else {
             return nums2[j];
         }
     } else {
         if (i == nums1Size) {
             return (nums2[j] + nums2[j+1]) / (float)2;
         } else if (j == nums2Size) {
             return (nums1[i] + nums1[i+1]) / (float)2;
         } else if (nums1[i] < nums2[j] && i+1 != nums1Size) {
             int b = (nums1[i+1] <= nums2[j]) ? nums1[i+1] : nums2[j];
             return (nums1[i] + b) / (float)2;
         } else if (nums1[i] > nums2[j] && j+1 != nums2Size) {
             int b = (nums2[j+1] <= nums1[i]) ? nums2[j+1] : nums1[i];
             return (nums2[j] + b) / (float)2;
         } else {
             return (nums2[j] + nums1[i]) / (float)2;
         }
     }
 }
