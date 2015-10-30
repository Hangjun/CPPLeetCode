/* Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"]. 
*/

The first idea is to use DFS to collect all the local and global paths:

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

However, this is reported Time Limit Exceeded by LeetCode OJ. 
