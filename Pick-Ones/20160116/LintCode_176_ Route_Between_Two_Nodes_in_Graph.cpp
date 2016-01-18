/*
Given a directed graph, design an algorithm to find out whether there is a route between two nodes.

Example

Given graph:

A----->B----->C
 \     |
  \    |
   \   |
    \  v
     ->D----->E

for s = B and t = E, return true

for s = D and t = C, return false
*/

// Submission #1: Accepted
/**
 * Definition for Directed graph.
 * struct DirectedGraphNode {
 *     int label;
 *     vector<DirectedGraphNode *> neighbors;
 *     DirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    /**
     * @param graph: A list of Directed graph node
     * @param s: the starting Directed graph node
     * @param t: the terminal Directed graph node
     * @return: a boolean value
     */
    bool hasRoute(vector<DirectedGraphNode*> graph,
                  DirectedGraphNode* s, DirectedGraphNode* t) {
        if (graph.empty()) return false;
        // start from node s, BFS on its neighbors
        unordered_set<DirectedGraphNode *> visited;
        visited.insert(s);
        queue<DirectedGraphNode *> q;
        q.push(s);
        while (!q.empty()) {
            DirectedGraphNode *curNode = q.front();
            q.pop();
            if (curNode == t) return true;
            for (int i = 0; i < curNode->neighbors.size(); i++) {
                DirectedGraphNode *nb = curNode->neighbors[i];
                if (visited.find(nb) == visited.end()) {
                    visited.insert(nb);
                    q.push(nb);
                }
            }
        }
        return false;
    }
};

