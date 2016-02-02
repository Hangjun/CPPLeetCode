/*
A biconnected component (also known as a block or 2-connected component) is a maximal biconnected subgraph. Given a connected undirected 
graph, it has a single connected components, but it may have multiple biconnected components. 

Given a connected undirected graph, compute its biconnected components.
*/


/* Analysis:
This problem builds upon the problem where we need to compute all the articulation points. 

References:
1. http://www.cs.umd.edu/class/fall2005/cmsc451/bicon.pdf
2. http://www.geeksforgeeks.org/biconnected-components/
*/


#include <iostream>
#include <unordered_set>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

class Edge {
public:
    int u;
    int v;
    Edge(int _u = -1, int _v = -1) {
        u = _u;
        v = _v;
    }
};

class Graph {
private:
    int V; // number of vertices
    int E; // number of edges
    unordered_set<int> *adj; // adjacency list of the graph
    void computeBCCDFS(int u, vector<bool> &visited, vector<int> &dfs, vector<int> &low, vector<int> &parent, stack<Edge> &st, int &t, vector<vector<Edge>> &res);
    
public:
    Graph(int _V) {
        V = _V;
        E = 0;
        adj = new unordered_set<int>[V];
    }
    void addEdge(int a, int b);
    vector<vector<Edge>> computeBCC();
};

void Graph::addEdge(int a, int b) {
    adj[a].insert(b);
    E++;
}

vector<vector<Edge>> Graph::computeBCC() {
    vector<bool> visited(V, false);
    vector<int> dfs(V, 0); // first discovered time
    vector<int> low(V, INT_MAX); // low point
    vector<int> parent(V, -1);
    stack<Edge> st;
    
    int t = 0; // global variable recording the time at which vertices are discovered
    vector<vector<Edge>> res;
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            computeBCCDFS(i, visited, dfs, low, parent, st, t, res);
        }
        if (!st.empty()) {
            vector<Edge> remain;
            while (!st.empty()) {
                remain.push_back(st.top());
                st.pop();
            }
            res.push_back(remain);
        }
    }
    return res;
}

void Graph::computeBCCDFS(int u, vector<bool> &visited, vector<int> &dfs, vector<int> &low, vector<int> &parent, stack<Edge> &st, int &t, vector<vector<Edge>> &res) {
    visited[u] = true;
    dfs[u] = low[u] = ++t;
    int children = 0;
    for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = *it;
        if (!visited[v]) { // (u, v) is a tree edge
            parent[v] = u;
            children++;
            st.push(Edge(u, v));
            computeBCCDFS(v, visited, dfs, low, parent, st, t, res);
            low[u] = min(low[u], low[v]);
            
            // if u is a vertex cut, pop all stored edges up until (u, v) -> it is a BCC
            if (parent[u] == -1 && children > 1 || parent[u] != -1 && low[v] >= dfs[u]) {
                vector<Edge> curBCC;
                Edge e;
                do {
                    e = st.top();
                    curBCC.push_back(e);
                    st.pop();
                } while (e.u != u || e.v != v);
                res.push_back(curBCC);
            }
        } else if (v != parent[u] && dfs[v] < dfs[u]) {
        	// (u, v) is a back edge from u to its ancestor v
        	// if dfs[v] > dfs[u], then we have already visited the back edge (v, u) previously (technically a forward edge) but we 
        	// cannot distinguish back edge and forward in undirected graphs
            low[u] = min(low[u], dfs[v]);
            st.push(Edge(u, v));
        }
    }
}

int main() {
	Graph g(12);
    g.addEdge(0,1);g.addEdge(1,0);
    g.addEdge(1,2);g.addEdge(2,1);
    g.addEdge(1,3);g.addEdge(3,1);
    g.addEdge(2,3);g.addEdge(3,2);
    g.addEdge(2,4);g.addEdge(4,2);
    g.addEdge(3,4);g.addEdge(4,3);
    g.addEdge(1,5);g.addEdge(5,1);
    g.addEdge(0,6);g.addEdge(6,0);
    g.addEdge(5,6);g.addEdge(6,5);
    g.addEdge(5,7);g.addEdge(7,5);
    g.addEdge(5,8);g.addEdge(8,5);
    g.addEdge(7,8);g.addEdge(8,7);
    g.addEdge(8,9);g.addEdge(9,8);
    g.addEdge(10,11);g.addEdge(11,10);
    vector<vector<Edge>> BCC;
    BCC = g.computeBCC();
	return 0;
}


/* Analysis:
On line 107, we added the dfs[v] < dfs[u] condition to reduce the redundancy: if dfs[v] > dfs[u], then we have already visited the back 
edge (v, u) earlier. To help understand the entire dfs[] low[] computation, consider running the above algorithm on the graph given in 
the main function. Here is how the algorithm runs:

begin DFS: dfs[0] = 1, low[0] = 1
pushing (0, 6) into stack
begin DFS: dfs[6] = 2, low[6] = 2
pushing (6, 5) into stack
begin DFS: dfs[5] = 3, low[5] = 3
pushing (5, 8) into stack
begin DFS: dfs[8] = 4, low[8] = 4
pushing (8, 9) into stack
begin DFS: dfs[9] = 5, low[9] = 5
end DFS: dfs[9] = 5, low[9] = 5
u = 8 is a vertex cut.
popping (8, 9) out of stack, into curBCC
pushing (8, 7) into stack
begin DFS: dfs[7] = 6, low[7] = 6
(7,5) is a back edge
pushing (7,5) into stack
end DFS: dfs[7] = 6, low[7] = 3
end DFS: dfs[8] = 4, low[8] = 3
u = 5 is a vertex cut.
popping (7, 5) out of stack, into curBCC
popping (8, 7) out of stack, into curBCC
popping (5, 8) out of stack, into curBCC
pushing (5, 1) into stack
begin DFS: dfs[1] = 7, low[1] = 7
pushing (1, 3) into stack
begin DFS: dfs[3] = 8, low[3] = 8
pushing (3, 4) into stack
begin DFS: dfs[4] = 9, low[4] = 9
pushing (4, 2) into stack
begin DFS: dfs[2] = 10, low[2] = 10
(2,3) is a back edge
pushing (2,3) into stack
(2,1) is a back edge
pushing (2,1) into stack
end DFS: dfs[2] = 10, low[2] = 7
end DFS: dfs[4] = 9, low[4] = 7
end DFS: dfs[3] = 8, low[3] = 7
u = 1 is a vertex cut.
popping (2, 1) out of stack, into curBCC
popping (2, 3) out of stack, into curBCC
popping (4, 2) out of stack, into curBCC
popping (3, 4) out of stack, into curBCC
popping (1, 3) out of stack, into curBCC
(1,0) is a back edge
pushing (1,0) into stack
end DFS: dfs[1] = 7, low[1] = 1
end DFS: dfs[5] = 3, low[5] = 1
end DFS: dfs[6] = 2, low[6] = 1
end DFS: dfs[0] = 1, low[0] = 1
popping remaining edge (1, 0) out of stack
popping remaining edge (5, 1) out of stack
popping remaining edge (6, 5) out of stack
popping remaining edge (0, 6) out of stack
begin DFS: dfs[10] = 11, low[10] = 11
pushing (10, 11) into stack
begin DFS: dfs[11] = 12, low[11] = 12
end DFS: dfs[11] = 12, low[11] = 12
end DFS: dfs[10] = 11, low[10] = 11
popping remaining edge (10, 11) out of stack
*/
