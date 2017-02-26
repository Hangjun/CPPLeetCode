/*
Numbers can be regarded as product of its factors. For example,

8 = 2 x 2 x 2;
  = 2 x 4.

Write a function that takes an integer n and return all possible combinations of its factors.

Note:

    Each combination's factors must be sorted ascending, for example: The factors of 2 and 6 is [2, 6], not [6, 2].
    You may assume that n is always positive.
    Factors should be greater than 1 and less than n.

Examples:
input: 1
output:

[]

input: 37
output:

[]

input: 12
output:

[
  [2, 6],
  [2, 2, 3],
  [3, 4]
]

input: 32
output:

[
  [2, 16],
  [2, 2, 8],
  [2, 2, 2, 4],
  [2, 2, 2, 2, 2],
  [2, 4, 4],
  [4, 8]
]

*/

// DFS recursive solution
class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> res;
        if (n <= 1) return res;
        vector<int> curSoln;
        getFactorsDFS(n, 2, curSoln, res);
        return res;
    }
    
    void getFactorsDFS(int n, int start, vector<int> &curSoln, vector<vector<int>> &res) {
        if (n <= 1) return;
        
        for (int i = start; i <= n/i; i++) {
            if (n % i) continue;
            curSoln.push_back(i);
            curSoln.push_back(n/i);
            res.push_back(curSoln);
            curSoln.pop_back();
            getFactorsDFS(n/i, i, curSoln, res);
            curSoln.pop_back();
        }
    }
};

// Iterative solution (Python)
class Solution(object):
    def getFactors(self, n):
        """
        :type n: int
        :rtype: List[List[int]]
        """
        todo, res = [(n, 2, [])], []
        while todo:
            n, i, curSoln = todo.pop()
            while i <= n/i:
                if (n % i == 0):
                    res += curSoln + [i, n/i],
                    todo += (n/i, i, curSoln+[i]),
                i += 1
        return res
