/*
There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        int mid = (m+n)/2;
        if ((m+n) %2 == 1) 
            //Note the mid+1 even when m+n is odd! (mid+1)th elem = nums[mid]
            return findKthNumber(nums1.begin(), m, nums2.begin(), n, mid+1);
        else {
            int median1 = findKthNumber(nums1.begin(), m, nums2.begin(), n, mid);
            int median2 = findKthNumber(nums1.begin(), m, nums2.begin(), n, mid+1);
            return 0.5*((double)median1 + (double)median2);
        }
    }
    
    int findKthNumber(vector<int>::iterator n1, int m, vector<int>::iterator n2, int n, int k) {
        //basecase: either nume1 or nums2 are fully traversed
        if (m == 0) return *(n2+k-1);
        if (n == 0) return *(n1+k-1);
        //start binary search for k
        int i = m/2, j = n/2;
        if (*(n1+i) <= *(n2+j)) {
            if (k > i+j+1)
                return findKthNumber(n1+i+1, m-i-1, n2, n, k-i-1);
            else
                return findKthNumber(n1, m, n2, j, k);
        } else  {
            if (k > i+j+1)
                return findKthNumber(n1, m, n2+j+1, n-j-1, k-j-1);
            else
                return findKthNumber(n1, i, n2, n, k);
        }
    }
};
