/*
Given a set of distinct integers, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/

/*
The first solution is to construct the powerset (the result) by adding numbers to every set of the existing powerset to create new powersets. This is the more natural solution in my opinion.
*/

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> powerset;
        powerset.push_back(vector<int>{});
        sort(nums.begin(), nums.end());
        for (int n : nums) {
            int s = powerset.size();
            for (int i = 0; i < s; i++) {
                vector<int> set = powerset[i];
                set.push_back(n);
                powerset.push_back(set);
            }
        }
        
        return powerset;
    }
};

/*
We can also construct the powerset using backtracking.
*/

