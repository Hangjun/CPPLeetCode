/*
Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array that is constructed by these N numbers successfully if one of the following is true for the ith position (1 ≤ i ≤ N) in this array:

The number at the ith position is divisible by i.
i is divisible by the number at the ith position.
Now given N, how many beautiful arrangements can you construct?

Example 1:
Input: 2
Output: 2
Explanation: 

The first beautiful arrangement is [1, 2]:

Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).

Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).

The second beautiful arrangement is [2, 1]:

Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).

Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.
Note:
N is a positive integer and will not exceed 15.
*/

/*
The first idea is to use backtracking and try every number from 1 to n at every position pos from 1 to n. This approach is very similar to Problem 46 (https://leetcode.com/problems/permutations/?tab=Description).
*/
class Solution {
public:
    int countArrangement(int n) {
        if (n < 1) return 0;
        int count = 0;
        vector<bool> canUse(n, true);
        dfs(n, 1, canUse, count);
        return count;
    }
    
    void dfs(int n, int pos, vector<bool> &canUse, int &count) {
        if (pos > n) {
            ++count;
            return;
        }
        
        for (int i = 1; i <= n; i++) {
            if (i % pos && pos % i) continue;
            if (!canUse[i]) continue;
            canUse[i] = false;
            dfs(n, pos+1, canUse, count);
            canUse[i] = true;
        }
    }
};
