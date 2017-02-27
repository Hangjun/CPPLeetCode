/*
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.



Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.
*/

/*
we can do this via backtracking DFS:
*/
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (digits.empty()) return res;
        vector<string> phoneDial = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        string curSoln;
        dfs(digits, 0, phoneDial, curSoln, res);
        return res;
    }
    
    void dfs(string digits, int start, vector<string> &phoneDial, string &curSoln, vector<string> &res) {
        if (start == digits.size()) {
            res.push_back(curSoln);
            return;
        }
        string letter = phoneDial[digits[start] - '0'];
        for(char c : letter) {
            curSoln.push_back(c);
            dfs(digits, start+1, phoneDial, curSoln, res);
            curSoln.pop_back();
        }
    }
};


/*
Since we know exactly how to construct the result, that is, we know exactly what the elements are, we can also solve this iteratively/constructively just like in Problem 78 (https://leetcode.com/problems/subsets/?tab=Description).
*/
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (digits.empty()) return res;
        res.push_back("");
        string phoneDial[10] = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        for (int i = 0; i < digits.size(); i++) {
            vector<string> tmp;
            for (char c : phoneDial[digits[i] - '0']) {
                for (string s : res) {
                    s.push_back(c);
                    tmp.push_back(s);
                }
            }
            res = tmp;
        }
        return res;
    }
};

/*
Remark: We see that for problem in which we do not the elements for the result (like finding the set of elements sum up to a target value) we can use DFS/Backtracking to find them. If we know exactly what they are, we can also solve it iteratively.
*/
