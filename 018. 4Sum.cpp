/*
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note: The solution set must not contain duplicate quadruplets.

For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/

// Brute-force. Time: O(n^3), Space: O(1). Do not forget to sort the input array first. 1Sum + 1Sum + 2Sum.
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if (nums.size() < 4) return res;
        
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < nums.size()-3; i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            for (int j = i+1; j < nums.size()-2; j++) {
                if (j > i+1 && nums[j] == nums[j-1]) continue;
                int left = j+1, right = nums.size()-1;
                while (left < right) {
                    int tmpSum = nums[i]+nums[j]+nums[left]+nums[right];
                    if (tmpSum == target) {
                        res.push_back({nums[i],nums[j],nums[left],nums[right]});
                        left++;
                        right--;
                        while (left < right && nums[left] == nums[left-1]) left++;
                        while (left < right && nums[right] == nums[right+1]) right--;
                    } else if (tmpSum < target) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        return res;
    }
};

/* 
Analysis: Use hash tale to store all possible 2Sums. Time: O(n^2), Space: O(n). Do not forget to sort the input array first. 2Sum + 2Sum.
*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if (nums.size() < 4) return res;
        sort(nums.begin(), nums.end());
        unordered_map<int, vector<pair<int, int>>> ht; // 2Sum -> vector of indices of elements add up to that sum
        for (int i = 0; i < nums.size()-1; i++) {
            for (int j = i+1; j < nums.size(); j++) {
                ht[nums[i]+nums[j]].push_back(make_pair(i, j));
            }
        }
        
        for (int i = 0; i < nums.size()-3; i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            for (int j = i+1; j < nums.size()-2; j++) {
                if (j > i+1 && nums[j] == nums[j-1]) continue;
                int residual = target-nums[i]-nums[j];
                if (ht.find(residual) == ht.end()) continue;
                bool firstPush = true; // per fixed (i, j) pair
                for (auto p : ht[residual]) {
                    if (p.first <= j) continue;
                    if (!firstPush && res.back()[2] == nums[p.first]) continue;
                    res.push_back({nums[i], nums[j], nums[p.first], nums[p.second]});
                    firstPush = false;
                }
            }
        }
        return res;
    }
};
