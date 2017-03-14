/*
Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example:
Given a = 1 and b = 2, return 3.
*/

class Solution {
public:
    int getSum(int a, int b) {
        int sum;
        while (b) {
            sum = a ^ b; // compute sum without thinking about the carry
            b = (a & b) << 1; // compute the carry
            a = sum;
        }
        return sum;
    }
};
