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
    cout << "begin DFS: dfs[" << u << "] = " << dfs[u] << ", low[" << u << "] = " << low[u] << endl;
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
                cout << "u = " << u << " is a vertex cut." << endl;
                vector<Edge> curBCC;
                Edge e;
                do {
                    e = st.top();
                    curBCC.push_back(e);
                    st.pop();
                } while (e.u != u || e.v != v);
                res.push_back(curBCC);
            }
        } else if (v != parent[u]) {
            cout << "(" << u << "," << v << ") is a back edge" << endl; 
            low[u] = min(low[u], dfs[v]);
            st.push(Edge(u, v));
        }
    }
    cout << "end DFS: dfs[" << u << "] = " << dfs[u] << ", low[" << u << "] = " << low[u] << endl;
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

