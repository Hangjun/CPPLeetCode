/*
Find the number Weak Connected Component in the directed graph. Each node in the graph contains a label and a list of its neighbors. (a connected set of a directed graph is a subgraph in which any two vertices are connected by direct edge path.) 

Example: given graph:
\begin{verbatim}
A----->B  C
 \     |  | 
  \    |  |
   \   |  |
    \  v  v
     ->D  E <- F
\end{verbatim}
Return \verb+{A,B,D}, {C,E,F}+. Since there are two connected component which are \verb+{A,B,D}+ and \verb+{C,E,F}+

\textbf{Note}: Sort the element in the set in increasing order.
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
     * @param nodes a array of directed graph node
     * @return a connected set of a directed graph
     */
    vector<vector<int>> connectedSet2(vector<DirectedGraphNode *>& nodes) {
        vector<vector<int>> res;
        if (nodes.empty())  return res;
        unordered_map<DirectedGraphNode *, DirectedGraphNode *> parent;
        for (int i = 0; i < nodes.size(); i++) {
            DirectedGraphNode *t = nodes[i];
            DirectedGraphNode *pt = find(parent, t);
            for (int j = 0; j < (t->neighbors).size(); j++) {
                DirectedGraphNode *nt = (t->neighbors)[j];
                unite(parent, t, nt);
            }
        }
        // post-processing to get the components
    	unordered_map<DirectedGraphNode *, vector<int>> components;
    	for (int i = 0; i < nodes.size(); i++) {
        	DirectedGraphNode *p = find(parent, nodes[i]);
        	components[p].push_back(nodes[i]->label);
    	}
    	for (auto it = components.begin(); it != components.end(); it++) {
        	vector<int> tmp = it->second;
        	sort(tmp.begin(), tmp.end());
        	res.push_back(tmp);
    	}
    	return res;
    }
    
    DirectedGraphNode *find (unordered_map<DirectedGraphNode *, DirectedGraphNode *> &parent, DirectedGraphNode *n) {
        if (parent.find(n) == parent.end()) {
        	parent[n] = n;
        	return parent[n];
    	}
    	DirectedGraphNode *p = n;
    	while (p != parent[p]) p = parent[p];
    	// path compression along n --> p
    	DirectedGraphNode *f = p;
    	while (f != p) {
        	DirectedGraphNode *tmp = parent[f];
        	parent[f] = p;
        	f = tmp;
    	}
    	return parent[n];
    }
    
    void unite (unordered_map<DirectedGraphNode *, DirectedGraphNode *> &parent, DirectedGraphNode *t, DirectedGraphNode *nt) {
        DirectedGraphNode *pt = find(parent, t);
        DirectedGraphNode *pnt = find(parent, nt);
        if (pt != pnt) {
            parent[pt] = (pt->label > pnt->label) ? pnt : pt;
            parent[pnt] = (pt->label > pnt->label) ? pnt : pt;
        }
    }
};
