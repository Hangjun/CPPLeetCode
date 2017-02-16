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

/*
The above solutions in the worse case will scan the string twice. Instead of recording whether the character has appeared or not, we can record the last location of this character so that whenever we see this character again, we can immediately jump the back pointer forward to the last location of this duplicate character and plus 1. 

One catch is that, when updating the left pointer, we need to put a max: left = max(ht[s[right]], left). This is because we can have a situation like "a......b......b......a". With the max, the left pointer will go backwards when we reach a, and results in a wrong maxLen calculation. The inner duplicating pairs have already put constraints on how the maxLen can be, and thus having the max will not miss the correct maxLen.

Time: O(n), space: O(1), 1 pass.
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) return 0;
        int maxLen = 0;
        unordered_map<char, int> ht; // character->index in s
        int left = 0, right = 0;
        for (int left = 0, right = 0; right < s.size(); right++) {
            if (ht.find(s[right]) != ht.end()) {
                left = max(ht[s[right]], left);
            }
            maxLen = max(maxLen, right - left + 1);
            ht[s[right]] = right + 1;
        }
        
        return maxLen;
    }
};
