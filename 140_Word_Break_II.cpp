/* Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"]. 
*/

// The first idea is to use DFS to collect all the local and global paths:

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<string> soln;
        if (wordDict.empty() || s.empty()) return soln;
        vector<string> curSoln;
        wordBreakDFS(s, 0, wordDict, curSoln, soln);
        return soln;
    }
    
    void wordBreakDFS(string s, int start, unordered_set<string> &wordDict, vector<string> &curSoln, vector<string> &soln) {
        // terminate condition
        if (start == s.size() && !curSoln.empty()) {
            // push curSoln into soln
            string tmp = curSoln[0];
            for (int i = 1; i < curSoln.size(); i++) {
                tmp = tmp + " " + curSoln[i];
            }
            soln.push_back(tmp);
        }
        
        string curBreak;
        for (int i = start; i < s.size(); i++) {
            curBreak.push_back(s[i]);
            if (wordDict.count(curBreak)) {
                curSoln.push_back(curBreak);
                // recurse on curBreak
                wordBreakDFS(s, i+1, wordDict, curSoln, soln);
                curSoln.pop_back();
            }
        }
    }
};

/*
However, this solution exceeds time limit. We then use memorization to record, for each substring, all of its breakable subtring solutions.
*/
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        return wordBreakDFS(s, dict);
    }
    
    vector<string> wordBreakDFS(string s,  unordered_set<string> &dict) {
        if (ht.find(s) != ht.end()) return ht[s];
        vector<string> res;
        if (dict.count(s)) res.push_back(s);
        
        for (int i = 1; i < s.size(); i++) {
            string curBreak = s.substr(0, i);
            if (!dict.count(curBreak)) continue;
            string remaining = s.substr(i);
            vector<string> prevBreak = combine(curBreak, wordBreakDFS(remaining, dict));
            res.insert(res.end(), prevBreak.begin(), prevBreak.end());
        }
        
        ht[s] = res;
        return res;
    }

private:
    unordered_map<string, vector<string>> ht; // current string -> breakable substrings
    
    vector<string> combine(string word, vector<string> strs) {
        for (int i = 0; i < strs.size(); i++) strs[i] = word + " " + strs[i];
        return strs;
    }
};

/*
Notice the simiarity between this problem and Problem 254. Factor Combinations (https://leetcode.com/problems/factor-combinations/#/description).
*/
