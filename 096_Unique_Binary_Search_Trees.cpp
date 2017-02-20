/*
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/

/* Analysis
This is really a math problem. The key is to note that, suppose node $i$ is chosen as a root, its left subtree can only consist of nodes $1,\cdots, i-1$, and its right subtree can only have nodes $i+1, \cdots, n$. This is guaranteed by the binary search tree structure. Therefore, if $i$ is the root, the problem reduced to how distinct binary search tree are there that take values in $1, \cdots, i-1$, and $i+1, \cdots, n$ respectively. This suggests a dynamic programming approach. If we define $dp[n]$ to be the number of distinct binary search tress with node values from $1$ to $n$, then we have the invariant:
\[dp[i] = dp[i-1]*dp[n-i].\]
Since there are $n$ possible roots, the total number $dp[n]$ is given by
\[dp[n] = \sum_{i = 0}^{n-1}\sum_{j = 0}^{i-1}dp[j]*dp[i-j-1].\]
*/

class Solution {
public:
    int numTrees(int n) {
        vector<int> numBST(n+1, 0); // number of distinct BSTs with n nodes
        numBST[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                numBST[i] += numBST[j] * numBST[i-1-j];
            }
        }
        return numBST[n];
    }
};
