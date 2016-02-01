/*
Given a connected undirected graph, a cut vertex (a.k.a. articulation point) is a vertex whose removal disconnects the graph. 

Compute all cut vertices in a connected undirected graph in linear time (in the size of the adjacency lists).
*/

/* Analysis:
This is a difficult problem. See the following references for details (listed in decreasing order of helpfulness).
1. http://pisces.ck.tp.edu.tw/~peng/index.php?action=showfile&file=fb1f19a9be617037cb419c5d454b184bead47e243
2. http://www.cs.cmu.edu/afs/cs/academic/class/15451-s14/LectureNotes/lecture11.pdf
3. https://en.wikipedia.org/wiki/Biconnected_component
4. http://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
*/

#include<iostream>
#include <vector>
#include <unordered_set>
#include <climits>

using namespace std;
 
class Graph
{
    int V;    // No. of vertices
    unordered_set<int> *adj;    // A dynamic array of adjacency lists
    void computeCutVertexDFS(int u, vector<bool> &visited, vector<int> &dfs, vector<int> &low, vector<int> &parent, vector<bool> &cv, int &t);

public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    vector<int> computeCutVertex (); // compute cut vertices of the graph
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new unordered_set<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].insert(w);
    adj[w].insert(v);  // Note: the graph is undirected
}

vector<int> Graph::computeCutVertex () {
    vector<int> res;
    vector<bool> visited(V, false);
    vector<int> dfs(V, 0);
    vector<int> low(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> cv(V, false);
    int t = 0; // global variable to keep track of dfs depth (i.e. discover time)
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            computeCutVertexDFS(i, visited, dfs, low, parent, cv, t);
        }
        // at this point we know whether node is a cut vertex for sure
        if (cv[i]) {
            cout << i << " ";
            res.push_back(i);
        }
    }
    
    return res;
}

void Graph::computeCutVertexDFS(int u, vector<bool> &visited, vector<int> &dfs, vector<int> &low, vector<int> &parent, vector<bool> &cv, int &t) {
    visited[u] = true;
    t++;
    dfs[u] = t;
    low[u] = t;
    int children = 0;
    for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = *it;
        if (!visited[v]) {
            parent[v] = u;
            children++;
            computeCutVertexDFS(v, visited, dfs, low, parent, cv, t);
            
            // (u, v) is a tree edge: check if the subtree rooted with v has a smaller low value than low[u]
            low[u] = min(low[u], low[v]);
            
            if (parent[u] == -1) { // if u is root
                cv[u] = (children > 1);
            } else if (low[u] >= dfs[u]) {
                cv[u] = true;
            }
        } else if (v != parent[u]) {
            // (u, v) is a back edge:  check if we can get a lower depth via the back edge (u, v)
            low[u] = min(low[u], dfs[v]);
        }
    }
}

int main() {
	// Create graphs given in above diagrams
    cout << "\nArticulation points in first graph \n";
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.computeCutVertex();
 
    cout << "\nArticulation points in second graph \n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.computeCutVertex();
 
    cout << "\nArticulation points in third graph \n";
    Graph g3(7);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(1, 6);
    g3.addEdge(3, 5);
    g3.addEdge(4, 5);
    g3.computeCutVertex();
	return 0;
}

