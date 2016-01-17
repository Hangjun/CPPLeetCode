/*
 Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.

OJ's undirected graph serialization:

Nodes are labeled uniquely.
We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.

As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

    First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
    Second node is labeled as 1. Connect node 1 to node 2.
    Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.

Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/
*/

// Submission #1: Failed: Time Limit Exceeded  Last executed input: {-1} 
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL) return NULL;
        unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> ht;
        ht[node] = new UndirectedGraphNode(node->label);
        queue<UndirectedGraphNode *> q;
        q.push(node);
        
        while (!q.empty()) {
            // loop invariant: q.front() has already been cloned
            UndirectedGraphNode *curNode = q.front();
            UndirectedGraphNode *curNodeCopy = ht[curNode];
            // clone curNode->neighbors
            for (int i = 0; i < curNode->neighbors.size(); i++) {
                UndirectedGraphNode *nb = curNode->neighbors[i];
                if (ht.find(nb) != ht.end()) {
                    curNodeCopy->neighbors.push_back(ht[nb]);
                } else {
                    UndirectedGraphNode *tmp = new UndirectedGraphNode(nb->label);
                    curNodeCopy->neighbors.push_back(tmp);
                    ht[nb] = tmp;
                    q.push(nb);
                }
            }
        }
        
        return ht[node];
    }
};

// The reason is that on line 47, we didn't pop curNode

// submission #2: Accepted
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL) return NULL;
        unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> ht;
        ht[node] = new UndirectedGraphNode(node->label);
        queue<UndirectedGraphNode *> q;
        q.push(node);
        
        while (!q.empty()) {
            // loop invariant: q.front() has already been cloned
            UndirectedGraphNode *curNode = q.front();
            q.pop();
            UndirectedGraphNode *curNodeCopy = ht[curNode];
            // clone curNode->neighbors
            for (int i = 0; i < curNode->neighbors.size(); i++) {
                UndirectedGraphNode *nb = curNode->neighbors[i];
                if (ht.find(nb) != ht.end()) {
                    curNodeCopy->neighbors.push_back(ht[nb]);
                } else {
                    UndirectedGraphNode *tmp = new UndirectedGraphNode(nb->label);
                    curNodeCopy->neighbors.push_back(tmp);
                    ht[nb] = tmp;
                    q.push(nb);
                }
            }
        }
        
        return ht[node];
    }
};

/*
Key logic: every node in the queue satisfies two properties:
1. it has been cloned already;
2. its neighbors either have not been cloned, or the neighboring nodes have been cloned, but this particular neighboring information has 
not been cloned over.
Every node will be pushed onto the queue exactly once. Therefore, given the front node of the queue a, and b a neighbor node of a. Let
a' = ht[a]. If b' = ht[b] exist, then it must be the case that a' does NOT recoginize b' as its neighbor yet since otherwise a appears in 
queue twice. This justifies line 96. Moreover, we cannot push b onto the queue since ht[b] exists means that it has already been on the
queue already (i.e. b must have gone through line 101 previously. It may still in the queue has been popped out already).
*/
