/*
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.
*/

/*
Analysis: If we are thinking forward, that is traversing the arrays left to right, then it seems that we must require two passes as well as additional space to hold the merged elements, otherwise it would've require a lot of swap operations, and it's just a mess. The problems hints us by saying that nums1 is large enough to hold both arrays. Whenever forward traversal does not work, we traverse backwards, and fill nums1 from the back, with larger elements being selected out of nums1 and nums2.

Time: O(n), Space: O(1).
*/
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, tar = m+n-1;
        while (j >= 0) nums1[tar--] = (i >= 0 && nums1[i] >= nums2[j]) ? nums1[i--] : nums2[j--];
    }
};
