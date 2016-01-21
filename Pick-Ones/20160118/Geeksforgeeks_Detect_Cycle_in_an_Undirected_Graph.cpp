/*
Given an undirected graph, test if it contains a cycle.
*/

// Submission #1: Failed

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
        if (visited.find(nb) == visited.end() && isCyclicDFS(nodes, nb, visited, curNode)) {
            return true;
        } 
        if (nb != parent) {
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
Lines 18-25 have a fatal logical bug that is not easily detected, since we could actually get away with that in the case of directed graphs. 
In that case instead of using parent node, we use inStack array to keep track of active nodes along a DFS recursion stack. 

Complete analysis see https://github.com/Hangjun/MyLeetCode/blob/master/Building_Blocks/Cycle_Detection_in_Undirected_Graph.cpp.
*/

// Submission #2: Accepted:
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
Compare lines 64-70 with lines 18-25 above. These are the only changes. 
*/

