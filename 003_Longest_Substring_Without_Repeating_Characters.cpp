/*
Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() <= 1)  return s.size();
        vector<bool> appeared(256, false);
        int maxLen = 1;
        int back = 0, front = 0;
        while (front < s.size()) {
            if (!appeared[s[front]]) {
                appeared[s[front]] = true;
                front++;
            } else {
                appeared[s[back]] = false;
                back++;
            }
            maxLen = max(maxLen, front - back);
        }
        return maxLen;
    }
};
