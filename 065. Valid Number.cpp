/*
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.
*/

// Time: O(n), Space: O(1)
class Solution {
public:
    bool isNumber(string s) {
        if (s.empty()) return false;
        int i = 0;
        while(isspace(s[i])) {
            i++;
        }
            
        if (s[i] == '+' || s[i] == '-') {
            i++;
        }
            
        bool eAppear = false;
        bool dotAppear = false;
        bool firstPart = false;
        bool secondPart = false;
        bool spaceAppear = false;

        while(s[i] != '\0') {
            if (s[i] == '.') {
                if (dotAppear || eAppear || spaceAppear) {
                    return false;
                } else {
                    dotAppear = true;
                }
            } else if (s[i] == 'e' || s[i] == 'E') {
                if (eAppear || !firstPart || spaceAppear) {
                    return false;
                } else {
                    eAppear = true;
                }
            } else if (isdigit(s[i])) {
                if (spaceAppear) {
                    return false;
                }
   
                if (!eAppear) {
                    firstPart = true;
                } else {
                    secondPart = true;
                }
            } else if (s[i] == '+' || s[i] == '-') {
                if (spaceAppear) {
                    return false;
                }

                if (!eAppear || !(s[i - 1] == 'e' || s[i - 1] == 'E')) {
                    return false;
                }
            } else if (isspace(s[i])) {
                spaceAppear = true;
            } else {
                return false;
            }
            i++;            
        }
        
        if (!firstPart) {
            return false;
        } else if (eAppear && !secondPart) {
            return false;
        } else {
            return true;
        }
    }
};
