/*
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

Update (2015-02-10):
The signature of the C++ function had been updated. If you still see your function signature accepts a const char * argument, please click the reload button to reset your code definition.
*/

class Solution {
public:
    int myAtoi(string str) {
        // corner case
        if (str.empty() || str[0] == '\0') return 0;
        int i = 0;
        // skip blanks at the beginning
        while (isspace(str[i])) i++;
        
        int minus = 1;
        // fetch sign, if at all
        if (str[i] == '-') {
            minus = -1;
            i++;
        } else if (str[i] == '+') {
            minus = 1;
            i++;
        }
        
        long long res = 0;
        while (isdigit(str[i])) {
            res = res * 10 + (str[i] - '0');
            i++;
            if (res > INT_MAX) {
                return minus > 0 ? INT_MAX : INT_MIN;
            }
        }
        return minus > 0 ? res : -res;
    }
};
