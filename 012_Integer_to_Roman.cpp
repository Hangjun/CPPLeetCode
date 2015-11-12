/*
Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.
*/

// reference: http://bangbingsyb.blogspot.com/2014/11/leetcode-integer-to-roman.html

I: 1
V: 5
X: 10
L: 50
C: 100
D: 500
M: 1000

class Solution {
public:
    string intToRoman(int num) {
        string res;
        string dict[13] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        int val[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        for (int i = 0; i < 13; i++) {
            if (num >= val[i]) {
                int count = num / val[i];
                num %= val[i];
                for (int j = 0; j < count; j++) {
                    res.append(dict[i]);
                }
            }
        }
        return res;
    }
};


Here is another way of handling the subtractive notation: instead of viewing \verb+IX+ as $10 - 1$, we can view it additively as 
$1 + (10 - 2 *1)$. Therefore we can simply push all the roman numeral bases into a hash table with keys their corresponding 
values. We then scan the input string, and if we find such an \emph{increasing} consecutively characters, we do the subtraction:

class Solution {
public:
    int romanToInt(string s) {
        int res = 0;
        unordered_map<char, int> ht;
        romanHashInit(ht);
        for (int i = 0; i < s.size(); i++) {
            if (ht.find(s[i]) == ht.end()) return 0;
            res += ht[s[i]];
            if (i > 0 && ht[s[i]] > ht[s[i-1]]) {
                res -= 2 * ht[s[i-1]];
            }
        }
        return res;
    }
    
    void romanHashInit(unordered_map<char, int> &ht) {
        ht['I'] = 1;
        ht['V'] = 5;
        ht['X'] = 10;
        ht['L'] = 50;
        ht['C'] = 100;
        ht['D'] = 500;
        ht['M'] = 1000;
    }
};
