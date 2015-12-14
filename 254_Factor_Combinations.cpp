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

class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        return getFactorsHelper(n, 2);
    }
    
    vector<vector<int>> getFactorsHelper(int n, int start) {
        vector<vector<int>> res;
        // i <= n/i is better than i*i <= n: prevents overflow
        for (int i = start; i <= n/i; i++) {
            if (n % i == 0) {
                res.push_back({i, n/i});
                vector<vector<int>> nextLevel = getFactorsHelper(n/i, i);
                // append i in front of each solution in nextLevel
                for (int j = 0; j < nextLevel.size(); j++) {
                    nextLevel[j].insert(nextLevel[j].begin(), i);
                    res.push_back(nextLevel[j]);
                }
            }
        }
        return res;
    }
};
