/*
Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.
*/

// reference: http://bangbingsyb.blogspot.com/2014/11/leetcode-integer-to-roman.html
/*
I: 1
V: 5
X: 10
L: 50
C: 100
D: 500
M: 1000
*/

class Solution {
public:
    string intToRoman(int num) {
        string res;
        string dict[13] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        int val[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        
        for (int i = 0; i < 13; i++) {
            if (num < val[i]) continue;
            int count = num / val[i];
            num %= val[i];
            for (int j = 0; j < count; j++) {
                res.append(dict[i]);
            }
        }
        
        return res;
    }
};
