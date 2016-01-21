/*
Given an undirected graph, test if it contains a cycle.
*/

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

bool isCyclicDFS(vector<UndirectedGraphNode *> &nodes, UndirectedGraphNode *curNode, unordered_set<UndirectedGraphNode *> &visited, UndirectedGraphNode *parent)
 {
    visited.insert(curNode);
    for (int i = 0; i < curNode->neighbors.size(); i++) {
        UndirectedGraphNode *nb = curNode->neighbors[i];
        if (visited.find(nb) == visited.end()) {
            if (isCyclicDFS(nodes, nb, visited, curNode));
        } else if (nb != parent) {
            // if nb has been visited, then for curNode-...-nb not to be a back edge, 
            // it is if and only if that nb == parent
            return true;
        }
    }
    // no cycle is found eminating from curNode
    return false;
 }
bool isCyclic(vector<UndirectedGraphNode *> &nodes) {
    if (nodes.empty()) return false;
    unordered_set<UndirectedGraphNode *> visited;
    UndirectedGraphNode *parent = NULL;
    for (int i = 0; i < nodes.size(); i++) {
        if (visited.find(nodes[i]) == visited.end()) {
            if (isCyclicDFS(nodes, nodes[i], visited, parent)) {
                // a cycle is found eminating from nodes[i]
                return true;
            }
        }
    }
    return false;
}

/* Analysis:
1. For undirected graph, we do not need to keep track of which nodes are in stack. In fact, we can't. Suppose A-B is an edge, and we start 
the dfs call on node A. It sees B as an unvisited node, and recurse onto B. B sees that its only neighbor A has been visited, thus if we 
use the previous inStack trick, it's going to report that we have a cycle, which is wrong. 

The upshot is that, the very nature that an undirected edge can go both ways prohibits the use of a stack, which is directional in nature. 
Once we run into a node that has been visited already, we only need to check whether it is same node as the parent node of the current node. 
Draw a (undirected) cycle out and convince yourself that this is indeed the case. 

2. The logic on lines 16-21 above is critical. If a node is unvisited, we need to recursively run dfs on it. In this case, even if the we do 
find a cycle eminating from that node, we should NOT test whether it equals to its parent node any more. Had we written:
if (visited.find(*it) && dfs(nodes, *it, visited, parent)) {
    return true;
} else if (*it != parent) {
    return true;
}
Even if *it is not visited, it will still be recursed on. And if the dfs returns false (no cycle is found), the if-condition fails, and thus 
the else-if condition will get executed. This will lead to a logical mistake: it a node is not visited, we shouldn't check whether it is the 
parent node. It is because of the && that we have to evaluate the entire expression to get a conclusion. 
*/

// Another graph representation

// A C++ Program to detect cycle in an undirected graph
// A C++ Program to detect cycle in an undirected graph
#include<iostream>
#include <list>
#include <limits.h>
using namespace std;
 
// Class for an undirected graph
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
    bool isCyclicUtil(int v, bool visited[], int parent);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph
    bool isCyclic();   // returns true if there is a cycle
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v); // Add v to w’s list.
}
 
// A recursive function that uses visited[] and parent to detect
// cycle in subgraph reachable from vertex v.
bool Graph::isCyclicUtil(int v, bool visited[], int parent)
{
    // Mark the current node as visited
    visited[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        // If an adjacent is not visited, then recur for that adjacent
        if (!visited[*i])
        {
           if (isCyclicUtil(*i, visited, v))
              return true;
        }
 
        // If an adjacent is visited and not parent of current vertex,
        // then there is a cycle.
        else if (*i != parent)
           return true;
    }
    return false;
}
 
// Returns true if the graph contains a cycle, else false.
bool Graph::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for (int u = 0; u < V; u++)
        if (!visited[u]) // Don't recur for u if it is already visited
          if (isCyclicUtil(u, visited, -1))
             return true;
 
    return false;
}
 
// Driver program to test above functions
int main()
{
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 0);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.isCyclic()? cout << "Graph contains cycle\n":
                   cout << "Graph doesn't contain cycle\n";
 
    Graph g2(3);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.isCyclic()? cout << "Graph contains cycle\n":
                   cout << "Graph doesn't contain cycle\n";
 
    return 0;
}

