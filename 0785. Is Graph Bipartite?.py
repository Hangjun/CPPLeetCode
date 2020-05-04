"""
Given an undirected graph, return true if and only if it is bipartite.

Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that every edge in the graph has one node in A and another node in B.

The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.

Example 1:
Input: [[1,3], [0,2], [1,3], [0,2]]
Output: true
Explanation: 
The graph looks like this:
0----1
|    |
|    |
3----2
We can divide the vertices into two groups: {0, 2} and {1, 3}.
Example 2:
Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
Output: false
Explanation: 
The graph looks like this:
0----1
| \  |
|  \ |
3----2
We cannot find a way to divide the set of nodes into two independent subsets.
 

Note:

graph will have length in range [1, 100].
graph[i] will contain integers in range [0, graph.length - 1].
graph[i] will not contain i or duplicate values.
The graph is undirected: if any element j is in graph[i], then i will be in graph[j].
"""

# DFS. Time: O(V+E), Space: O(V).
class Solution(object):
    def isBipartite(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: bool
        """
        if not graph:
            return True
        colorMap = {}
        
        # visit every node in the graph, if uncolored, color it and dfs on its neighbors
        for i in range(len(graph)):
            if i not in colorMap and graph[i]:
                colorMap[i] = 0
                if not self.dfs(graph, i, 0, colorMap):
                    return False
        return True
    
    def dfs(self, graph, curNode, curColor, colorMap):
        for n in graph[curNode]:
            if n not in colorMap:
                colorMap[n] = 1 - curColor
                if not self.dfs(graph, n, colorMap[n], colorMap):
                    return False
            elif colorMap[n] == curColor:
                return False
                
        return True

# BFS. Time: O(V+E), Space: O(V).
from collections import deque
class Solution(object):
    def isBipartite(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: bool
        """
        if not graph:
            return True
        colorMap = {}
        queue = deque([])
        # visit every node in the graph, if uncolored, color it and dfs on its neighbors
        for i in range(len(graph)):
            if i not in colorMap and graph[i]:
                colorMap[i] = 0
                queue.append(i)
                
                # BFS to color neighboring nodes level by level
                # invariant: node in the queue has already been colored
                while queue:
                    curSize = len(queue)
                    for _ in range(curSize):
                        curNode = queue.popleft()
                        for n in graph[curNode]:
                            if n not in colorMap:
                                colorMap[n] = 1 - colorMap[curNode]
                                queue.append(n)
                            elif colorMap[n] == colorMap[curNode]:
                                return False
        return True
