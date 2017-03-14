/*
Given an array of integers, every element appears three times except for one, which appears exactly once. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/

/*
Analysis: Since we are dealing with integers here, each one is 32 bit. We can scan all the numbers, and for each bit, compute the sum of that bit % 3. If the result is nonzero, we know the single number has a 1 in that bit.

Time: O(32 * n), Space: O(1). Easily generalizable to kn + 1 problems, for any k.
*/
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < 32; i++) {
            int bitSum = 0;
            for (int n : nums) {
                if ((n >> i) & 1) bitSum = (bitSum+1) % 3;
            }
            if (bitSum) res |= bitSum << i;
        }
        return res;
    }
};
