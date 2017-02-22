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
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> powerset;
        vector<int> curSoln;
        powerset.push_back(curSoln);
        sort(nums.begin(), nums.end());
        dfs(nums, 0, curSoln, powerset);
        return powerset;
    }
    
    void dfs(vector<int> &nums, int start, vector<int> &curSoln, vector<vector<int>> &powerset) {
        if (start >= nums.size()) return;
        for (int i = start; i < nums.size(); i++) {
            curSoln.push_back(nums[i]);
            powerset.push_back(curSoln);
            dfs(nums, i+1, curSoln, powerset);
            curSoln.pop_back();
        }
    }
};

/*
The slickest solution is to realize that, the resulting powerset has size 2^n, where n is the number of elements in nums. We can use bitset to toggle 0 and 1 to represent whether the current element is included in the set or not. We include this solution just for fun.
*/
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> powerset;
        sort(nums.begin(), nums.end());
        unsigned long long numSets = pow(2, nums.size());
        for (auto i = 0; i < numSets; i++) {
            powerset.push_back(bitToSet(nums, i));
        }
        return powerset;
    }
    
    vector<int> bitToSet(vector<int> &nums, unsigned long long bitIndex) {
        vector<int> res;
        int i = 0;
        // each bit in bitIndex describes which element in numbers is chosen for this set
        while (bitIndex) {
            if (bitIndex & 1) {
                res.push_back(nums[i]);
            }
            i++;
            bitIndex = bitIndex >> 1;
        }
        return res;
    }
};
