# Microsoft Interview Follow Up
```
Given N currencies and a matrix M such that M[i][j] represents that currency i can be used to buy M[i][j] units of currency j. Given a particular currency, determine whether there is an optimal way to utilize the arbitrage that might exists in a chain of currency exchanges.
```

_**Solution**_: Note that it suffices to find a cycle of currencies ${c_{1}, c_{2}, \cdots, c_{k}}$ such that 
\begin{equation}
M[c_{1}][c_{2}] \cdot M[c_{2}][c_{3}] \cdots M[c_{k}][c_{1}] > 1.
\end{equation}

Let $G: = \{V, E\}$ be a directed weighted graph with vertices the N currencies and edges $(i, j)$ if we can exchange $i$ for $j$. In this case we are assuming we can go from any currency to any other, thus $|E| = 
\binom {N} {2}$. Intuitively, we want to transform the problem of finding a currency sequence satisfying the above equation to the problem of finding a **directed (negative) cycle** in $G$. Therefore we need to define weights in a way that is additive instead of multiplicative as in Equation (1).

Set $w[i][j]: = -\log M[i][j]$ for vertices $i$ and $j$. Then Equation (1) is equivalent to 
\begin{equation}
w[c_{1}][c_{2}] + w[c_{2}][c_{3}] + \cdots + w[c_{k}][c_{1}] < 0.
\end{equation}

The problem is now to find a directed negative cycle in $G = \{V, E, w\}$, in which $w$ is the weight function defined above. 

The **Bellman–Ford** algorithm is perfect for this problem as it can compute single source shortest paths as well as detecting negative cycles. For the purpose of this problem we manually add a source node $c_{0}$ that has an edge to all other vertices in the graph with weights identically $0$. We then run Bellman–Ford with $c_{0}$ as the source node.

There are many standard implementations of the Bellman–Ford algorithm (see http://www.geeksforgeeks.org/dynamic-programming-set-23-bellman-ford-algorithm/ for example). 

_**Complexity Analysis**_: For time complexity, constructing $G$ takes $O(N^{2})$ time. Bellman–Ford algorithm runs in $O(N^{3})$ time. So the total time complexity is $O(N^{3})$. For space complexity, $G$ consumes $O(N^{2})$ space, and Bellman–Ford uses $O(N)$ to keep track of the distances from the source. So the total space complexity is $O(N^{2})$.

_**Further Discussions**_: If we want to print out a directed negative cycle, we can add an array $\verb+parent+$ that keeps track of the parent node of every node:

```c++
// initialize parent[i] = NULL

for (int j = 0; j < E; j++) {
    int u = graph->edge[j].src;
    int v = graph->edge[j].dest;
    int weight = graph->edge[j];
    if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        dist[v] = dist[u] + weight;
        // update the parent table
        parent[v] = u;
    }
}
```

To print out the path, we recursively relax the edge weights and follow the parent table to trace out the path. The additional time to print out the path is $O(N)$.


