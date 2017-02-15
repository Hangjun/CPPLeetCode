/*
Given a positive integer num, write a function which returns True if num is a perfect square else False.

Note: Do not use any built-in library function such as sqrt.

Example 1:

Input: 16
Returns: True
Example 2:

Input: 14
Returns: False
*/

/* The first idea is that a number is a perfect square if and only if it can be expressed as 1+3+5+7+9+....
The time complexity of this algorithm is O(sqrt(n)).
*/
class Solution {
public:
    bool isPerfectSquare(int num) {
        int i = 1;
        while (num > 0) {
            num -= i;
            i += 2;
        }
        return num == 0;
    }
};

/*
Another solution is the reverse of the sqrt(x) problem and use binary search. Time = O(log n).
*/
class Solution {
public:
    bool isPerfectSquare(int num) {
        int left = 1, right = num;
        while (left <= right) {
            long mid = left + (right - left)/2;
            long long midSquare = mid * mid;
            if (midSquare == num) {
                return true;
            } else if (midSquare < num) {
                left = (int) mid + 1;
            } else {
                right = (int) mid - 1;
            }
        }
        return false;
    }
};

// We can of course use Newton's method, but that's not what this problem is really asking for.
