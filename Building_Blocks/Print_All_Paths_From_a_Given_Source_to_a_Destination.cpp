/*
Given a directed graph, a source vertex ‘s’ and a destination vertex ‘d’, print all paths from given ‘s’ to ‘d’. 
*/

#include <iostream>
#include <list>
#include <vector>

using namespace std;
 
// A directed graph using adjacency list representation
class Graph
{
    int V;    // No. of vertices in graph
    list<int> *adj; // Pointer to an array containing adjacency lists
 
    // A recursive function used by printAllPaths()
    void printAllPathsDFS(int, int, vector<bool> &, vector<int> &, vector<vector<int>> &);
 
public:
    Graph(int V);   // Constructor
    void addEdge(int u, int v);
    void printAllPaths(int s, int d);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v); // Add v to u’s list.
}

void Graph::printAllPaths(int s, int d) {
    vector<int> curPath;
    vector<vector<int>> paths;
    vector<bool> visited(V);
    printAllPathsDFS(s, d, visited, curPath, paths);
    // display all paths
    for (int i = 0; i < paths.size(); i++) {
        vector<int> p = paths[i];
        for (int j = 0; j < p.size(); j++) {
            cout << p[j] << "  ";
        }
        cout << endl;
    }
}

void Graph::printAllPathsDFS(int curNode, int target, vector<bool> &visited, vector<int> &curPath, vector<vector<int>> &paths) {
    visited[curNode] = true;
    curPath.push_back(curNode);
    if (curNode == target) {
        paths.push_back(curPath);
    } else {
        for (auto it = adj[curNode].begin(); it != adj[curNode].end(); it++) {
            if (!visited[*it]) {
                printAllPathsDFS(*it, target, visited, curPath, paths);
            }
        }
    }
    // backtrack
    visited[curNode] = false;
    curPath.pop_back();
}

int main() {
	Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
 
    int s = 0, d = 3;
    g.printAllPaths(s, d);
	return 0;
}


/* Analysis:
We need to use the visited array to avoid running into the same node on the same DFS traversal. For instance, suppose there is an edge from 
a to b as well as from b to a. Without using the visited, array, we can bounce between a and b infinitely before making any other meaning 
progress. 
*/
