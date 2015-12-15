/*
Find Minimum in Rotated Sorted Array II:

Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

The array may contain duplicates.
*/

/*
This problem can be solved in the same way as its predecessor Find Minimum in Rotated Sorted Array, except that now it is possible that 
\verb+nums[mid] == nums[end]+, in which case we do not know if the minimum is before \verb+mid+ or after \verb+mid+. How do we proceed? 
One simple idea is to decrement \verb+end+ by $1$ and ignore the last element. Even if the last element is indeed minimal, since we still 
hold \verb+mid+, the minimal is not lost. 
Thus we add a new test condition for this case:
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.empty()) return INT_MAX;
        int left = 0, right = nums.size()-1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[right]) {
                right = mid;
            } else if (nums[mid] > nums[right]){
                left = mid + 1;
            } else { // nums[mid] == nums[right]
                right--;
            }
        }
        return nums[left];
    }
};
