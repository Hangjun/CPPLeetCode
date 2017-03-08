/*
Write a function that takes a string as input and reverse only the vowels of a string.

Example 1:
Given s = "hello", return "holle".

Example 2:
Given s = "leetcode", return "leotcede".

Note:
The vowels does not include the letter "y".
*/

// Time: O(n), Space: O(1).
class Solution {
public:
    string reverseVowels(string s) {
        int i = 0, j = s.size();
        while (i < j) {
            if (!isVowel(s[i])) {
                i++;
            } else if (!isVowel(s[j])) {
                j--;
            } else {
                swap(s[i++], s[j--]);
            }
        }
        return s;
    }
    
    bool isVowel(char c) {
        char cLower = tolower(c);
        return cLower == 'a' || cLower == 'e' || cLower == 'i' || cLower == 'o' || cLower == 'u';
    }
};
