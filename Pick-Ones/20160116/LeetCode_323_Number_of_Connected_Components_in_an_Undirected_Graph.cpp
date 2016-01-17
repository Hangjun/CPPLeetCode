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

// Submission #1: Failed:  Wrong Answer
/* 
Input: 4
[[0,1],[2,3],[1,2]]
Output: 2
Expected: 1 
*/

class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        // corner cases
        if (edges.empty()) return n;
        if (n < 2) return 1;
        // initialize parent table
        vector<int> parent(n, -1);
        for (int i = 0; i < edges.size(); i++) {
            int n1 = edges[i].first;
            int n2 = edges[i].second;
            // there is an edge between node n1 and n2, merge them
            // initialize the parent node
            int p1 = find(parent, n1);
            int p2 = find(parent, n2);
            // union the two nodes
            myUnion(parent, n1, n2);
        }
        // count the number of "big brothers"
        unordered_set<int> components;
        for (int i = 0; i < n; i++) {
            components.insert(parent[i]);
        }
        return components.size();
    }
    
    int find(vector<int> &parent, int node) {
        if (parent[node] == -1) {
            parent[node] = node;
            return parent[node];
        }
        int p = node;
        while(p != parent[p]) p = parent[p];
        // path compression along node --> p
        int f = node;
        while (f != p) {
            int tmp = parent[f];
            parent[f] = p;
            f = tmp;
        }
        return p;
    }
    
    void myUnion(vector<int> &parent, int n1, int n2) {
        int p1 = find(parent, n1);
        int p2 = find(parent, n2);
        if (p1 != p2) {
            parent[n1] = min(p1, p2);
            parent[n2] = min(p1, p2);
        }
    }
};

/* Analysis:
After running the above test case, the parent table looks like this:
0   1   2   3
0   0   0   2
In our code above, we didn't manage to update the parent of node 3.
*/

// Submission #2: Failed after trying to fix the bug by sorting the input edge set by the first index
/*
Submission Result: Wrong Answer
Input: 6
[[0,1],[0,2],[2,5],[3,4],[3,5]]
Output: 2
Expected: 1 
*/

bool pairCompare(pair<int, int> &p1, pair<int, int> &p2) {
    return p1.first < p2.first;
}

class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        // corner cases
        if (edges.empty()) return n;
        if (n < 2) return 1;
        // initialize parent table
        vector<int> parent(n, -1);
        // sort edges on the first index
        sort(edges.begin(), edges.end(), pairCompare);
        for (int i = 0; i < edges.size(); i++) {
            int n1 = edges[i].first;
            int n2 = edges[i].second;
            // there is an edge between node n1 and n2, merge them
            // initialize the parent node
            int p1 = find(parent, n1);
            int p2 = find(parent, n2);
            // union the two nodes
            myUnion(parent, n1, n2);
        }
        // count the number of "big brothers"
        unordered_set<int> components;
        for (int i = 0; i < n; i++) {
            components.insert(parent[i]);
        }
        return components.size();
    }
    
    int find(vector<int> &parent, int node) {
        if (parent[node] == -1) {
            parent[node] = node;
            return parent[node];
        }
        int p = node;
        while(p != parent[p]) p = parent[p];
        // path compression along node --> p
        int f = node;
        while (f != p) {
            int tmp = parent[f];
            parent[f] = p;
            f = tmp;
        }
        return p;
    }
    
    void myUnion(vector<int> &parent, int n1, int n2) {
        int p1 = find(parent, n1);
        int p2 = find(parent, n2);
        if (p1 != p2) {
            parent[n1] = min(p1, p2);
            parent[n2] = min(p1, p2);
        }
    }
};

/* Analysis:
The parent table of the above test case is:
0   1   2   3   4   5
0   0   0   0   3   0
*/


// Submission #3: Failed after trying to fix it by update the parent index after scanning the edge set but before counting the components
/*
Submission Result: Wrong Answer
Input: 10
[[5,8],[3,5],[1,9],[4,5],[0,2],[1,9],[7,8],[4,9]]
Output: 4
Expected: 3 
*/

/* Analysis:
Updating the parent index at the end still does not combind the parents of node 3,5,7,8 with 1,4,9.
*/

class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        // corner cases
        if (edges.empty()) return n;
        if (n < 2) return 1;
        // initialize parent table
        vector<int> parent(n, -1);
        for (int i = 0; i < edges.size(); i++) {
            int n1 = edges[i].first;
            int n2 = edges[i].second;
            // there is an edge between node n1 and n2, merge them
            // initialize the parent node
            int p1 = find(parent, n1);
            int p2 = find(parent, n2);
            // union the two nodes
            myUnion(parent, n1, n2);
        }
        // update the parent indices
        for (int i = 0; i < n; i++) {
            find(parent, i);
        }
        // count the number of "big brothers"
        unordered_set<int> components;
        for (int i = 0; i < n; i++) {
            components.insert(parent[i]);
        }
        return components.size();
    }
    
    int find(vector<int> &parent, int node) {
        if (parent[node] == -1) {
            parent[node] = node;
            return parent[node];
        }
        int p = node;
        while(p != parent[p]) p = parent[p];
        // path compression along node --> p
        int f = node;
        while (f != p) {
            int tmp = parent[f];
            parent[f] = p;
            f = tmp;
        }
        return p;
    }
    
    void myUnion(vector<int> &parent, int n1, int n2) {
        int p1 = find(parent, n1);
        int p2 = find(parent, n2);
        if (p1 != p2) {
            parent[n1] = min(p1, p2);
            parent[n2] = min(p1, p2);
        }
    }
};

/* Analysis:
The bug resides in the union function: when merging two components, my implementation is not able to change the parent for EVERY node in 
the two components. On lines 231 and 232, the parent nodes should be unioned, i.e. it should be something like parent[p1] = min(p1, p2);
parent[p2] = min(p1, p2).
*/

// Submission #4: Accepted
class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        // corner cases
        if (edges.empty()) return n;
        if (n < 2) return 1;
        // initialize parent table
        vector<int> parent(n, -1);
        int count = 0;
        for (int i = 0; i < edges.size(); i++) {
            int n1 = edges[i].first;
            int n2 = edges[i].second;
            // there is an edge between node n1 and n2, merge them
            // initialize the parent node
            int p1 = find(parent, n1);
            int p2 = find(parent, n2);
            if (p1 !=  p2) {
                // union the two nodes
                myUnion(parent, n1, n2);
                count++;
            }
        }
        return n - count;
    }
    
    int find(vector<int> &parent, int node) {
        if (parent[node] == -1) {
            parent[node] = node;
            return parent[node];
        }
        int p = node;
        while(p != parent[p]) p = parent[p];
        // path compression along node --> p
        int f = node;
        while (f != p) {
            int tmp = parent[f];
            parent[f] = p;
            f = tmp;
        }
        return p;
    }
    
    void myUnion(vector<int> &parent, int n1, int n2) {
        int p1 = find(parent, n1);
        int p2 = find(parent, n2);
        if (p1 != p2) {
            parent[p1] = min(p1, p2);
            parent[p2] = min(p1, p2);
        }
    }
};

// Submission #5: A more compact implementation: Accepted
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


