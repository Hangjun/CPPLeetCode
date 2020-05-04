/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

For example:

Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.

Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.

Hint:

    Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], what should your return? Is this case a valid tree?
    According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”

Note: you can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges. 
*/

/* Analysis:
An undirected graph is a tree if and only if it is connected and doesn't have any undirected cycle.
*/

class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        if (n == 0) return true;
        // tree if and only if graph is connected without undirected cycle
        // build adjacency list
        vector<unordered_set<int>> adj(n);
        for (int i = 0; i < edges.size(); i++) {
            pair<int, int> e = edges[i];
            adj[e.first].insert(e.second);
            adj[e.second].insert(e.first);
        }
        // check if undirected cycles exist
        vector<bool> visited(n, false);
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                components++;
                if (dfs(i, visited, adj, -1)) {
                    // cycle found eminating from node i
                    return false;
                }
            }
        }
        // no cycle found: it is a tree
        return components == 1;
    }
    
    bool dfs(int curNode, vector<bool> &visited, vector<unordered_set<int>> &adj, int parent) {
        visited[curNode] = true;
        for (auto it = adj[curNode].begin(); it != adj[curNode].end(); it++) {
            if (!visited[*it]) {
                if (dfs(*it, visited, adj, curNode)) {
                    return true;
                }
            } else if (*it != parent) {
                return true;
            }
        }
        return false;
    }
};
