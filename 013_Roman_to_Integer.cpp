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

/*
Remark: Here is another way of handling the subtractive notation: instead of viewing IX as 10 - 1, we can view it additively as 
1 + (10 - 2 *1). Therefore we can simply push all the roman numeral bases into a hash table with keys their corresponding 
values. We then scan the input string, and if we find such an increasing consecutively characters, we do the subtraction:
*/

// Time: O(n), Space: O(1).
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
