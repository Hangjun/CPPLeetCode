# Dynamic Programming Problem
[toc]
## Introduction
Dynamic Programming is an algorithmic paradigm that solves a given complex problem by breaking it into subproblems and stores the results of subproblems to avoid computing the same results again. Following are the two main properties of a problem that suggest that the given problem can be solved using Dynamic programming.

### Overlapping Subproblems:
Like Divide and Conquer, Dynamic Programming combines solutions to sub-problems. Dynamic Programming is mainly used when solutions of same subproblems are needed again and again. In dynamic programming, computed solutions to subproblems are stored in a table so that these don’t have to recomputed. So Dynamic Programming is not useful when there are no common (overlapping) subproblems because there is no point storing the solutions if they are not needed again. For example, Binary Search doesn’t have common subproblems. If we take example of following recursive program for Fibonacci Numbers, there are many subproblems which are solved again and again.

### Optimal Substructure: A given problems has Optimal Substructure Property if optimal solution of the given problem can be obtained by using optimal solutions of its subproblems.

For example, the Shortest Path problem has following optimal substructure property:
If a node x lies in the shortest path from a source node u to destination node v then the shortest path from u to v is combination of shortest path from u to x and shortest path from x to v. The standard All Pair Shortest Path algorithms like Floyd–Warshall and Bellman–Ford are typical examples of Dynamic Programming.

The dimension of a DP problem usually depends on the number of free variables. 

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

[115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/115.%20Distinct%20Subsequences.cpp))
```
Given a string S and a string T, count the number of distinct subsequences of T in S.
A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
Here is an example:
S = "rabbbit", T = "rabbit"
Return 3.
```

```c++
/* Time: O(mn), Space: O(mn). 
 * Standard rolling array trick brings the space complexity down to O(min(m, n)).
 */
class Solution {
public:
    int numDistinct(string s, string t) {
        if (t.empty()) return 1;
        if (s.size() < t.size()) return 0;
        
        int m = s.size(), n = t.size();
        // dp[i][j] = number of subsequences of t[0:i-1] in s[0:j-1]
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (int i = 0; i <= m; i++) dp[i][0] = 1;
        for (int j = 1; j <= n; j++) dp[0][j] = 0;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = s[i-1] == t[j-1] ? (dp[i-1][j-1] + dp[i-1][j]) : dp[i-1][j];
            }
        }
        
        return dp[m][n];
    }
};
```

