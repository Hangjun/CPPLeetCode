/*
Given an Undirected simple graph, We need to find how many triangles it can have.
*/

/* Analysis:
The bruteforce solution is to check all triples (i,j,k) of the graph nodes, and if there is an between from i to j, and j to k and k to i, 
we increment a counter. We need to divied the result by 6 since the we are triple counted the nodes in a triangle, and since the graph is 
undirected so (i,j,k) and (k,j,i) are the same. This algorithm runs in $O(|V|^3)$ time, where $V$ is the vertex set. Can we do better than 
cubic running time?

Let adj be the adjancency matrix of an undirected graph. adj[i][j] = k if there are k edges between i and j. Another way to think about 
this is that adj[i][j] counts the number of length 1 paths between i and j. It turns out that adj^n[i][j] counts the number of length n 
paths between i and j. Therefore for this problem, we are simply interested in adj^3[i][i]: number of length 3 paths between any node i and 
itself, i.e. triangles. The sum \sum_{i}adj^3[i][i] = trace(adj^3) has triple counts the nodes in a triagle. Modulo the undirectedness the 
result is trace(adj^3)/6. Strassen’s matrix multiplication algorithm runs in O(|V|^2.8074) time, thus this approach can beat the cubic running 
time in the brute-force algorithm. We will not implement Strassen's algorithm for this problem.
*/

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> matrixMul(vector<vector<int>> &A, vector<vector<int>> &B) {
    int m = A.size();
    int n = A[0].size();
    int k = B[0].size();
    vector<vector<int>> res(m, vector<int>(k));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            for (int l = 0; l < n; l++) {
                res[i][j] += A[i][l] * B[l][j];
            }
        }
    }
    return res;
}

int trace(vector<vector<int>> &A) {
    int res = 0;
    for (int i = 0; i < A.size(); i++) {
        res += A[i][i];
    }
    return res;
}

int trianglesInUndirectedGraph(vector<vector<int>> &graph) {
    vector<vector<int>> graphSquared = matrixMul(graph, graph);
    vector<vector<int>> graphCubed = matrixMul(graph, graphSquared);
    return trace(graphCubed)/6;
}


int main() {
	vector<vector<graph>> = {{0,1,1,0}, {1,0,1,1}, {1,1,0,1}, {0,1,1,0}};
	cout << trianglesInUndirectedGraph(graph) << endl;
	return 0;
}

