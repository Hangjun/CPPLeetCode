/*
Dijkstra's algorithm for computing single source shortest paths in a directed graph with non-negative weights.
*/

/* Analysis:
With a binary heap data structure, Dijkstra's algorithms runs in O(VlogE) time, where V = number of vertices, E = number of edges.
*/

class Graph {
private:
    int V; // number of nodes
    vector<vector<int>> adj; // adjacency matrix
    vector<int> parent; // parent node for tracing back shortest paths
    vector<int> dist; // shortest path estimates
    void initialize_single_source(int s);
    void relax(int u, int v, vector<vector<int>> &adj, Heap<pair<int, int>>& minHeap);
    
public:
    Graph(int _V);
    void addEdge(int u, int v, int w);
    void dijkstra(int s);
};

Graph::Graph(int _V) {
    V = _V;
    adj.resize(V);
    for (int i = 0; i < V; i++) {
        adj[i].resize(V);
    }
    parent.resize(V);
    dist.resize(V);
}

void Graph::addEdge(int u, int v, int w) {
    adj[u][v] = w;
}

void Graph::dijkstra(int s) {
    unordered_set<int> explored;
    initialize_single_source(s);
    Heap<pair<int, int>> minHeap (false); // the heap APIs are not complete
    for (int i = 0; i < V; i++) {
        minHeap.push(make_pair<i, dist[i]>);
    }
    
    while (!minHeap.empty()) {
        int u = minHeap.pop().first;
        explored.insert(u);
        for (int v = 0; v < V; v++) {
            if (adj[u][v] != 0) {
                relax(u, v, adj, minHeap);
            }
        }
    }
}

void Graph::initialize_single_source(int s) {
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[s] = 0;
}

void Graph::relax(int u, int v, vector<vector<int>> &adj, Heap<pair<int, int>>& minHeap) {
    if (dist[v] > dist[u] + adj[u][v]) {
        /* This part can also be improved by a single heap operation: decreaseKey */
        miHeap.delete(v);
        dist[v] = dist[u] + adj[u][v];
        v.push(make_pair(v, dist[v]));
        parent[v] = u;
    }
}

