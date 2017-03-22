# Binary Search Problems

[35. Search Insert Position](https://leetcode.com/problems/search-insert-position/#/description)
'''
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
You may assume no duplicates in the array.
Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0
'''

```c++
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        while (left <= right) {
            int mid = left + (right-left)/2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) left = mid+1;
            else right = mid-1;
        }
        return left;
    }
};
```

[162. Find Peak Element](https://leetcode.com/problems/find-peak-element/#/description)
```
A peak element is an element that is greater than its neighbors.
Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.
The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
You may imagine that num[-1] = num[n] = -∞.
For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.
Note:
Your solution should be in logarithmic complexity.
```

```c++
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        // loop invariant: peak is contained in [left, right]
        while (left < right) {
            int mid = left + (right - left)/2;
            if (nums[mid] < nums[mid+1]) left = mid+1;
            else right = mid;
        }
        return left;
    }
};
```

[392. Is Subsequence](https://leetcode.com/problems/is-subsequence/#/description) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/392.%20Is%20Subsequence.cpp))
```
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
```

```c++
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
```

[74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/#/description)
```
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,
Consider the following matrix:
[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
Given target = 3, return true.
```

```c++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int m = matrix.size(), n = matrix[0].size();
        // without this check the algorithm will run out of bound
        if (target < matrix[0][0] || target > matrix[m-1][n-1]) return false; 
        int row = m-1, col = 0;
        while (row >= 0 && col < n) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] > target) {
                row--;
            } else {
                col++;
            }
        }
        return false;
    }
};
```

[311. Sparse Matrix Multiplication](https://leetcode.com/problems/sparse-matrix-multiplication/#/description)
```
Given two sparse matrices A and B, return the result of AB.
You may assume that A's column number is equal to B's row number.
Example:
A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]
B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]
|  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |
```

```c++
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        int m = A.size();
        int n = B.size();
        int k = B[0].size();
        vector<vector<int>> res(m, vector<int>(k, 0));
        
        // find all non-zero elements in A
        vector<pair<int, int>> AReduce;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (A[i][j]) AReduce.push_back(make_pair(i, j));
            }
        }
        
        // compute all non-zero elements in B and store them in row index -> <non zero elements> hash table
        unordered_map<int, vector<int>> BReduce;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                if (B[i][j]) BReduce[i].push_back(j);
            }
        }
        
        // multiply AReduce with BReduce
        for (auto p : AReduce) {
            int x1 = p.first;
            int y1 = p.second;
            int x2 = y1;
            for (auto y2 : BReduce[x2]) res[x1][y2] += A[x1][x2]*B[x2][y2];
        }
        
        return res;
    }
};
```

[475. Heaters](https://leetcode.com/problems/heaters/#/solutions) ([Github Solution](https://github.com/Hangjun/MyLeetCode/blob/master/475.%20Heaters.cpp))
```
Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.
Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.
So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.
Note:
Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
As long as a house is in the heaters' warm radius range, it can be warmed.
All the heaters follow your radius standard and the warm radius will the same.
Example 1:
Input: [1,2,3],[2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
Example 2:
Input: [1,2,3,4],[1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.
```

```c++
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int res = INT_MIN;
        sort(heaters.begin(), heaters.end());
        
        for (int house : houses) {
            int index = findUpperBoundIndex(heaters, house); // find the smallest upper bound of house
            int curDist = INT_MAX;
            if (index != heaters.size()) curDist = heaters[index]-house;
            if (index) curDist = min(curDist, house-heaters[index-1]);
            res = max(res, curDist);
        }
        
        return res;
    }
    
    // return the first element that is not smaller than val
    int findUpperBoundIndex(vector<int> &nums, int val) { 
        int left = 0, right = nums.size()-1;
        while (left < right) {
            int mid = left + (right-left)/2;
            if (nums[mid] < val) left = mid+1;
            else right = mid;
        }
        return nums[left] >= val ? left : left+1;
    }
};
```



