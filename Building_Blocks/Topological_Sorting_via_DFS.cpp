struct DirectedGraphNode {
    int label;
    vector<DirectedGraphNode *> neighbors;
    DirectedGraphNode(int x) : label(x) {};
};

void topSortDFS(vector<DirectedGraphNode *> &nodes, DirectedGraphNode *curNode,
stack<DirectedGraphNode *> &s, unordered_set<DirectedGraphNode *> &visited) {
    visited.insert(curNode);
    for (int i = 0; i < curNode->neighbors.size(); i++) {
        DirectedGraphNode *nb = curNode->neighbors[i];
        if (visited.find(nb) == visited.end()) {
            topSortDFS(nodes, nb, s, visited);
        }
    }
    s.push(curNode);
}

vector<DirectedGraphNode *> topSort(vector<DirectedGraphNode *> nodes) {
    vector<DirectedGraphNode *> res;
    if (nodes.empty()) return res;
    stack<DirectedGraphNode *> s;
    unordered_set<DirectedGraphNode *> visited;
    for (int i = 0; i < nodes.size(); i++) {
        if (visited.find(nodes[i]) == visited.end()) {
            topSortDFS(nodes, nodes[i], s, visited);
        }
    }
    while (!s.empty()) {
        res.push_back(s.top());
        s.pop();
    }
    return res;
}
