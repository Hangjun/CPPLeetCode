/*
 For a undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example 1:

Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3

return [1]

Example 2:

Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5

return [3, 4]

Hint:

    How many MHTs can a graph have at most?

Note:

(1) According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”

(2) The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf. 
*/


/* Submission #1: Failed:
Submission Result: Wrong Answer
Input: 4
[[1,0],[1,2],[1,3]]
Output: [3,1]
Expected: 
*/
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        vector<int> res;
        if (n == 0) return res;
        if (edges.empty()) {
            for (int i = 0; i < n; i++) {
                res.push_back(i);
            }
            return res;
        }
        vector<int> ind(n, 0);
        vector<vector<int>> adj(n, vector<int>());
        for (auto e : edges) {
            adj[e.first].push_back(e.second);
            adj[e.second].push_back(e.first);
            ind[e.first]++;
            ind[e.second]++;
        }
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (ind[i] == 1) {
                q.push(i);
            }
        }
        while (n > 2) {
            int u = q.front();
            q.pop();
            n--;
            for (auto v : adj[u]) {
                if (--ind[v] == 1) {
                    q.push(v);
                }
            }
        }
        while (!q.empty()) {
            res.push_back(q.front());
            q.pop();
        }
        
        return res;
    }
};


/* Analysis:
This is due to the misunderstanding of the algorithm: we must delete all the leaf nodes from the previous round before testing n > 2.
In the Course Schedule problem, we do not need to worry about this since every course will be examined. 
*/

// Submission #2: Accpeted.
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        vector<int> res;
        if (n == 0) return res;
        if (edges.empty()) {
            for (int i = 0; i < n; i++) {
                res.push_back(i);
            }
            return res;
        }
        vector<int> ind(n, 0);
        vector<vector<int>> adj(n, vector<int>());
        for (auto e : edges) {
            adj[e.first].push_back(e.second);
            adj[e.second].push_back(e.first);
            ind[e.first]++;
            ind[e.second]++;
        }
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (ind[i] == 1) {
                q.push(i);
            }
        }
        while (n > 2) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                int u = q.front();
                q.pop();
                n--;
                for (auto v : adj[u]) {
                    if (--ind[v] == 1) {
                        q.push(v);
                    }
                }
            }
            
        }
        while (!q.empty()) {
            res.push_back(q.front());
            q.pop();
        }
        
        return res;
    }
};