[97. Interleaving String](https://leetcode.com/problems/interleaving-string/#/description)
```
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
For example,
Given:
s1 = "aabcc",
s2 = "dbbca",
When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
```

```c++

Time: O(mn), Space: O(mn).
*/
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if (s3.size() != m + n) return false;
        // dp[i][j] = whether s3 is interleaving at (i+j-1)th element if s1 is at the ith, s2 is at the jth element, resp.
        vector<vector<bool>> dp (m+1, vector<bool>(n+1, false)); 
        
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
               if (i == 0 && j == 0) dp[i][j] = true;
               else if (i == 0) dp[i][j] = dp[i][j-1] && s2[j-1] == s3[i+j-1];
               else if (j == 0) dp[i][j] = dp[i-1][j] && s1[i-1] == s3[i+j-1];
               else dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) || (dp[i][j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
        
        return dp[m][n];
    }
};

```


### Cut/Break/Sliding Window Problems
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

[312. Burst Balloons](https://leetcode.com/problems/burst-balloons/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/312.%20Burst%20Balloons.cpp))
```
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.
Find the maximum coins you can collect by bursting the balloons wisely.
Note: 
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
Example:
Given [3, 1, 5, 8]
Return 167
nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
```

```c++
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        vector<vector<int>> dp(n+2, vector<int>(n+2, 0));  // dp[i][j] = max coins generated from interval [i, j] inclusive
        
        for (int len = 1; len <= n; len++) { // all possible sliding window length
            for (int left = 1; left <= n-len+1; left++) {
                int right = left+len-1;
                // index of last balloon to burst
                for (int k = left; k <= right; k++) {
                    dp[left][right] = max(dp[left][right], nums[left-1]*nums[k]*nums[right+1] + dp[left][k-1] + dp[k+1][right]);
                }
            }
        }
        
        return dp[1][n];
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

### Local/Global Problems
Usually for this type of DP problem, local stores the current state that ends at the current index, global stores the optimal state that's up to and including the current index.

[188. Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/#/description)
```
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most k transactions.
Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
```

```c++
// Local-Global DP with standard rolling array trick. Time: O(nk), Space: O(k).
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty()) return 0;
        if (k >= prices.size()) return maxProfit(prices); // can make transaction every day - reduces to part II of this series
        int n = prices.size();
        // local[i][j] = max profit with at most j transactions and the ith day a sell
        vector<vector<int>> local(2, vector<int>(k+1, 0));
        // global[i][j] = max profit with at most j transactions from 0th day to ith day
        vector<vector<int>> global(2, vector<int>(k+1, 0));
        
        for (int i = 1; i < n; i++) {
            int delta = prices[i] - prices[i-1];
            for (int j = 1; j <= k; j++) {
                local[i%2][j] = max(global[(i-1)%2][j-1] + max(delta, 0), local[(i-1)%2][j] + delta);
                global[i%2][j] = max(local[i%2][j], global[(i-1)%2][j]);
            }
        }
        
        return global[(n-1)%2][k];
    }
    
    int maxProfit(vector<int> &prices) {
        int res = 0;
        for (int i = 1; i < prices.size(); i++) {
            int delta = prices[i] - prices[i-1];
            if (delta > 0) res += delta;
        }
        
        return res;
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


Here is a general template for problems with DFS/BFS + DP memorization:


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

Let look at another example:
[97. Interleaving String](https://leetcode.com/problems/interleaving-string/#/description): Previously we have solved in with space O(mn). We can use the method of rolling arrays to reduce the space complexity to O(min(m,n)). 2 Rows.

```c++
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if (s3.size() != m + n) return false;
        // dp[i][j] = whether s3 is interleaving at (i+j-1)th element if s1 is at the ith, s2 is at the jth element, resp.
        vector<vector<bool>> dp (2, vector<bool>(n+1, false)); 
        
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
               if (i == 0 && j == 0) dp[i%2][j] = true;
               else if (i == 0) dp[i%2][j] = dp[i%2][j-1] && s2[j-1] == s3[i+j-1];
               else if (j == 0) dp[i%2][j] = dp[(i-1)%2][j] && s1[i-1] == s3[i+j-1];
               else dp[i%2][j] = (dp[(i-1)%2][j] && s1[i-1] == s3[i+j-1]) || (dp[i%2][j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
        
        return dp[m%2][n];
    }
};
```

We can further reduce the space complexity to only one row. 

```c++
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if (s3.size() != m + n) return false;
        // dp[i][j] = whether s3 is interleaving at (i+j-1)th element if s1 is at the ith, s2 is at the jth element, resp.
        vector<bool> dp(n+1, false);
        dp[0] = true;
        for (int j = 1; j <= n; j++) dp[j] = dp[j-1] && s2[j-1] == s3[j-1];
        
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
               if (j == 0) dp[j] = dp[j] && s1[i-1] == s3[i+j-1];
               else dp[j] = (dp[j] && s1[i-1] == s3[i+j-1]) || (dp[j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
        
        return dp[n];
    }
};
```

Here is a general template for this type DP problem with the above space optimizations:

```c++
// DP: Space Optimization Template. Time: O(mn), Space: O(min(m, n)). One Row.
int m = rows, n = cols;
vector<int> dp(n, initialValue);
for (int j = 0; j < n; j++) dp[j] = InitialValue; // initialize first row

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

[279. Perfect Squares](https://leetcode.com/problems/perfect-squares/#/description)
```
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.
For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.
```

```c++
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = i; // sum of i 1's
            for (int j = 1; j * j <= i; j++) {
                dp[i] = min(dp[i], 1 + dp[i - j * j]);
            }
        }
        return dp[n];
    }
};
```

A problem essentially the same we the above is given in the following. The key takeaway is that, whenever we want to find the **minimum** number of summands to construct a target sum, we use this non-continuous state transition function:

\begin{equation}
dp[i] = \min(dp[i], dp[i-j] + 1), \forall\, j <= i.
\end{equation}

[322. Coin Change](https://leetcode.com/problems/coin-change/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/322.%20Coin%20Change.cpp))
```
You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)
Example 2:
coins = [2], amount = 3
return -1.
Note:
You may assume that you have an infinite number of each kind of coin.
```

_Analysis_: This is obviously a DP problem. The subproblems are also easy to construct: if we can know the minimum number of coins need to sum up to a value less than the target amount, then we can compute the minimum number of coins need to sum up to target amount. This actually also defines the states as well as the state transition functions.
This problem is essentially the same as problem 279. Perfect Squares (https://leetcode.com/problems/perfect-squares/#/description). Whenever it comes to finding the minimum number of summands.
Time: $O(n*amount)$, Space: $O(amount)$. We cannot optimize the space complexity as the state transition function is not continuous.

```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (coins.empty() || amount < 0) return -1;
        int n = coins.size();
        vector<int> dp(amount+1, amount+1); // dp[i] = min # of coins needed to sum up to value i
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int j = 0; j < n; j++) {
                if (i >= coins[j]) dp[i] = min(dp[i], dp[i-coins[j]]+1);
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
```

