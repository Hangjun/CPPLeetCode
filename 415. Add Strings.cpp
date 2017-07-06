/*
Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.

Note:

The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
*/

// Bit Int addion. Time: O(n), Space: O(1).
class Solution {
public:
    string addStrings(string num1, string num2) {
        string res = "";
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        int n = max(num1.size(), num2.size());
        int carry = 0;
        for (int i = 0; i < n; i++) {
            // compute current digit sum
            int tmp = 0;
            if (i < num1.size()) tmp += num1[i] - '0';
            if (i < num2.size()) tmp += num2[i] - '0';
            tmp += carry;
            
            res.push_back(tmp % 10 + '0');
            carry = tmp / 10;
        }
        if (carry) res.push_back('1');
        
        // no need to handle trailing zeros
        
        reverse(res.begin(), res.end());
        return res;
    }
};
