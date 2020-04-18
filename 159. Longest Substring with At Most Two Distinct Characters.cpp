/*
Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

For example, Given s = “eceba”,

T is "ece" which its length is 3.
*/

/*
Analysis: Similar to Problem 3. Longest Substring Without Repeating Characters, we can use a sliding window with two pointers 
plus a hash table to solve this problem and its follow up Problem 340. Longest Substring with At Most K Distinct Characters.

The most important idea in solving this kind of questions is "how to update the "start" pointer" and the solution to these 
questions seem usually differ only in this respect.

Time: O(n), Space: O(1).
*/

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        if (s.size() < 3) return s.size();
        vector<int> dict(256, 0);
        int maxLen = 0;
        int left = 0;
        int count = 0;
        for (int right = 0; right < s.size(); right++) {
            dict[s[right]]++;
            if (dict[s[right]] == 1) { // new character
                count++;
                while (count > 2) { // shrink window if needed
                    dict[s[left]]--;
                    if (dict[s[left]] == 0) count--;
                    left++;
                }
            }
            maxLen = max(maxLen, right-left+1);
        }
        return maxLen;
    }
};
