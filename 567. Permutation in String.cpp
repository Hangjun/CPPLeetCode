/*
Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.

Example 1:
Input:s1 = "ab" s2 = "eidbaooo"
Output:True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:
Input:s1= "ab" s2 = "eidboaoo"
Output: False
Note:
The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].
*/

/*
Analysis: This is essentially the same problem as Problem 438. Find All Anagrams in a String.

Time: O(n), Space: O(k). Two pointer sliding window.
*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int k = s1.size(), n = s2.size();
        if (k > n) return false;
        
        vector<int> base(256, 0);
        vector<int> match(256, 0);
        for (int i = 0; i < k; i++) {
            ++base[s1[i] - 'a'];
            ++match[s2[i] - 'a'];
        }
        if (base == match) return true;
        
        // now we have [0, k-1], we maintain a sliding window of size k: [i-k+1, i]
        for (int i = k; i < n; i++) {
            ++match[s2[i] - 'a'];
            --match[s2[i-k] - 'a'];
            if (base == match) return true;
        }
        
        return false;
    }
};
