/*
Given a directed graph, compute its strongly connected components (a.k.a. SCC) in time linear in the number of vertices and edges. 
*/

/* Analysis:
We use Kosaraju's algorithm to compute the SCCs. The algorithm uses two DFS, and runs in linear time (in the number of vertices and edges).
*/

#include <iostream>
#include <unordered_set>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;
 
// A directed graph using adjacency list representation
class Graph
{
    int V;    // No. of vertices in graph
    unordered_set<int> *adj; // Pointer to an array containing adjacency lists
    void backwardDFS(vector<unordered_set<int>> &adj_rev, int curNode, vector<bool> &visited, vector<int> &timeStamp, int &t);
    void forwardDFS(int curNode, vector<bool> &visited, vector<int> &component);
    
public:
    Graph(int V);   // Constructor
    void addEdge(int u, int v);
    vector<vector<int>> computeSCC();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new unordered_set<int>[V];
}
 
void Graph::addEdge(int u, int v)
{
    adj[u].insert(v); // Add v to u’s adjacency list.
}

vector<vector<int>> Graph::computeSCC() {
    // construct reverse graph adjacency list
    vector<unordered_set<int>> adj_rev(V);
    for (int i = 0; i < V; i++) {
        for (auto it = adj[i].begin(); it != adj[i].end(); it++) {
            adj_rev[*it].insert(i);
        }
    }
    vector<int> timeStamp(V);
    vector<bool> visited(V, false);
    int t = 0;
    // DFS on the reverse graph to compute the finishing times
    for (int i = V-1; i >= 0; i--) {
        if (!visited[i]) {
            backwardDFS(adj_rev, i, visited, timeStamp, t);
        }
    }
    // mem_set(visited, false, sizeof(bool) * V);
    for (int i = 0; i < V; i++) {visited[i] = false;}
    vector<vector<int>> res;
    // DFS on the original graph in the order of decreasing finishing times
    for (int i = V-1; i >= 0; i--) {
        int curNode = timeStamp[i];
        if (!visited[curNode]) {
            vector<int> component;
            forwardDFS(curNode, visited, component);
            res.push_back(component);
        }
    }
    return res;
}

void Graph::backwardDFS(vector<unordered_set<int>> &adj_rev, int curNode, vector<bool> &visited, vector<int> &timeStamp, int &t) {
    visited[curNode] = true;
    for (auto it = adj_rev[curNode].begin(); it != adj_rev[curNode].end(); it++) {
        if (!visited[*it]) {
            backwardDFS(adj_rev, *it, visited, timeStamp, t);
        }
    }
    timeStamp[t++] = curNode;
    return;
}

void Graph::forwardDFS(int curNode, vector<bool> &visited, vector<int> &component) {
    // cout << "forwardDFS: curNode = " << curNode << endl;
    visited[curNode] = true;
    component.push_back(curNode);
    for (auto it = adj[curNode].begin(); it != adj[curNode].end(); it++) {
        if (!visited[*it]) {
            forwardDFS(*it, visited, component);
        }
    }
    return;
}

int main() {
	Graph g(14);
    // scc1
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 0);
	
	// scc2
	g.addEdge(4, 7);
	g.addEdge(7, 6);
	g.addEdge(5, 6);
	g.addEdge(4, 5);
	g.addEdge(6, 4);
	
	// scc3
	g.addEdge(8, 9);
	g.addEdge(9, 10);
	g.addEdge(10, 8);
	
	// scc4
	g.addEdge(11, 13);
	g.addEdge(13, 12);
	g.addEdge(12, 11);
	
	// scc1 -> scc2
	g.addEdge(0, 7);
	
	// scc1 -> scc3
	g.addEdge(2, 8);
	
	// scc2 -> scc4
	g.addEdge(6, 12);
	
	// scc3 -> scc4
	g.addEdge(9, 13);
	
	vector<vector<int>> scc = g.computeSCC();
	return 0;
}


/* Analysis:
Kosaraju's algorithm requires two passes of DFS. Can the SCC's be found using only a single DFS? The answer is yes. Tarjan’s Algorithm 
for computing SCC's of a directed graph also runs in linear time with the added bonus that we only need to traverse the graph once. 
See:
https://github.com/Hangjun/MyLeetCode/blob/master/Pick-Ones/20160201/Tarjan_Algorithm_for_Computing_SCC_in_Directed_Graph.cpp
*/
