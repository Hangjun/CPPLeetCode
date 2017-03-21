/*
Given a string s and a string t, check if s is subsequence of t.

You may assume that there is only lower case English letters in both s and t. t is potentially a very long (length ~= 500,000) string, and s is a short string (<=100).

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"

Return true.

Example 2:
s = "axc", t = "ahbgdc"

Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one by one to see if T has its subsequence. In this scenario, how would you change your code?
*/

/*
Analysis: A linear scan of the larger string t will do.

Time: O(n), n = t.size(); Space: O(1).
*/
class Solution {
public:
    bool isSubsequence(string s, string t) {
        if (s.empty()) return true;
        int i = 0, j = 0;
        for (; i < t.size(); i++) {
            j += t[i] == s[j];
            if (j == s.size()) return true;
        }
        return false;
    }
};

/*
Analysis: For the follow up, if the "dictionary" string t is too large, and we have to make many queries like this, the natural idea when it comes to large string is to use a hash table. This should be very straightforward, as there are only 26 characters. Therefore a larger string much have lots of duplciates while its hash table representation has at most 26 keys.

Having transformed the input t to its hash table representation (key = char, value = [index array of this char]), for each character in s, we can do a binary search to find the smallest admissible index. Due to the subsequence requirement, we need to repeatedly update the lower bound for the admissible indices.

Time: O(mlogn), m = s.size(), n = t.size(); Space: O(n). The time complexity is calcuated by noting that the average size of an [index array] w.r.t. a character is n/26 = O(n). Therefore each look up takes O(logn) time. In the case of m small and n large, this is much faster than the above linear scan two pointer solution.
*/
class Solution {
public:
    bool isSubsequence(string s, string t) {
        if (s.empty()) return true;
        unordered_map<char, vector<int>> ht;
        for (int i = 0; i < t.size(); i++) ht[t[i]].push_back(i);
        int lowerBound = 0;
        for (char c : s) {
            if (ht.find(c) == ht.end()) return false;
            vector<int> indexArray = ht[c];
            // find the first index that is >= lowerBound
            int tmpIndex = binarySearch(indexArray, lowerBound);
            if (tmpIndex == indexArray.size()) return false;
            lowerBound = tmpIndex+1;
        }
        return true;
    }
    
    int binarySearch(vector<int> &nums, int lb) {
        int n = nums.size();
        if (lb > nums[n-1]) return n;
        int left = 0, right = n-1;
        while (left < right) {
            int mid = left + (right-left)/2;
            if (nums[mid] == lb) return nums[mid]; // all indices are distinct
            else if (nums[mid] < lb) left = mid+1;
            else right = mid;
        }
        return nums[left];
    }
};
