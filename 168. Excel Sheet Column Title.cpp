/*
Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB
*/

/*
Analysis: This is the same thing as converting a number into base-26.
*/
class Solution {
public:
    string convertToTitle(int n) {
        string res;
        while (n > 0) {
            --n;
            res.push_back('A' + n % 26);
            n /= 26;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

// A really cool one-liner:
class Solution {
public:
    string convertToTitle(int n) {
        return n == 0 ? "" : convertToTitle(n / 26) + (char) (--n % 26 + 'A');
    }
};
