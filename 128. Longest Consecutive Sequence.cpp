/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.
*/

/*
The first immediate idea is to sort it first. However, the time complexity is required to be O(n), so sorting is out. The next immediate idea is then to use a hash set to record all the elements in the array. After that, for each element n in the array, we check in the hash set to see if n-1 and n+1 are there, and if yes n-2 and n+2, etc. 

One catch here is that, suppose n+1 indeed exists after checking, we need to remove it from the hash set to avoid duplicated counting (e.g. when the current value is n-1). Each insert/erase operation for a hash set is amorized O(1).
*/

// Time O(n), Space O(n).
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        unordered_set<int> hs(nums.begin(), nums.end()); // notice how we can initialize a hash set so concisely
        int maxLen = 1;
        for (int n : nums) {
            if (hs.empty()) break;
            if (hs.find(n) == hs.end()) continue;
            hs.erase(n);
            int prev = n-1, next = n+1;
            while (hs.find(prev) != hs.end()) hs.erase(prev--);
            while (hs.find(next) != hs.end()) hs.erase(next++);
            
            maxLen = max(maxLen, next - prev - 1); // next-prev+1-2: (-2) because both next and prev will be incremented once more before the while loop breaks
        }
        
        return maxLen;
    }
};
