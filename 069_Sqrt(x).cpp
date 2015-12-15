/*
Implement int sqrt(int x).

Compute and return the square root of x.
*/

class Solution {
public:
    int mySqrt(int x) {
        if (x < 0) return -1;
        if (x == 0) return x;
        if (x == 1) return 1;
        long long left = 1;
        long long right = x/2;
        while (left < right) {
            long long mid = left + (right - left) / 2;
            long long midSqure = mid * mid;
            if (midSqure == x) {
                return mid;
            } else if (midSqure < x) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        // left == right
        if (left * left > x) return left-1;
        return left;
    }
};
