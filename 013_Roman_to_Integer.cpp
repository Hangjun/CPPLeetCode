/*
Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.
*/

// reference: http://bangbingsyb.blogspot.com/2014/11/leetcode-roman-to-integer.html

class Solution {
public:
    int romanToInt(string s) {
        int res = 0;
        string dict[13] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        int val[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        int i = 0, index = 0;
        while (i < s.size() && index < 13) {
            string target = dict[index];
            string cur = s.substr(i, target.size());
            if (cur == target) {
                res += val[index];
                i += target.size();
            } else {
                index++;
            }
        }
        return res;
    }
};
