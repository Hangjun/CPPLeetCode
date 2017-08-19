/*
Given an integer array, find three numbers whose product is maximum and output the maximum product.

Example 1:
Input: [1,2,3]
Output: 6
Example 2:
Input: [1,2,3,4]
Output: 24
Note:
The length of the given array will be in range [3,104] and all elements are in the range [-1000, 1000].
Multiplication of any three numbers in the input won't exceed the range of 32-bit signed integer.
*/

/*
Solution:
Another solution could be to sort the given numsnums array(in ascending order) and find out the product of the last three numbers.

But, we can note that this product will be maximum only if all the numbers in numsnums array are positive. But, in the given problem statement, negative elements could exist as well.

Thus, it could also be possible that two negative numbers lying at the left extreme end could also contribute to lead to a larger product if the third number in the triplet being considered is the largest positive number in the numsnums array.

Thus, either the product nums[0]xnums[1]xnums[n-1] or nums[n-3]xnums[n-2]xnums[n−1] will give the required result. Thus, we need to find the larger one from out of these values.

// Time: O(nlogn), Space: O(logn) as sorting takes O(logn) space.
*/

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        const int n = nums.size();
        return max(nums[n-1] * nums[n-2] * nums[n-3], nums[0] * nums[1] * nums[n-1]);
    }
};
