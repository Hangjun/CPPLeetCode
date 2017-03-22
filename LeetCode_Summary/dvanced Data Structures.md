# Advanced Data Structures
[toc]

[378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/#/description)
```
Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.
Note that it is the kth smallest element in the sorted order, not the kth distinct element.
Example:
matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,
return 13.
Note: 
You may assume k is always valid, 1 ≤ k ≤ n2.
```

```c++
class Cell {
public:
    int x;
    int y;
    int val;
   
    Cell(int _x = 0, int _y = 0, int _val = 0):x(_x), y(_y), val(_val) {}
    
    bool operator < (const Cell &c) const {
        return val > c.val;
    }
};

struct pair_hash {
    inline size_t operator()(const pair<int,int> &v) const {
        return v.first*31 + v.second;
    }
};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        if (matrix.empty() || matrix[0].empty()) return INT_MAX;
        int m = matrix.size(), n = matrix[0].size();
        if (k > m*n || k < 1) return INT_MAX;
        unordered_set<pair<int, int>, pair_hash> visited;
        priority_queue<Cell> minHeap;
        int count = 0;
        Cell c(0, 0, matrix[0][0]);
        visited.insert(make_pair(0, 0));
        minHeap.push(c);
        while (count < k-1) {
            Cell cur = minHeap.top();
            minHeap.pop();
            ++count;
            for (int i = 0; i < 2; i++) { // next bigger elements are on the right and bottom
                int nx = cur.x + dx[i];
                int ny = cur.y + dy[i];
                pair<int, int> px = make_pair(nx, ny);
                if (!inBound(matrix, nx, ny) || visited.find(px) != visited.end()) continue;
                visited.insert(px);
                minHeap.push(Cell(nx, ny, matrix[nx][ny]));
            }
        }
        return minHeap.top().val;
    }
    
private:
    bool inBound(vector<vector<int>> &matrix, int x, int y) {
        int m = matrix.size();
        int n = matrix[0].size();
        return x >= 0 && x < m && y >= 0 && y < n;
    }
    int dx[2] = {1, 0};
    int dy[2] = {0, 1};
};
```

## Priority Queue / Heap

## Union-Find

## Red-Black Tree

## AVL Tree

## Trie (Prefix Tree)

## Segment Tree

## Kd-Tree

## Skip Linked List

