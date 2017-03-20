# Two Pointer Problems
[toc]

There are mainly three types of Two Pointer Problems. We refer to them as:
```
1. Sliding Window;
2. Colliding Two Pointers;
3. Pointers of Two Arrays
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
// Template: Sliding Window - Partition
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

[209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/209_Minimum_Size_Subarray_Sum.cpp))
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

[159. Longest Substring with At Most Two Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/159.%20Longest%20Substring%20with%20At%20Most%20Two%20Distinct%20Characters.cpp))
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

Below is a subtle variation of the above problem:

[487. Max Consecutive Ones II] (https://leetcode.com/problems/max-consecutive-ones-ii/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/487.%20Max%20Consecutive%20Ones%20II.cpp))
```
Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.
Example 1:
Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
    After flipping, the maximum number of consecutive 1s is 4.
Note:
The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
Follow up:
What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory. Could you solve it efficiently?
```

```c++
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        if (nums.empty()) return 0;
        int res = 0;
        int zeros = 0;
        int k = 1;
        for (int left = 0, right = 0; right < nums.size(); right++) {
            if (nums[right] == 0) zeros++;
            while (zeros > k) {
                if (nums[left++] == 0) zeros--;
            }
            res = max(res, right-left+1);
        }
        return res;
    }
};
```


_**A general template for this type of sliding window problem is**_:

```c++
// Template: Sliding Window - Aggregation and Optimization
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

## Colliding Two Pointers
In this type of problems, the two pointers are marching (in an alternating fashion) towards each other. The most canonical problem is the kSum problem:

[15. 3Sum](https://leetcode.com/problems/3sum/#/description)
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

[18. 4Sum](https://leetcode.com/problems/4sum/#/description)
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

One key note to keep in mind: when we use colliding two pointers, almost always we need to **sort** the input array first, if the array is not already sorted.

There are some problems in LeetCode that are just a subtle variation of the Colliding Two Pointers paradigm:

[1. Container With Most Water] (https://leetcode.com/problems/container-with-most-water/#/description)
```
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.
Note: You may not slant the container and n is at least 2.
```

```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = INT_MIN;
        if (height.empty()) return maxArea;
        int left = 0, right = height.size()-1;
        
        while (left < right) {
            int tempArea = min(height[right], height[left]) * (right - left);
            maxArea = max(maxArea, tempArea);
            if (height[left] < height[right]) {
                left++;
            } else if (height[left] > height[right]) {
                right--;
            } else {
                left++;
                right--;
            }
        }
        
        return maxArea;
    }
};
```
And
[42. Trapping Rain Water] (https://leetcode.com/problems/trapping-rain-water/#/description)
```
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.
For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
```

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 2) return 0;
        
        int water = 0;
        int left = 0, right = n-1;
        while (left < right) {
            if (height[left] < height[right]) { // can drop water from the left since the right height is a valid right bound
                int tmpLeftHeight = height[left++];
                while (left < right && height[left] <= tmpLeftHeight) { // while tmpLeftHeight is a valid left bound
                    water += tmpLeftHeight-height[left++];
                }
            } else { // can drop water from the right since the left height is a valid left bound
                int tmpRightHeight = height[right--];
                while (left < right && height[right] <= tmpRightHeight) { // while tmpRightHeight is a valid right bound
                    water += tmpRightHeight-height[right--];
                }
            }
        }
        return water;
    }
};
```

The same idea generalizes to a higher dimension analogue of the above problem:

[407. Trapping Rain Water II] (https://leetcode.com/problems/trapping-rain-water-ii/#/description)
```
Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.
Note:
Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.
Example:
Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]
Return 4.
```

```c++
class Cell {
public:
    int x;
    int y;
    int height;
        
    Cell(int _x = 0, int _y = 0, int _height = 0) : x(_x), y(_y), height(_height) {}
    
    bool operator < (const Cell &c) const {
        return height > c.height;
    }
};

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int water = 0;
        if (heightMap.empty() || heightMap[0].empty()) return water;
        int m = heightMap.size(), n = heightMap[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        priority_queue<Cell> pq;
        
        // push all boundary cells into pq to find the way to pour water in
        for (int i = 0; i < m; i++) {
            pq.push(Cell(i, 0, heightMap[i][0]));
            visited[i][0] = true;
            pq.push(Cell(i, n-1, heightMap[i][n-1]));
            visited[i][n-1] = true;
        }
        for (int j = 0; j < n; j++) {
            pq.push(Cell(0, j, heightMap[0][j]));
            visited[0][j] = true;
            pq.push(Cell(m-1, j, heightMap[m-1][j]));
            visited[m-1][j] = true;
        }
        // BFS mininum height way in to pour water
        while (!pq.empty()) {
            Cell cur = pq.top();
            pq.pop();
            for (int i = 0; i < 4; i++) {
                Cell nb(cur.x+dx[i], cur.y+dy[i]);
                if (!inBound(heightMap, nb) || visited[nb.x][nb.y]) continue;
                // pour water into lower cell neighbors if possible
                water += max(0, cur.height-heightMap[nb.x][nb.y]);
                // pass the current max height along
                nb.height = max(heightMap[nb.x][nb.y], cur.height);
                pq.push(nb);
                visited[nb.x][nb.y] = true;
            }
        }
        return water;
        
    }
private:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    bool inBound(vector<vector<int>>& heightMap, Cell &c) {
        return c.x >= 0 && c.x < heightMap.size() && c.y >= 0 && c.y < heightMap[0].size();
    }
};
```
We will revisit the above problem in more detail when we discuss priority queues and heaps.

Another type of problem that fits into this Colliding Two Pointers paradigm is in palindrome checking.

[125. Valid Palindrome] (https://leetcode.com/problems/valid-palindrome/#/description)
```
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.
Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.
For the purpose of this problem, we define empty string as valid palindrome.
```

```c++
class Solution {
public:
    bool isPalindrome(string s) {
        if (s.size() < 2) return true;
        int left = 0, right = s.size()-1;
        while (left < right) {
            while (left < right && !isalpha(s[left]) && !isdigit(s[left])) left++;
            while (right > left && !isalpha(s[right]) && !isdigit(s[right])) right--;
            if (tolower(s[left]) != tolower(s[right])) return false;
            left++;
            right--;
        }
        return true;
    }
};
```
For this type of application, the use of two pointers is often straightforward.

A general template for the Colliding Two Pointers problems is:

```c++
// Template: Colliding Two Pointers
int left = start, right = end;
while (left < right) {
    if (condition is met) {
        record current state;
        left++;
        right--;
    } else if (condition is not met from one direction) {
        left++;
    } else { // condition is not met from the other direction
        right--;
    }
}
```

## Pointers of Two Arrays
As the title suggests, this type of problem involves two pointers, each pointing at an array. Usually for problems of this type, the goal is to compare the two arrays one by one.

[28. Implement strStr()](https://leetcode.com/problems/implement-strstr/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/028_Implement_strStr().cpp))
```
Implement strStr().
Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
```

```c++
// Straightforward Solution: Time O(mn)
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (haystack.size() < needle.size()) return -1;
        if (needle.empty()) return 0;
        
        int m = haystack.size();
        int n = needle.size();
        
        for (int i = 0; i <= m-n; i++) {
            for (int j = 0; j <= n; j++) {
                if (j == n) return i;
                if (haystack[i+j] != needle[j]) break;
            }
        }
        
        return -1;
    }
};
```

[524. Longest Word in Dictionary through Deleting](https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/#/description)
```
Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string. If there are more than one possible results, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
Example 1:
Input:
s = "abpcplea", d = ["ale","apple","monkey","plea"]
Output: 
"apple"
Example 2:
Input:
s = "abpcplea", d = ["a","b","c"]
Output: 
"a"
Note:
All the strings in the input will only contain lower-case letters.
The size of the dictionary won't exceed 1,000.
The length of all the strings in the input won't exceed 1,000.
```

```c++
class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        string res;
        for (int i = 0; i < d.size(); i++) {
            int pi = 0, pj = 0;
            // try to find d[i] in s
            for (; pi < s.size() && pj < d[i].size(); pi++) {
                pj += s[pi] == d[i][pj]; // beautiful!!!
            }
            if (pj == d[i].size() && (res.size() < d[i].size() || (res.size() == d[i].size() && res > d[i])))
                res = d[i];
        }
        return res;
    }
};
```

[30. Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/#/description)
```
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.
For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]
You should return the indices: [0,9].
(order does not matter).
```

```c++
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int n = s.size(), num = words.size(), len = words[0].size();
        if (n < num * len) return res;
        unordered_map<string, int> need;
        for (string s : words) need[s]++;
        
        for (int i = 0; i < n - num * len + 1; i++) {
            int j = 0;
            unordered_map<string, int> seen;
            for (; j < num; j++) {
                string cur = s.substr(i+j*len, len);
                if (need.find(cur) == need.end() || ++seen[cur] > need[cur]) break;
            }
            if (j == num) res.push_back(i);
        }
        return res;
    }
};
```

[350. Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/350.%20Intersection%20of%20Two%20Arrays%20II.cpp))
```
Given two arrays, write a function to compute their intersection.
Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].
Note:
Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.
Follow up:
What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm is better?
What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
```

```c++
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] == nums2[j]) {
                res.push_back(nums1[i]);
                i++;
                j++;
            } else if (nums1[i] < nums2[j]) {
                i++;
            } else {
                j++;
            }
        }
        return res;
    }
};
```

[21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/#/description)
```
(Slightly modified from the original LeetCode where the merge need not be in place.)
Merge two sorted linked lists in place.
```

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *dummyNode = new ListNode(-1);
        ListNode *prevNode = dummyNode;
        prevNode->next = l1;
        
        while (l1 && l2) {
            if (l1->val < l2->val) {
                l1 = l1->next;
            } else {
                ListNode *tmp = l2->next;
                prevNode->next = l2;
                l2->next = l1;
                l2 = tmp;
            }
            prevNode = prevNode->next;
        }
        
        if (l2) prevNode->next = l2;
        return dummyNode->next;
    }
};
```

