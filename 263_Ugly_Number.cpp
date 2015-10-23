 Write a program to check whether a given number is an ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.

Note that 1 is typically treated as an ugly number. 


class Solution {
public:
    bool isUgly(int num) {
        // corner cases
        if (num <= 0)  return false;
        num = maxDivisible(num, 2);
        num = maxDivisible(num, 3);
        num = maxDivisible(num, 5);
        return num == 1;
    }
    
    int maxDivisible(int &num, int a) {
        while (num % a == 0) {
            num /= a;
        }
        return num;
    }
};
