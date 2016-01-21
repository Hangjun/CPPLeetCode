/* 
Test whether a directed graph contains a directed edge.
*/

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


/* Analysis:
Can just use a visited vector to keep track of visited nodes, and we reset visited = false when completely finished with each dfs 
traversal, and we report a cycle as soon as we run into an already visited node? 
If we reset the value of visited before returning from each dfs call, I think the algorithm still holds (need to double check!!). The problem 
is that a node might be visited multiple times. This impacts the performance greatly. Here is the implementation with just the visited array, 
for future references.
*/

struct DirectedGraphNode {
    int label;
    vector<DirectedGraphNode *> neighbors;
    DirectedGraphNode(int x) : label(x) {};
};

bool isCyclicDFS(vector<DirectedGraphNode *> &nodes, DirectedGraphNode *curNode, unordered_set<DirectedGraphNode *> &visited) {
    visited.insert(curNode);
    for (int i = 0; i < curNode->neighbors.size(); i++) {
        DirectedGraphNode *nb = curNode->neighbors[i];
        if (visited.find(nb) == visited.end()) {
            if (isCyclicDFS(nodes, nb, visited)) {
                return true;
            }
        } else { // *it was visited: cycle found
            return true;
        }
    }
    visited.erase(curNode);
    return false;
}

bool isCyclic(vector<DirectedGraphNode *> nodes) {
    if (nodes.empty()) return false;
    unordered_set<DirectedGraphNode *> visited;
    for (int i = 0; i < nodes.size(); i++) {
        if (visited.find(nodes[i]) == visited.end()) {
            if (isCyclicDFS(nodes, nodes[i], visited)) {
                return true;
            }
        }
    }
    return false;
}
