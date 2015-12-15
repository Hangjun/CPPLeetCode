/*
Implement pow(x, n). 
*/

class Solution {
public:
    double myPow(double x, int n) {
        // corner cases
        if (x == 1) return x;
        if (n >= 0) return myPowRecur(x, n);
        if (n < 0) return 1/myPowRecur(x, -n);
    }
    
    double myPowRecur(double x, int n) {
        if (n == 0) return 1;
        double res = myPowRecur(x, n/2);
        if (n % 2 == 0) return res * res;
        return res * res * x;
    }
};
