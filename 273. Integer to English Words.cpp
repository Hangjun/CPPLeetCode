/*
Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.

For example,
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
*/

class Solution {
public:
    string numberToWords(int num) {
        if (num < 1000) return convertBelow1000(num);
        
        string res = "";
        int d = -1;
        while (num > 0) {
            if (num % 1000 != 0) {
                string s = convertBelow1000(num % 1000);
                if (d >= 0) s += " " + scale[d];
                if (res == "") res = s;
                else res = s + " " + res;
            }
            num /= 1000;
            d++;
        }
        return res;
    }

private:
    vector<string> low = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

    vector<string> tens = {"Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

    vector<string> scale = {"Thousand", "Million", "Billion"};
    
    string convertBelow100(int n) {
        if (n < 20) return low[n];

        string s = tens[n/10 - 2];
        if (n == 10) return s;
        return n % 10 ? s + " " + low[n % 10] : s;
    }

    string convertBelow1000(int n) {
        string s1 = low[n / 100] + " Hundred";
        string s2 = convertBelow100(n % 100);
        
        if (n < 100) return s2;
        if (n == 100) return s1;
        return n % 100 ? s1 + " " + s2 : s1;
    }
};
