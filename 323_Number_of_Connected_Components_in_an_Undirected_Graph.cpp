/*
 Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to find the number of connected components in an undirected graph.

Example 1:

     0          3
     |          |
     1 --- 2    4

Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.

Example 2:

     0           4
     |           |
     1 --- 2 --- 3

Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.

Note:
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges. 
*/

// Union-Find Solution
class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        if (edges.empty()) return n;
        if (n < 2) return 1;
        vector<int> parent(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        int count = 0;
        for (int i = 0; i < edges.size(); i++) {
            int n1 = edges[i].first;
            int n2 = edges[i].second;
            int p1 = find(parent, n1);
            int p2 = find(parent, n2);
            if (p1 != p2) {
                unite(parent, n1, n2);
                count++;
            }
        }
        return n - count;
    }
    
    int find(vector<int> &parent, int node) {
        if (node != parent[node]) {
            // path compression from node --> ultimate parent node
            parent[node] = find(parent, parent[node]);
        }
        return parent[node];
    }
    
    void unite(vector<int> &parent, int n1, int n2) {
        int p1 = find(parent, n1);
        int p2 = find(parent, n2);
        if (p1 != p2) {
            // unite the parent nodes, NOT n1, n2!
            parent[p1] = min(p1, p2);
            parent[p2] = min(p1, p2);
        }
    }
};

// BFS solution
class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        if (edges.empty()) return n;
        if (n < 2) return 1;
        // re-represent the graph using adjacency matrix and use BFS
        // we can use either vector<unordered_set> or vector<list>
        vector<unordered_set<int>> adj(n);
        for (int i = 0; i < edges.size(); i++) {
            pair<int, int> e = edges[i];
            adj[e.first].insert(e.second);
            adj[e.second].insert(e.first);
        }
        vector<bool> visited(n, false);
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                bfs(adj, i, visited);
                components++;
            }
        }
        return components;
    }
    
    void bfs(vector<unordered_set<int>> &adj, int index, vector<bool> &visited) {
        visited[index] = true;
        queue<int> q;
        q.push(index);
        while (!q.empty()) {
            int curNode = q.front();
            q.pop();
            // level order search its unvisited neighbors
            unordered_set<int>::iterator it;
            for (it = adj[curNode].begin(); it != adj[curNode].end(); it++) {
                if (!visited[*it]) {
                    visited[*it] = true;
                    q.push(*it);
                }
            }
        }
    }
};

// DFS solution
class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        if (edges.empty()) return n;
        if (n < 2) return 1;
        // construct adjancy list representation of the graph
        vector<unordered_set<int>> adj(n); // adj size = n
        for (int i = 0; i < edges.size(); i++) {
            pair<int, int> e = edges[i];
            adj[e.first].insert(e.second);
            adj[e.second].insert(e.first);
        }
        int components = 0;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(adj, i, visited);
                components++;
            }
        }
        return components;
    }
    
    void dfs(vector<unordered_set<int>> &adj, int index, vector<bool> &visited) {
        visited[index] = true;
        // adj[index] contains all vertices incident to index
        for (auto it = adj[index].begin(); it != adj[index].end(); it++) {
            if (!visited[*it]) {
                dfs(adj, *it, visited);
            }
        }
    }
};
