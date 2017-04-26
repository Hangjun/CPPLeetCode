# Google Interval Prep
[toc]

## Binary Search
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

## Backtracking
Backtracking is an algorithmic paradigm that tries different solutions until finds a solution that “works”. Problems which are typically solved using backtracking technique have following property in common. These problems can only be solved by trying every possible configuration and each configuration is tried only once. A Naive solution for these problems is to try all configurations and output a configuration that follows given problem constraints. Backtracking works in incremental way and is an optimization over the Naive solution where all possible configurations are generated and tried.

[46. Permutations](https://leetcode.com/problems/permutations/#/description)
```
Given a collection of distinct numbers, return all possible permutations.
For example,
[1,2,3] have the following permutations:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
```

```c++
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty()) return res;
        vector<int> localSoln;
        vector<bool> canUse(nums.size(), true);
        sort(nums.begin(), nums.end());
        dfs(nums, canUse, localSoln, res);
        return res;
    }
    
    void dfs(vector<int> &nums, vector<bool> &canUse, vector<int> &localSoln, vector<vector<int>> &res) {
        if (localSoln.size() == nums.size()) {
            res.push_back(localSoln);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if ((i > 0 && nums[i] == nums[i-1] && canUse[i-1]) || !canUse[i]) continue;
            canUse[i] = false;
            localSoln.push_back(nums[i]);
            dfs(nums, canUse, localSoln, res);
            localSoln.pop_back();
            canUse[i] = true;
        }
    }
};
```

[40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/#/description)
```
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
Each number in C may only be used once in the combination.
Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
A solution set is: 
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
```

```c++
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> res;
        if (candidates.empty()) return res;
        vector<int> curSoln;
        sort(candidates.begin(), candidates.end()); // when in backtracking, sort first
        dfs(candidates, 0, target, curSoln, res);
        
        return res;
    }
    
    void dfs(vector<int> &candidates, int start, int target, vector<int> &curSoln, vector<vector<int>> &res) {
        if (target == 0) {
            res.push_back(curSoln);
            return;
        }
        
        for (int i = start; i < candidates.size(); i++) {
            // avoid duplicate combination sums
            if (i > start && candidates[i] == candidates[i-1]) continue;
            // avoid infinite loops
            if (candidates[i] > target) continue;
            curSoln.push_back(candidates[i]);
            dfs(candidates, i+1, target-candidates[i], curSoln, res);
            curSoln.pop_back();
        }
    }
};
```


## DFS

```c++
// Graph
DFS(G,v):
    label v as visited
        for all edges from v to w in G.adjacentEdges(v) do
            if vertex w is not labeled as discovered then
                DFS(G,w)
```

```c++
// Tree
DFS(RootNode):
    label RootNode as visited
        for node in [RootNode->left, RootNode->right]
            if node not NULL and node not visited
                DFS(node)
```

## BFS

```c++
// Tree
BFS(RootNode):
    queue<TreeNode> q;
    mark RootNode as visited;
    q.push(RootNode);
    
    while (!q.empty()) {
        curNode = q.front();
        q.pop();
        for node in [curNode->left, curNode->right]:
            if node not NULL and node not visited:
                mark node as visited
                q.push(node)
    }
```

## Tree
### Tree Traversals
* Preorder: mid-left-right
    1. Check if the current node is empty / null.
    2. Display the data part of the root (or current node).
    3. Traverse the left subtree by recursively calling the pre-order function.
    4. Traverse the right subtree by recursively calling the pre-order function.

    ```c++
    // Recursive
    preorder(node):
        if (node = null)
            return
        visit(node)
        preorder(node.left)
        preorder(node.right)
    ```
    
    ```c++
    // Iterative
    iterativePreorder(node)
        if (node = null)
            return
        s ← empty stack
        s.push(node)
        while (not s.isEmpty())
            node ← s.pop()
            visit(node)
            //right child is pushed first so that left is processed first
            if (node.right ≠ null)
              s.push(node.right)
            if (node.left ≠ null)
              s.push(node.left)
    ```
    
* Inorder: left-mid-right
    1. Check if the current node is empty / null.
    2. Traverse the left subtree by recursively calling the in-order function.
    3. Display the data part of the root (or current node).
    4. Traverse the right subtree by recursively calling the in-order function.
    
    ```c++
    // Recursive
    inorder(node)
        if (node = null)
            return
        inorder(node.left)
        visit(node)
        inorder(node.right)
    ```
    
    ```c++
    // Iterative
    iterativeInorder(node)
        s ← empty stack
        while (not s.isEmpty() or node ≠ null)
        if (node ≠ null)
            s.push(node)
            node ← node.left
        else
            node ← s.pop()
            visit(node)
            node ← node.right
    ```
    
    
Inorder traversal of a **binary search tree** is monotonic increasing.

* Postorder: left-right-mid
    1. Check if the current node is empty / null.
    2. Traverse the left subtree by recursively calling the post-order function.
    3. Traverse the right subtree by recursively calling the post-order function.
    4. Display the data part of the root (or current node).

```c++
// Recursive
postorder(node)
  if (node = null)
    return
  postorder(node.left)
  postorder(node.right)
  visit(node)
```

```c++
// Iterative (no need to memorize)
iterativePostorder(node)
  s ← empty stack
  lastNodeVisited ← null
  while (not s.isEmpty() or node ≠ null)
    if (node ≠ null)
      s.push(node)
      node ← node.left
    else
      peekNode ← s.peek()
      // if right child exists and traversing node
      // from left child, then move right
      if (peekNode.right ≠ null and lastNodeVisited ≠ peekNode.right)
        node ← peekNode.right
      else
        visit(peekNode)
        lastNodeVisited ← s.pop()
```

[102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/#/description)
```
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
```

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        queue<TreeNode *> curLevel;
        queue<TreeNode *> nextLevel;
        curLevel.push(root);
        
        while (!curLevel.empty()) {
            vector<int> level;
            while (!curLevel.empty()) {
                TreeNode *curNode = curLevel.front();
                curLevel.pop();
                level.push_back(curNode->val);
                if (curNode->left) nextLevel.push(curNode->left);
                if (curNode->right) nextLevel.push(curNode->right);
            }
            res.push_back(level);
            swap(curLevel, nextLevel);
        }
        
        return res;
    }
};
```

## Graph
Graphs can be categorized as **directed** and **undirected**. There are three common representations of a graph: 
1. Adjacency matrix adj[i][j] = 1 if there is an edge from i to j, and adj[i][j] = 0 otherwise. The adjacency matrix of an undirected graph is by definition symmetric.
2. Neighbor list: for every node in the graph, we keep track of its neighbors. Concretely, we can define a graph as a collection of the following graph nodes.
3. Edge list. In this representation, a graph is simply a set of edges, given in c++ as pairs.

```c++
class GraphNode {
public:
    int val;
    vector<GraphNode> neighbors;
};
```

Graph problems can be mainly categorized as:
1. **Connected components**
2. **Cycle detection**
3. **Topological sorting**

Depending on whether the graph is directed or not, we have $6$ different graph problems. 

Undirected graph:
1. **Connected components**: BFS, DFS, Union-Find
2. **Cycle detection**: DFS + parent
3. **Topological sorting**: N/A.

Directed graph:
1. **Weakly connected components**: 2 passes of Union-Find
2. **Strongly connected components** (not required to know): 2 passes of DFS
2. **Cycle detection**: DFS + instack
3. **Topological sorting**: DFS



## Dynamic Programming
[Google Interview Problem: Maximum Holiday]
```

```

