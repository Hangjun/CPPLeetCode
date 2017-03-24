/*
Given a list of words (without duplicates), please write a program that returns all concatenated words in the given list of words.

A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.

Example:
Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]

Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
 "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
Note:
The number of elements of the given array will not exceed 10,000
The length sum of elements in the given array will not exceed 600,000.
All the input string will only include lower case letters.
The returned elements order does not matter.
*/

/*
Analysis: The first idea is to sort the words in ascending order of their lengths. We then traverse the words. If the a word is not breakable, then it is a "build block" word. We add it to a dictionary. Otherwise the word is part of our result.

This solution is TLE:
*/
class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> res;
        if (words.empty()) return res;
        auto myCompare = [&](const string& str1, const string& str2) { return str1.size() < str2.size(); };
        sort(words.begin(), words.end(), myCompare);
        unordered_set<string> dict;
        
        for (string s : words) {
            if (wordBreak(s, dict)) res.push_back(s);
            else dict.insert(s);
        }
        
        return res;
    }
    
    bool wordBreak(string s, unordered_set<string>& dict) {
        if (dict.empty()) return false;
        int n = s.size();
        vector<bool> dp(n+1, false); // dp[i] = s[0:i-1] is breakable or not
        dp[0] = true; // empty strings are breakable
        
        for (int i = 0; i < n; i++) {
            for (int j = i; j >= 0; j--) {
                if (dp[j] && dict.count(s.substr(j, i-j+1))) dp[i+1] = true;
            }
        }
        
        return dp[n];
    }
};

