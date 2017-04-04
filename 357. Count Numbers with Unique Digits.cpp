/*
Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10n.

Example:
Given n = 2, return 91. (The answer should be the total numbers in the range of 0 ≤ x < 100, excluding [11,22,33,44,55,66,77,88,99])

Hint:

A direct way is to use the backtracking approach.
Backtracking should contains three states which are (the current number, number of steps to get that number and a bitmask which represent which number is marked as visited so far in the current number). Start with state (0,0,0) and count all valid number till we reach number of steps equals to 10n.
This problem can also be solved using a dynamic programming approach and some knowledge of combinatorics.
Let f(k) = count of numbers with unique digits with length equals k.
f(1) = 10, ..., f(k) = 9 * 9 * 8 * ... (9 - k + 2) [The first factor is 9 because a number cannot start with 0].
*/

/*
Analysis: Simple math problem. Let f(k) be the count of numbers with unique digits with length equals k. Then:
f(0) = 1;
f(1) = 10;
f(2) = 9*9; since for the first digit there are 9 options excluding 0. After picking the first digit there are 9 options remaining for the second digit.
f(3) = 9*9*8; as we fix the first two digits, there are still 8 options left;
f(4) = 9*9*8*7;
...
f(10) = 9*9*8*7*6*5*4*3*2*1;

Time: O(1), Space: O(1).
*/
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n > 10) return 0;
        if (n == 0) return 1;
        int res = 0;
        vector<int> table = {1, 10, 9*9, 9*9*8, 9*9*8*7, 9*9*8*7*6, 9*9*8*7*6*5, 9*9*8*7*6*5*4, 9*9*8*7*6*5*4*3, 9*9*8*7*6*5*4*3*2, 9*9*8*7*6*5*4*3*2*1};
        while (n > 0) {
            res += table[n--];
        }
        return res;
    }
};