[23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/023.%20Merge%20k%20Sorted%20Lists.cpp))
```
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
```

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
class MyCompare {
public:
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *dummyNode = new ListNode(-1);
        ListNode *head = dummyNode;
        priority_queue<ListNode*, vector<ListNode*>, MyCompare> minHeap;
        for (ListNode * l : lists) {
            if (l) minHeap.push((l));
        }
        
        while (!minHeap.empty()) {
            ListNode *curNode = minHeap.top();
            minHeap.pop();
            head->next = curNode;
            head = head->next;
            if (curNode->next) minHeap.push(curNode->next);
        }
        
        return dummyNode->next;
    }
};
```

[243. Shortest Word Distance](https://leetcode.com/problems/shortest-word-distance/#/description)
```
Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.
For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.
Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.
```

```c++
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int pos1 = -1, pos2 = -1;
        int res = words.size();
        for (int i = 0; i < words.size(); i++) {
            if (words[i] == word1) pos1 = i;
            else if (words[i] == word2) pos2 = i;
            
            if (pos1 != -1 && pos2 != -1) res = min(res, abs(pos1 - pos2));
        }
        
        return res;
    }
};
```

[244. Shortest Word Distance II](https://leetcode.com/problems/shortest-word-distance-ii/#/description)
```
This is a follow up of Shortest Word Distance. The only difference is now you are given the list of words and your method will be called repeatedly many times with different parameters. How would you optimize it?
Design a class which receives a list of words in the constructor, and implements a method that takes two words word1 and word2 and return the shortest distance between these two words in the list.
For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.
Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.
```

```c++
class WordDistance {
public:
    WordDistance(vector<string> words) {
        for (int i = 0; i < words.size(); i++) {
            ht[words[i]].push_back(i);
        }
    }
    
    int shortest(string word1, string word2) {
        int i = 0, j = 0;
        vector<int> index1 = ht[word1];
        vector<int> index2 = ht[word2];
        int res = INT_MAX;
        while (i < index1.size() && j < index2.size()) {
            res = min(res, abs(index1[i] - index2[j]));
            if (index1[i] < index2[j]) i++;
            else j++;
        }
        return res;
    }
private:
    unordered_map<string, vector<int>> ht; // string->indices
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance obj = new WordDistance(words);
 * int param_1 = obj.shortest(word1,word2);
 */
```

[245. Shortest Word Distance III](https://leetcode.com/problems/shortest-word-distance-iii/#/description)
```
This is a follow up of Shortest Word Distance. The only difference is now word1 could be the same as word2.
Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.
word1 and word2 may be the same and they represent two individual words in the list.
For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
Given word1 = “makes”, word2 = “coding”, return 1.
Given word1 = "makes", word2 = "makes", return 3.
Note:
You may assume word1 and word2 are both in the list.
```

```c++
class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        int pos1 = -1, pos2 = -1;
        int res = words.size();
        for (int i = 0; i < words.size(); i++) {
            if (words[i] == word1) {
                pos1 = i;
            }
            if (words[i] == word2) {
                if (word1 == word2) pos1 = pos2;
                pos2 = i;
            }
            if (pos1 != -1 && pos2 != -1) res = min(res, abs(pos1 - pos2));
        }
        return res;
    }
};
```

The above problem involving two pointers for two arrays, we generally have two templates:

```c++
// Template: Pointers of Two Arrays - Matching 
int i = initialValue, j = initialValue;
for (i = start; i <= end; i++) {
    for (j = start; j <= end; j++) {
        if (condition is not met) break;
    }
    if (j == end) return current soultion;
}
return no solution;
```

Also:

```c++
// Template: Pointers of Two Arrays - Comparing
int i = initialValue, j = initialValue;
while (i < bound && j < bound) {
    if (condition is met) {
        record current solution;
        i++;
        j++;
    } else if (condition is not met from one direction) {
        i++;
    } else { // condition is not met from the other direction
        j++;
    }
}
```

This summarizes the main types of two pointers problems in LeetCode.

