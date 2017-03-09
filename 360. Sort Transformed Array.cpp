/*
Given a sorted array of integers nums and integer values a, b and c. Apply a function of the form f(x) = ax2 + bx + c to each element x in the array.

The returned array must be in sorted order.

Expected time complexity: O(n)

Example:
nums = [-4, -2, 2, 4], a = 1, b = 3, c = 5,

Result: [3, 9, 15, 33]

nums = [-4, -2, 2, 4], a = -1, b = 3, c = 5

Result: [-23, -5, 1, 7]
*/

/*
Analysis: Given the input array is sorted, and f(x) is a quadractic function, we can use two colliding pointers to "gradient descent" down to the middle of the array (which takes the minimum/maximum value depending on the sign of a). This is a very straightforward and yet fast solution.

Time: O(n), Space: O(1).
*/
class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        vector<int> res (nums.size());
        if (nums.empty()) return res;
        int left = 0, right = nums.size()-1;
        if (a >= 0) {
            int index = nums.size()-1;
            while (left <= right) {
                res[index--] = quad(nums[left], a, b, c) > quad(nums[right], a, b, c) ? quad(nums[left++], a, b, c) : quad(nums[right--], a, b, c);
                }
            } else {
            int index = 0;
            while (left <= right) {
                res[index++] = quad(nums[left], a, b, c) < quad(nums[right], a, b, c) ? quad(nums[left++], a, b, c) : quad(nums[right--], a, b, c);
            }
        }
        return res;
    }
    
    int quad (int x, int a, int b, int c) {
        return a * x * x + b * x + c;
    }
};
