# Dynamic Programming Problem
[toc]
## Bottom-Up
### String Matching Problems
[72. Edit Distance](https://leetcode.com/problems/edit-distance/#/description)
```
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)
You have the following 3 operations permitted on a word:
a) Insert a character
b) Delete a character
c) Replace a character
```

```c++
// Time: O(mn), Space: O(mn).
class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word1.empty()) return word2.size();
        if (word2.empty()) return word1.size();
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0)); // dp[i][j] = dist(word1[0:i-1], word2[0:j-1])
        // dp[i][0]: match word1 with empty string
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        
        // dp[0][j]: match word2 with empty string
        for (int j = 0; j <= n; j++) dp[0][j] = j;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = 1 + min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]);
                }
            }
        }
        
        return dp[m][n];
    }
};
```


### Cut/Break Problems
For problems in which we need to make cuts of a range, and find the optimal cuts, it is often a 2D DP problem dp[k][i]: = optimal solution that cuts [0, ..., i] into k parts. The state transfer function is often computed by moving a j pointer from i to the left.

[139. Word Break](https://leetcode.com/problems/word-break/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/139_Word_Break.cpp))
```
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words.
For example, given
s = "leetcode",
dict = ["leet", "code"].
Return true because "leetcode" can be segmented as "leet code".
```

```c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (wordDict.empty()) return false;
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
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
```

[410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/#/description)
```
Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.
Note:
If n is the length of array, assume the following constraints are satisfied:
1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)
Examples:
Input:
nums = [7,2,5,10,8]
m = 2
Output:
18
Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
```

```c++
// Time: O(n^2 * m), Space: O(nm)
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<long> partialSum(n, 0);
        vector<vector<long>> dp(n, vector<long>(m+1, INT_MAX)); // dp[i][k] = max sum with k partitions on nums[0:i]
        // generic state transfer function: dp[i][k] = min(dp[i][k], max(partialSum[j:i], dp[j-1][k-1])), for all k-1 <= j <= i
        
        for (int i = 0; i < n; i++) partialSum[i] = i == 0 ? nums[0] : (nums[i] + partialSum[i-1]);
        
        for (int i = 0; i < n; i++) {
            int maxPartition = min(m, i+1); // [0:i] can have at most i+1 partitions
            for (int k = 1; k <= maxPartition; k++) {
                if (k == 1) {
                    dp[i][k] = partialSum[i];
                    continue;
                }
                for (int j = i; j >= k-1; j--) { // [0:j-1] with k-1 partitions and a single partition [j: i] 
                    long partial = partialSum[i]-partialSum[j]+nums[j];
                    if (partial > dp[i][k]) continue; // in case there is negative number: need to look all j
                    dp[i][k] = min(dp[i][k], max(partial, dp[j-1][k-1]));
                }
            }
        }
        
        return dp[n-1][m];
        
    }
};
```

### Knapsack Problems
[416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/#/description)
```
Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.
Note:
Each of the array element will not exceed 100.
The array size will not exceed 200.
-Example 1:
Input: [1, 5, 11, 5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
-Example 2:
Input: [1, 2, 3, 5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
```

```c++
// 0/1 Knapsack problem.
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) sum += num;
        if (sum % 2) return false;
        sum /= 2;
        int n = nums.size();
        // dp[i][j] = whether the nums[0:i-1] has a subset that sums to j
        vector<vector<bool>> dp(n+1, vector<bool>(sum+1, false));
        dp[0][0] = true; // empty set sums up to 0 sum
        for (int i = 1; i <= n; i++) dp[i][0] = true; // just don't select any number
        for (int j = 1; j <= sum; j++) dp[0][j] = false;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= sum; j++) {
                dp[i][j] = dp[i-1][j];
                if (j >= nums[i-1]) dp[i][j] = (dp[i][j] || dp[i-1][j-nums[i-1]]);
            }
        }
       
        return dp[n][sum];
    }
};
```

## Top-Down: Memorization (Combination of DFS/BFS)
We can also compute DP values from the top-down. This is called **memorization**. We recursively solve problems of smaller size and store all the intermediate computations.

A set of problems of this kind is used in combination of DFS/BFS. In these problems, DFS and BFS are used to find all or build up to a global solution. The use of DP is to memorize previously computed subproblems, hence the name **memorization**.

Following up Problem [139. Word Break](https://leetcode.com/problems/word-break/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/139_Word_Break.cpp)), if we want to return all possible combinations of breaking a given string, we use memorization as we DFS:
[140. Word Break II](https://leetcode.com/problems/word-break-ii/#/description)
```
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. You may assume the dictionary does not contain duplicate words.
Return all such possible sentences.
For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].
A solution is ["cats and dog", "cat sand dog"].
```

```c++
// DP: Memorization
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
```

A classic problem in this category is the so-called **Ski Problem**. A generic form of the ski problem is as follows:
[329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/329_Longest_Increasing_Path_in_a_Matrix.cpp))
```
Given an integer matrix, find the length of the longest increasing path.
From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).
-Example 1:
nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Return 4
The longest increasing path is [1, 2, 6, 9].
-Example 2:
nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
```

```c++
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int maxLen = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                maxLen = max(maxLen, dfs(matrix, i, j, m, n, dp));
            }
        }
        
        return maxLen;
    }
    
    int dfs(vector<vector<int>> &matrix, int x, int y, int m, int n, vector<vector<int>> &dp) {
        // if visited, just return - result already optimal
        if (dp[x][y]) return dp[x][y];
        
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {-1, 0, 1, 0};
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            if (matrix[nx][ny] <= matrix[x][y]) continue;
            dp[x][y] = max(dp[x][y], dfs(matrix, nx, ny, m, n, dp));
        }
        
        return ++dp[x][y];
    }
};
```
The ski problem has many variants.

## Space Complexity Optimization
Suppose we are looking at a 2d DP problem. If the state $dp[i][j]$ only depends on a subset of $dp[i-1][j]$, $dp[i][j-1]$ and $dp[i-1][j-1]$, we can optimize the space complexity in two successive procedures. 

As a first step we use a method call **Rolling Arrays** to get the space complexity down to a constant number of rows/columns (often two to three). Without loss of generality, we suppose the row size is smaller than the column size, thus in our solutions below we use the convention of rolling rows.

As a follow up step, we sometimes can use only one row/column by overwriting the previous values.

The rolling array trick applies to a wide range of DP problems for space complexity, and should be thought of every time a DP problem shows up.

### dp[i][j] only depends on dp[i-1][j] and dp[i][j-1]
In this case, we can **always** optimize the space complexity down to a single row/column.

[64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/#/description)
```
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
Note: You can only move either down or right at any point in time.
```

```c++
// Non-optimized DP. Time: O(mn), Space: O(mn).
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int> (n, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; i++) dp[i][0] = dp[i-1][0] + grid[i][0]; // first column
        for (int j = 1; j < n; j++) dp[0][j] = dp[0][j-1] + grid[0][j]; // first row
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        
        return dp[m-1][n-1];
    }
};
```

```c++
// Space optimized using Roll Arrays. Time: O(mn), Space: O(min(m, n)). Two Rows.
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(2, vector<int> (n, 0));
        dp[0][0] = grid[0][0];
        for (int j = 1; j < n; j++) dp[0][j] = dp[0][j-1] + grid[0][j]; // first row
        
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 0) dp[i%2][j] = dp[(i-1)%2][j] + grid[i][j];
                else dp[i%2][j] = min(dp[(i-1)%2][j], dp[i%2][j-1]) + grid[i][j];
            }
        }
        
        return dp[(m-1)%2][n-1];
    }
};
```

```c++
// DP: space optimized. Time: O(mn), Space: O(min(m, n)). One Row.
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n, grid[0][0]);
        for (int j = 1; j < n; j++) dp[j] = dp[j-1] + grid[0][j];
        
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 0) dp[j] += grid[i][j];
                else dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
            }
        }
        return dp[n-1];
    }
};
```

Here is a general template for this type DP problem with the above space optimizations:

```c++
// DP: Space Optimization Template. Time: O(mn), Space: O(min(m, n)). One Row.
int m = rows, n = cols;
vector<int> dp(n, initialValue);
for (int j = 0; j < n; j++) dp[0][j] = InitialValue; // initialize first row

for (int i = 1; i < m; i++) {
    for (int j = 0; j < n; j++) {
        if (j == 0) update dp[j];
        else dp[j] = f(dp[j], dp[j-1]); // f is the state transition function
    }
}

return dp[n-1];
```

### dp[i][j] depends on dp[i-1][j], dp[i][j-1] and dp[i-1][j-1]
If $dp[i-1][j-1]$ also depends on the previous diagonal value, optimizing the space complexity down to a single row is tricky, but the rolling array method still applies.

[221. Maximal Square](https://leetcode.com/problems/maximal-square/#/description)
```
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
For example, given the following matrix:
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.
```

```c++
// Non-optimized DP: Time: O(mn), Space: O(mn).
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0)); // dp[i][j] = max size of square ending at (i, j)
        int maxSize = 0;
        for (int i = 0; i < m; i++) {
            dp[i][0] = matrix[i][0] == '1';
            maxSize = max(maxSize, dp[i][0]);
        }
        for (int j = 0; j < n; j++) {
            dp[0][j] = matrix[0][j] == '1';
            maxSize = max(maxSize, dp[0][j]);
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == '0') continue;
                dp[i][j] = min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
                maxSize = max(maxSize, dp[i][j]);
            }
        }
        
        return maxSize * maxSize;
    }
};
```

```c++
// Rolling Arrays: Time: O(mn), Space: O(min(m, n)). Two Rows.
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(2, vector<int>(n, 0)); // dp[i][j] = max size of square ending at (i, j)
        int maxSize = 0;
        for (int j = 0; j < n; j++) {
            dp[0][j] = matrix[0][j] == '1';
            maxSize = max(maxSize, dp[0][j]);
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 0) {
                    dp[i%2][j] = matrix[i][j] == '1';
                } else if (matrix[i][j] == '1') {
                    dp[i%2][j] = min(min(dp[(i-1)%2][j], dp[i%2][j-1]), dp[(i-1)%2][j-1]) + 1;
                } else {
                    dp[i%2][j] = 0; // necessary to overwrite previously written value here
                }

                maxSize = max(maxSize, dp[i%2][j]);
            }
        }
        
        return maxSize * maxSize;
    }
};
```

Further optimizing it to a single row is tricky since there the previous diagonal value cannot be easily fetched (it is the previous value of dp[j-1]). We need extra bookkeeping:

```c++
// Time: O(mn), Space: O(min(m, n)). Single Row.
// tmp == dp[i-1][j], per == dp[i-1][j-1], dp[j-1] == dp[i][j-1]
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> dp(n+1, 0);
        int maxSize = 0;
        int pre = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 1; j <= n; j++) {
                int tmp = dp[j];
                if (matrix[i][j-1] == '1') {
                    dp[j] = min(dp[j], min(dp[j-1], pre)) + 1;
                    maxSize = max(maxSize, dp[j]);
                } else {
                    dp[j] = 0;
                }
                pre = tmp;
            }
        }
        
        return maxSize * maxSize;
    }
};
```



## Non-continous Transfer Functions
Often times the state transfer function is continuous in the sense that $dp[i] = f(dp[i-1])$, where $f$ is the transfer function. Below is a problem in which $f$ does not depend on the immediate previous value:
[338. Counting Bits](338. Counting Bits)
```
Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.
Example:
For num = 5 you should return [0,1,1,2,1,2].
```

```c++
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> dp(num+1, 0);
        for (int i = 1; i <= num; i++) {
            dp[i] = dp[i & (i-1)] + 1;
        }
        return dp;
    }
};
```


