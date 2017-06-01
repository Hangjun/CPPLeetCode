/*
Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
*/

/*
Analysis: A straightfoward solution is to look at every p.size() length substring of s.
Time: O(nk), n = s.size(), k = p.size(). Space: O(k).
*/
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int n = s.size(), k = p.size();
        if (n < k) return res;
        
        vector<int> base(256, 0);
        for (char c : p) ++base[c - 'a'];
        
        for (int i = 0; i <= n-k; i++) {
            string str = s.substr(i, k);
            vector<int> curHist(base);
            int j = 0;
            for (; j < str.size(); j++) {
                if (--curHist[str[j] - 'a'] < 0) break;
            }
            if (j == str.size()) res.push_back(i);
        }
        
        return res;
    }
};
