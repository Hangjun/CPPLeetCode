/*
Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]
*/

/* Analysis:
The idea is, for each string in the dictonary, figure out different palindomic complements, and check if any exist in the dictionary as well. For each string, we loop through it, and divide it into two parts A+B. Notice that if A is palindomic, and reverse(B) exist in the dictionary, then reverse(B) + A + B is also palindromic. Any pair that consititues a palindrome can be decomposed this way as well. Thus we do not lose any admissible pair.

Suppose there are n strings, and the average length of each string is k. Then the running time of this algorithm is O(nk^2):
1. We loop through the dictionary, which takes n iterations;
2. For each string, we whether all possible prefix (and surfix) is palindomic, which takes O(k^2) time. 
*/
class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> res;
        unordered_map<string, int> ht; // word -> index
        for (int i = 0; i < words.size(); i++) ht[words[i]] = i;
        for (int i = 0; i < words.size(); i++) {
            string word = words[i];
            for (int l = 0; l <= word.size(); l++) {
                string firstHalf = word.substr(0, l);
                string secondHalf = word.substr(l);
                if (isPal(firstHalf)) {
                    string tmp = secondHalf;
                    reverse(tmp.begin(), tmp.end());
                    if (ht.find(tmp) != ht.end() && ht[tmp] != i) {
                        res.push_back(vector<int>{ht[tmp], i});
                    }
                }
                
                if (isPal(secondHalf)) {
                    string tmp = firstHalf;
                    reverse(tmp.begin(), tmp.end());
                    if (ht.find(tmp) != ht.end() && ht[tmp] != i && !secondHalf.empty()) {
                        res.push_back(vector<int>{i, ht[tmp]});
                    }
                }
            }
        }
        return res;
    }
private:
    bool isPal(string s) {
        int i = 0, j = s.size()-1;
        while (i <= j) {
            if (s[i++] != s[j--]) return false;
        }
        return true;
    }
};

/* Analysis:
Checking all possible prefixes palindomic or not takes too much time. This can definitely be optimized via better palindomic checking algorithms (e.g. Manacher's algorithm), and better data structures (e.g. prefix tree). We now use a prefix tree to speed up the above implementation.
*/
