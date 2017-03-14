/*
Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:
The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
*/

/*
Analysis: We first xor all elements in the array. The resulting number is the xor of the two single numbers. To separate them, we find the first index of bit 1 in the previous result (the first bit that the two single numbers differ). Then we scan the array one more time and based on whether not this bit is 1, we separate the numbers into two groups and reduce the problem to two original 2n+1 single number problems.

Time: O(n), Space: O(1). 2 Passes. 2n+2 problem.
*/
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int res = 0;
        for (int n : nums) res ^= n;
        
        int res1 = 0, res2 = 0; // res1 xor res2 = res
        int index = firstOneBitIndex(res);
        for (int n : nums) {
            if (equalOneBit(n, index)) res1 ^= n;
            else res2 ^= n;
        }
        return vector<int>{res1, res2};
        
    }
    
    int firstOneBitIndex(int n) {
        int index = 0;
        while ((n & 1) == 0) {
            ++index;
            n >>= 1;
        }
        return index;
    }
    
    bool equalOneBit(int n, int index) {
        return (n >>= index) & 1;
    }
};
