/*
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

Note:
0 ≤ x, y < 231.

Example:

Input: x = 1, y = 4

Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑

The above arrows point to positions where the corresponding bits are different.
*/

/*
Analysis: The sentence "corresponding bits are different" should immediately remind you about xor. The solution is simply the number of bit 1's in x ^ y.
*/
class Solution {
public:
    int hammingDistance(int x, int y) {
        int n = x ^ y;
        int res = 0;
        while (n) {
            ++res;
            n &= (n-1);
        }
        return res;
    }
};
