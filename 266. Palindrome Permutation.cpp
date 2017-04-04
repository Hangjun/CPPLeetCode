/*
Given a string, determine if a permutation of the string could form a palindrome.

For example,
"code" -> False, "aab" -> True, "carerac" -> True.

Hint:

Consider the palindromes of odd vs even length. What difference do you notice?
Count the frequency of each character.
If each character occurs even number of times, then it must be a palindrome. How about character which occurs odd number of times?
*/

// Bitset. Time: O(n), Space: (n).
class Solution {
public:
    bool canPermutePalindrome(string s) {
        bitset<256> ht;
        for (char c : s) ht.flip(c);
        return ht.count() < 2;
    }
};
