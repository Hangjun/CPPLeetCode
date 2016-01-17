/*
Given an integer, write a function to determine if it is a power of three.
Follow up:
Could you do it without using any loop / recursion? 
*/

// Submission #1: While-loop solution. Accepted

class Solution {
public:
    bool isPowerOfThree(int n) {
        // corner case
        if (n <= 0) return false;
        if (n == 1) return true;
        
        // repeatedly divide n by 3
        while (n % 3 == 0) {
            n /= 3;
        }
        return n == 1;
    }
};

// Submission #2: O(1). Accepted.
// Idea: Compute the largest integer that is a power of 3. Then n is a power of 3 iff n divides it. 

class Solution {
public:
    bool isPowerOfThree(int n) {
        // corner case
        if (n <= 0) return false;
        if (n == 1) return true;
        
        // compute the largest integer that is a power of 3
        int maxPow3 = log10(INT_MAX) / log10(3);
        int maxPow3Val = pow(3, maxPow3);  

        // n is a power of 3 iff n divides maxPow3Val
        return maxPow3Val % n == 0;
    }
};

// We can also compute all the integers that are powers of 3, put them in an unordered_set, and test whether n belongs to that unordered_set.
