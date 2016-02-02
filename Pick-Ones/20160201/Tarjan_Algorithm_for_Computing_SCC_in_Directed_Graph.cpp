/*
Given a weakly connected directed graph, we have previously discussed Kosaraju’s algorithm for computing its strongly connected 
components. However, that algorithm requires two runs of DFS. Tarjan's algorithm makes use of the notion of a low point of any node, and 
only requires a single DFS traversal.
*/

/* Wikipedia:
The nodes are placed on a stack in the order in which they are visited. When the depth-first search recursively explores a node v and 
its descendants, those nodes are not all necessarily popped from the stack when this recursive call returns. The crucial invariant 
property is that a node remains on the stack after exploration if and only if it has a path to some node earlier on the stack.

At the end of the call that explores v and its descendants, we know whether v itself has a path to any node earlier on the stack. 
If so, the call returns, leaving v on the stack to preserve the invariant. If not, then v must be the root of its strongly connected 
component, which consists of v together with any later nodes on the stack (such nodes all have paths back to v but not to any earlier 
node, because if they had paths to earlier nodes then v would also have paths to earlier nodes which is false ). This entire component 
is then popped from the stack and returned, again preserving the invariant.
*/

#include <iostream>
#include <unordered_set>
#include <vector>
#include <stack>

using namespace std;

class Graph {
private:
    int V; // number of vertices
    unordered_set<int> *adj; // adjacency list
    void computeSCCDFS(int u, vector<bool> &visited, vector<bool> &inStack, vector<int> &dfs, vector<int> &low, stack<int> &st, int &t, vector<vector<int>> &res);

public:
    Graph(int _V);
    void addEdge(int u, int v);
    
    vector<vector<int>> computeSCC();
};

Graph::Graph(int _V) {
    V = _V;
    adj = new unordered_set<int>[V];
}

void Graph::addEdge(int u, int v) {
    adj[u].insert(v);
}

vector<vector<int>> Graph::computeSCC(){
    vector<vector<int>> res;
    vector<bool> visited(V, false);
    vector<bool> inStack(V, false);
    vector<int> dfs(V, 0);
    vector<int> low(V, 0);
    stack<int> st;
    int t = 0;
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            computeSCCDFS(i, visited, inStack, dfs, low, st, t, res);
        }
    }
    
    return res;
}

void Graph::computeSCCDFS(int u, vector<bool> &visited, vector<bool> &inStack, vector<int> &dfs, vector<int> &low, stack<int> &st, int &t, vector<vector<int>> &res) {
    visited[u] = true;
    inStack[u] = true;
    dfs[u] = low[u] = ++t;
    st.push(u);
    
    for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
        int v = *it;
        if (!visited[v]) {
            computeSCCDFS(v, visited, inStack, dfs, low, st, t, res);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], dfs[v]);
        }
    }
    
    if (low[u] == dfs[u]) { // u is the head node of its SCC
        // pop stack up to (and including) u
        vector<int> curSCC;
        int temp;
        do {
            temp = st.top();
            st.pop();
            // Caution: need to reset inStack value for ALL nodes poped, not just the head u 
            inStack[temp] = false;
            curSCC.push_back(temp);
        } while (temp != u);
        res.push_back(curSCC);
    }
}


int main() {
	cout << "\nSCCs in first graph \n";
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.computeSCC();
 
    cout << "\nSCCs in second graph \n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.computeSCC();
 
    cout << "\nSCCs in third graph \n";
    Graph g3(7);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(1, 6);
    g3.addEdge(3, 5);
    g3.addEdge(4, 5);
    g3.computeSCC();
 
    cout << "\nSCCs in fourth graph \n";
    Graph g4(11);
    g4.addEdge(0,1);g4.addEdge(0,3);
    g4.addEdge(1,2);g4.addEdge(1,4);
    g4.addEdge(2,0);g4.addEdge(2,6);
    g4.addEdge(3,2);
    g4.addEdge(4,5);g4.addEdge(4,6);
    g4.addEdge(5,6);g4.addEdge(5,7);g4.addEdge(5,8);g4.addEdge(5,9);
    g4.addEdge(6,4);
    g4.addEdge(7,9);
    g4.addEdge(8,9);
    g4.addEdge(9,8);
    g4.computeSCC();
 
    cout << "\nSCCs in fifth graph \n";
    Graph g5(5);
    g5.addEdge(0,1);
    g5.addEdge(1,2);
    g5.addEdge(2,3);
    g5.addEdge(2,4);
    g5.addEdge(3,0);
    g5.addEdge(4,2);
    g5.computeSCC();
	return 0;
}
