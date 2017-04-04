/*
Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

Note:
n is positive and will fit within the range of a 32-bit signed integer (n < 231).

Example 1:

Input:
3

Output:
3
Example 2:

Input:
11

Output:
0

Explanation:
The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
*/

/*
Analysis: We divide this problem into three subproblems:
1. Find the number of digits of the number where the nth digit is from, i.e. get the "range".
2. Find the exact number where the nth digit is from.
3. Find the exact digit in that number.

Time: O(logn), Space: O(1).
*/
class Solution {
public:
    int findNthDigit(int n) {
        long base = 9, digits = 1;
        long start = 1;
        
        // find the length of the number
        while (n > base * digits) {
            n -= base * digits;
            base *= 10;
            digits++;
            start *= 10;
        }
        // find the number where the nth digit is from
        start += (n-1) / digits; // use n-1 since our number system is 0 based
        
        // find the ((n-1) % digits)th digit in that number
        return to_string(start)[(n-1)%digits] - '0';
    }
};
