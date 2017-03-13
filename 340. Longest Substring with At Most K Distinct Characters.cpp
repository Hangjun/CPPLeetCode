/*
Total Accepted: 18886
Total Submissions: 49248
Difficulty: Hard
Contributors: Admin
Given a string, find the length of the longest substring T that contains at most k distinct characters.

For example, Given s = “eceba” and k = 2,

T is "ece" which its length is 3.
*/

/*
Analysis: Direct generalization of 159. Longest Substring with At Most Two Distinct Characters.

Time: O(n), Space: O(1).
*/
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (s.size() < k+1) return s.size();
        vector<int> dict(256, 0);
        int maxLen = 0;
        int left = 0;
        int count = 0;
        for (int right = 0; right < s.size(); right++) {
            dict[s[right]]++;
            if (dict[s[right]] == 1) { // new character
                count++;
                while (count > k) { // shrink window if needed
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
