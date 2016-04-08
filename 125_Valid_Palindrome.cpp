/*
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome. 
*/

/* 
Time: O(n)
Space: O(1)
*/

class Solution {
public:
    bool isPalindrome(string s) {
        if (s.empty()) return true;
        int left = 0, right = s.size() - 1;
        while (left < right) {
            // shrink left and right towards each other to skip non-digit or non-alpha characters
            while (left < right && !isalpha(s[left]) && !isdigit(s[left])) left++;
            while (left < right && !isalpha(s[right]) && !isdigit(s[right])) right--;
            if (tolower(s[left]) != tolower(s[right])) return false;
            left++;
            right--;
        }
        return true;
    }
};
