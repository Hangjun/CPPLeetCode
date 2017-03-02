/*
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].
*/

/*
Analysis: The idea is to hash the substrings of size 10 to a as more compact data structure as possible, and scan the input string linearly to find repeating ones. There are many ways to hash, and the more compact the hash value gets the more complicated the hash function is. In theory, A, C, G, T can be represented 2 bits: 00, 01, 10 and 11, and a 10 character substring can be represented by a 20 bit array. We choose to hash the subtrings to longs for simplicity.
*/
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> res;
        if (s.size() < 10) return res;
        unordered_map<long, int> ht;
        for (int i = 0; i <= s.size()-10; i++) {
            string cur = s.substr(i, 10);
            if (ht[hashToLong(cur)]++ == 1) res.push_back(cur); // not >= 1 to avoid duplicating solutions
        }
        return res;
    }
    
    long hashToLong(string s) {
        long res = 0;
        for (char c : s) {
            res *= 10;
            if (c == 'A') res += 1;
            else if (c == 'C') res += 2;
            else if (c == 'G') res += 3;
            else res += 4;
        }
        return res;
    }
};
