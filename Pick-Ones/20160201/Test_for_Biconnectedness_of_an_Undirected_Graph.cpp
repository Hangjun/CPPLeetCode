/*
Given an undirected graph G, it is biconnected if the removal of any vertex does not disconnect the graph. Equivalently, there are two 
vertex-disjoint paths between any pair of vertices. Another equivalent characterization for biconnectedness is that there exists a simple 
cycle through any two vertices. Note that a biconnected graph is necessarily (also trivially) connected.

Given an undirected graph, determine if it is biconnected.
*/

/* Analysis: 
G is biconnected if it is connected and does not have any articulation point.
*/

// Submission #1: Failed.
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class UndirectedGraph {
private:
    int V; // number of vertices
    unordered_set<int> *adj;
    bool isBiconnectedDFS(int u, vector<bool> &visited, vector<int> &parent, vector<int> &dfs, vector<int> &low, int &t);

public:
    UndirectedGraph(int _V);
    void addEdge(int u, int v);
    bool isBiconnected();
};

UndirectedGraph::UndirectedGraph(int _V) {
    V = _V;
    adj = new unordered_set<int>[V];
}

void UndirectedGraph::addEdge(int u, int v) {
    adj[u].insert(v);
    adj[v].insert(u);
}

bool UndirectedGraph::isBiconnected() {
    if (V <= 1) return true;
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);
    vector<int> dfs(V, 0);
    vector<int> low(V, 0);
    int t = 0;
    int components = 0;
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (isBiconnectedDFS(i, visited, parent, dfs, low, t)) {
                return false;
            }
            components++;
        }
    }
    
    // no articulation point found, but still need to test for connectedness
    return components == 1;
}

bool UndirectedGraph::isBiconnectedDFS(int u, vector<bool> &visited, vector<int> &parent, vector<int> &dfs, vector<int> &low, int &t) {
    visited[u] = true;
    dfs[u] = low[u] = ++t;
    int children = 0;
    
    for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = *it;
        if (!visited[v]) {
            // (u, v) is a tree edge
            parent[v] = u;
            children++;
            
            isBiconnectedDFS(v, visited, parent, dfs, low, t);
            
            low[u] = min(low[u], low[v]);
            
            if (parent[u] == 1 && children > 1 || parent[u] != -1 && low[v] >= dfs[u]) {
                return true;
            }
        } else if (v != parent[u] && dfs[v] < dfs[u]) {
            // (u, v) is a back edge
            low[u] = min(low[u], dfs[v]);
        }
    }
    return false;
}

/* Analysis:
On line 76, it should be if (isBiconnectedDFS(v, visited, parent, dfs, low, t)) {return true;}. Otherwise, u would have no idea if an 
articulation point has already been found in its subtree.
*/

// Submission #2: Accepted.
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class UndirectedGraph {
private:
    int V; // number of vertices
    unordered_set<int> *adj;
    bool isBiconnectedDFS(int u, vector<bool> &visited, vector<int> &parent, vector<int> &dfs, vector<int> &low, int &t);

public:
    UndirectedGraph(int _V);
    void addEdge(int u, int v);
    bool isBiconnected();
};

UndirectedGraph::UndirectedGraph(int _V) {
    V = _V;
    adj = new unordered_set<int>[V];
}

void UndirectedGraph::addEdge(int u, int v) {
    adj[u].insert(v);
    adj[v].insert(u);
}

bool UndirectedGraph::isBiconnected() {
    if (V <= 1) return true;
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);
    vector<int> dfs(V, 0);
    vector<int> low(V, 0);
    int t = 0;
    int components = 0;
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (isBiconnectedDFS(i, visited, parent, dfs, low, t)) {
                return false;
            }
            components++;
        }
    }
    
    // no articulation point found, but still need to test for connectedness
    return components == 1;
}

bool UndirectedGraph::isBiconnectedDFS(int u, vector<bool> &visited, vector<int> &parent, vector<int> &dfs, vector<int> &low, int &t) {
    visited[u] = true;
    dfs[u] = low[u] = ++t;
    int children = 0;
    
    for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = *it;
        if (!visited[v]) {
            // (u, v) is a tree edge
            parent[v] = u;
            children++;
            
            if (isBiconnectedDFS(v, visited, parent, dfs, low, t)) {
                return true;
            }
            
            low[u] = min(low[u], low[v]);
            
            if (parent[u] == 1 && children > 1 || parent[u] != -1 && low[v] >= dfs[u]) {
                return true;
            }
        } else if (v != parent[u] && dfs[v] < dfs[u]) {
            // (u, v) is a back edge
            low[u] = min(low[u], dfs[v]);
        }
    }
    return false;
}

int main() {
    // test cases
    UndirectedGraph g1(2);
    g1.addEdge(0, 1);
    g1.isBiconnected()? cout << "Yes\n" : cout << "No\n";
 
    UndirectedGraph g2(5);
    g2.addEdge(1, 0);
    g2.addEdge(0, 2);
    g2.addEdge(2, 1);
    g2.addEdge(0, 3);
    g2.addEdge(3, 4);
    g2.addEdge(2, 4);
    g2.isBiconnected()? cout << "Yes\n" : cout << "No\n";
 
    UndirectedGraph g3(3);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.isBiconnected()? cout << "Yes\n" : cout << "No\n";
 
    UndirectedGraph g4(5);
    g4.addEdge(1, 0);
    g4.addEdge(0, 2);
    g4.addEdge(2, 1);
    g4.addEdge(0, 3);
    g4.addEdge(3, 4);
    g4.isBiconnected()? cout << "Yes\n" : cout << "No\n";
 
    UndirectedGraph g5(3);
    g5.addEdge(0, 1);
    g5.addEdge(1, 2);
    g5.addEdge(2, 0);
    g5.isBiconnected()? cout << "Yes\n" : cout << "No\n";

	return 0;
}

/* Output:
Yes
Yes
No
No
Yes
*/



