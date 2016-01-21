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

