# Two Pointer Problems
[toc]

There are mainly three types of Two Pointer Problems. We refer to them as:
```
1. Sliding window;
2. Colliding pointers;
3. Pointers taking turns
```

## Sliding Window
This type of problem involves two (or more) pointers, usually referred to as a *left* pointer and a *right* pointer. The canonical problem is to move the right pointer to the right, usually in a greedy fashion, and then do some calculation before adjusting the left pointer to the right while maintaining some conditions.

The sliding window problems on LeetCode can be classified into two categories: **partition**, **aggregation and maximization**.

### Sliding Window - Partition
This type of problem involves partition an array according to some rule. For instance:
```
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.
```

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int left = 0, right = 0;
        while (right < nums.size()) {
            if (nums[right]) swap(nums[left++], nums[right++]);
            else right++;
        }
    }
};
```
A slightly mutated problem is to modify the array so that only non-zero elements are kept. In this case we can use an "overwrite" algorithm:
```
Given an array and a value, remove all instances of that value in place and return the new length. Do not allocate extra space for another array, you must do this in place with constant memory.
The order of elements can be changed. It doesn't matter what you leave beyond the new length.
Example: 
Given input array nums = [3,2,2,3], val = 3
Your function should return length = 2, with the first two elements of nums being 2.
For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].
```

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.empty()) return nums.size();
        int len = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) nums[++len] = nums[i];
        }
        return len+1;
    }
};
```
One generalization of this type of problem is to have more than two classes to partition:
```
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
```

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        int cur = 0;
        while (cur <= right) {
            if (nums[cur] == 0) {
                swap(nums[left++], nums[cur++]);
            } else if (nums[cur] == 2) {
                swap(nums[cur], nums[right--]);
            } else {
                cur++;
            }
        }
    }
};
```
The key to solving this type of problem is to have a clear idea about the **loop invariant**.

Further generalization to more than 3 classes is beyond the scope of the algorithms we are discussing here. We can use algorithms like bucket sort to do the partition more efficiently:
```
Given an array of n objects with k different colors (numbered from 1 to k), sort them so that objects of the same color are adjacent, with the colors in the order 1, 2, ... k.
Example:
Given colors=[3, 2, 2, 1, 4], k=4, your code should sort colors in-place to [1, 2, 2, 3, 4].
```

```c++
class Solution{
public:
    /**
     * @param colors: A list of integer
     * @param k: An integer
     * @return: nothing
     */    
    void sortColors2(vector<int> &colors, int k) {
        for (int i = 0; i < colors.size(); i++) {
            while (colors[i] > 0) { // colors[i] > 0 iff this color is not bucketed yet
                int bucketId = colors[i]-1;
                if (colors[bucketId] > 0) { // bucketId is not in use
                    colors[i] = colors[bucketId];
                    colors[bucketId] = -1; // count = 1 for color[i] (before the swap)
                } else { // this bucket is occupied - increment the count
                    colors[bucketId]--;
                    colors[i] = 0;
                }
            }
        }
        
        int len = colors.size()-1; // fill the colors backwards so that we do not overwrite the bucketing information
        for (int i = k-1; i >= 0; i--) { // bucketing informations saved in colors[0:k-1]
            if (colors[i] == 0) continue;
            int count = -colors[i];
            while (count > 0) {
                colors[len--] = i+1;
                count--;
            }
        }
    }
};
```
A general template for this type of sliding window problem is

```c++
int left = initialValue, right = initialValue;
while (right < bound) {
    if (current value belongs to class I) {
        swap(right++, left++);
    } else { // class II
        right++;
    }
}
```


### Sliding Window - Aggregation and Optimization
This type of problem tries to find an sliding window that satisfies certain conditions (often in terms of aggregation) in an optimal way. For instance,
```
Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.
For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.
```

```c++
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if (nums.empty()) return 0;
        int left = 0, right = 0;
        int sum = 0;
        int minLen = INT_MAX;
        while (left < nums.size()) {
            while (right < nums.size() && sum < s) {
                sum += nums[right++];
            }
            if (sum < s) break;
            // sum >= s: shrink left to to the right as much as possible
            minLen = min(minLen, right-left);
            sum -= nums[left++];
        }
        return minLen == INT_MAX ? 0 : minLen;
    }
};
```
In the above problem, the aggregation condition is partial sum. We can have different conditions. In the following problem, the condition is the number of distinct characters:
```
Given a string, find the length of the longest substring T that contains at most 2 distinct characters. For example, Given s = “eceba”, T is "ece" which its length is 3.
```

```c++
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        if (s.size() < 3) return s.size();
        vector<int> dict(256, 0);
        int maxLen = 0;
        int left = 0;
        int count = 0;
        for (int right = 0; right < s.size(); right++) {
            dict[s[right]]++;
            if (dict[s[right]] == 1) { // new character
                count++;
                while (count > 2) { // shrink window if needed
                    dict[s[left]]--;
                    if (dict[s[left]] == 0) count--;
                    left++;
                }
            }
            maxLen = max(maxLen, right-left+1);
        }
        return maxLen;
    }
};
```
We can generalize the above problem to $k$ distinct characters by change $count > 2$ condition to $count> k$. 

A general template for this type of sliding window problem is:

```c++
int left = intialValue, right = intialValue;
int optimalCondition;
while (right < bound) {
    while (right < bound && condition is not met) {
        update current condition;
        right++;
    }
    if (condition is still not met) {
        condition cannot be satisfied;
        break;
    }
    update optimalCondition;
    left++;
}
return optimalCondition;
```
The only differences among problems of this type is **how the condition update is calculated** (e.g. via partial sum or hash table) and **how the pointer updates are defined**.

## Collision of Two Pointers
In this type of problems, the two pointers are marching (in an alternating fashion) towards each other. The most canonical problem is the kSum problem:

[3Sum](https://leetcode.com/problems/3sum/#/description)
```
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
Note: The solution set must not contain duplicate triplets.
For example, given array S = [-1, 0, 1, 2, -1, -4],
A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() < 3) return res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size()-2; i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            int left = i+1, right = nums.size()-1;
            while (left < right) {
                int tmpSum = nums[i]+nums[left]+nums[right];
                if (tmpSum == 0) {
                    res.push_back({nums[i], nums[left], nums[right]});
                    left++;
                    right--;
                    while (left < right && nums[left] == nums[left-1]) left++;
                    while (left < right && nums[right] == nums[right+1]) right--;
                } else if (tmpSum > 0) {
                    right--;
                } else {
                    left++;
                }
            }
        }
        return res;
    }
};
```
And

[4Sum](https://leetcode.com/problems/4sum/#/description)
``` 
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
Note: The solution set must not contain duplicate quadruplets.
For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.
A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
```

```c++
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
```
In the above 4Sum problem, we can have a faster algorithm using hash tables, but the colliding two pointer solution is so simple that one can hardly make any mistakes. 

One key note to keep in mind: when we use colliding two pointers, almost always we need to **sort** the input array.


