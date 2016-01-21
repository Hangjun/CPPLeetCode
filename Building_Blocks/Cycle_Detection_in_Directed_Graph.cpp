#include<iostream>
#include <list>
#include <vector>
#include <limits.h>
 
using namespace std;
 
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
    bool isCyclicDFS(int v, vector<bool> &visited, vector<bool> &inStack);  // used by isCyclic()
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph
    bool isCyclic();    // returns true if there is a cycle in this graph
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
// This function is a variation of DFSUytil() in http://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclicDFS(int v, vector<bool> &visited, vector<bool> &inStack)
{
    // Mark the current node as visited and part of recursion stack
    visited[v] = true;
    inStack[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i]) {
            if (isCyclicDFS(*i, visited, inStack)) {
                return true;
            }
        } else if (inStack[*i]) { // if *i has been visited, check if it's currently on stack
            return true;
        }
    }
    inStack[v] = false;  // remove the vertex from recursion stack
    return false;
}
 
// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() in http://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    vector<bool> visited(V);
    vector<bool> inStack(V);

    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        inStack[i] = false;
    }
 
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for(int i = 0; i < V; i++)
        if (!visited[i]) {
            if (isCyclicDFS(i, visited, inStack)) {
                return true;
            }
        }
 
    return false;
}

int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    if(g.isCyclic())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";
    return 0;
}


// another graph represetation
struct DirectedGraphNode {
    int label;
    vector<DirectedGraphNode *> neighbors;
    DirectedGraphNode(int x) : label(x) {};
};

bool isCyclicDFS(vector<DirectedGraphNode *> &nodes, DirectedGraphNode *curNode,
unordered_set<DirectedGraphNode *> &visited, unordered_set<DirectedGraphNode *> &inStack) {
    visited.insert(curNode);
    inStack.insert(curNode);
    for (int i = 0; i < curNode->neighbors.size(); i++) {
        DirectedGraphNode *nb = curNode->neighbors[i];
        if (visited.find(nb) == visited.end()) { {
            if (isCyclicDFS(nodes, nb, visited, inStack)) {
                return true;
            }
        } else if (inStack.find(nb) != inStack.end()) {
            return true;
        }
    }
    inStack.erase(curNode);
    return false;
}

bool isCyclic(vector<DirectedGraphNode *> nodes) {
    if (nodes.empty()) return false;
    unordered_set<DirectedGraphNode *> visited;
    unordered_set<DirectedGraphNode *> inStack;
    for (int i = 0; i < nodes.size(); i++) {
        if (visited.find(nodes[i]) == visited.end()) {
            if (isCyclicDFS(nodes, nodes[i], visited, inStack)) {
                return true;
            }
        }
    }
    return false;
}
