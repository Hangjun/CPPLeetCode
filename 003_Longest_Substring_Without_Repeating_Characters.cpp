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


/* Here is another implementation of the same idea:
Time: O(n)
Space: O(1)
*/

class Solution {
public:
    /**
     * @param s: a string
     * @return: an integer 
     */
    int lengthOfLongestSubstring(string s) {
        if (s.empty())  return 0;
        int maxLen = INT_MIN;
        int left = 0, right = 0;
        bitset<256> b;
        b.reset();
        while (right < s.size()) {
            while (right < s.size() && b[s[right]] == 0)  b.flip(s[right++]);
            maxLen = max(maxLen, right-left);
            if (right == s.size()) break;
            // shrink left to find the repeat
            while (left < right && s[left] != s[right])  b.flip(s[left++]);
        }
        return maxLen;
    }
};
