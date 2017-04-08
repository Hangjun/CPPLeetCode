/*
Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.

For example:

Given s = "aabb", return ["abba", "baab"].

Given s = "abc", return [].

Hint:

If a palindromic permutation exists, we just need to generate the first half of the string.
To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.
*/

/*
Analysis: According to the hint, the key is to find the first half of the palindromic string, and then generate all possible permutations of the first half. The permutation part is easy. The slightly trikier part is getting thet first half in cases where some characters appear more than 2 times (but still even number of times). The C++ string constructor allows us to generate a given number of copies of a character. This solves the problem.
*/
class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<string> res;
        unordered_map<char, int> ht;
        for (char c : s) ht[c]++;
        
        int odd = 0; char mid; string firstHalf;
        for (auto p : ht) {
            if (p.second % 2) {
                mid = p.first;
                if (++odd > 1) return res;
            }
            firstHalf += string(p.second / 2, p.first);
        }
        
        // generate all permutations of the first half
        string localSoln = "";
        vector<bool> canUse(firstHalf.size(), true);
        permuteDFS(firstHalf, canUse, localSoln, res);
        
        for (string &str : res) {
            string t(str);
            reverse(t.begin(), t.end());
            if (odd) t = mid + t;
            str += t;
        }
        
        return res;
    }
    
    void permuteDFS(string &firstHalf, vector<bool> &canUse, string &localSoln, vector<string> &res) {
        if (localSoln.size() == firstHalf.size()) {
            res.push_back(localSoln);
            return;
        }
        
        for (int i = 0; i < firstHalf.size(); i++) {
            if ((i > 0 && firstHalf[i] == firstHalf[i-1]) && canUse[i-1] || !canUse[i]) continue;
            canUse[i] = false;
            localSoln.push_back(firstHalf[i]);
            permuteDFS(firstHalf, canUse, localSoln, res);
            localSoln.pop_back();
            canUse[i] = true;
        }
    }
};
