/*
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:

2, [[1,0]]

There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.

2, [[1,0],[0,1]]

There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.

click to show more hints.
Hints:

    This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
    Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
    Topological sort could also be done via BFS.
*/

/* Analysis:
We can finish all the courses if and only if a topological ordering exists. Thus the problem is equivalent as detecting whether a directed 
cycle exists. We first need to transform the edge list representation to an adjacency list representation of the graph. Then we can simply 
run our DFS cycle detection algorithm above. 
*/

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        if (prerequisites.empty() || numCourses == 0) return true;
        // build adjacency list
        vector<unordered_set<int>> adj(numCourses);
        for (int i = 0; i < prerequisites.size(); i++) {
            // e.second -> e.first, i.e. e.second is a prerequisite for e.first
            pair<int, int> e = prerequisites[i];
            adj[e.second].insert(e.first);
        }
        // detect directed cycle in adj
        vector<bool> visited(numCourses, false);
        vector<bool> inStack(numCourses, false);
        for (int i = 0; i < numCourses; i++) {
            if (!visited[i]) {
                if (dfs(adj, i, visited, inStack)) {
                    // a cycle exists: cannot finish
                    return false;
                }
            }
        }
        // no cycle detected: can finish
        return true;
    }

private:
    bool dfs(vector<unordered_set<int>> &adj, int index, vector<bool> &visited, vector<bool> &inStack) {
        visited[index] = true;
        inStack[index] = true;
        for (auto it = adj[index].begin(); it != adj[index].end(); it++) {
            if (!visited[*it] && dfs(adj, *it, visited, inStack)) { // cycle found
                return true;
            }
            if (inStack[*it]) { // cycle found
                return true;
            }
        }
        inStack[index] = false;
        // no cycle eminating from node index
        return false;
    }
};

/* Analysis:
We also use the in-degree in graph theory to represent dependencies of courses. The following is a BFS solution.
*/

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        if (prerequisites.empty()) return true;
        // inDegree[i] = k means courses i has k prerequisites
        // courses without any prerequisites can be taken immedinately
        vector<int> inDegree(numCourses, 0);
        for (int i = 0; i < prerequisites.size(); i++) {
            inDegree[prerequisites[i].first]++;
        }
        queue<int> prereqCourses;
        int totalDegree = 0;
        for (int i = 0; i < numCourses; i++) {
            totalDegree += inDegree[i];
            if (inDegree[i] == 0) {
                prereqCourses.push(i);
            }
        }
        if (prereqCourses.empty()) return false;
        while (totalDegree != 0 && !prereqCourses.empty()) {
            int curCourse = prereqCourses.front();
            prereqCourses.pop();
            for (int i = 0; i < prerequisites.size(); i++) {
                if (prerequisites[i].second == curCourse) {
                    --totalDegree;
                    if (--inDegree[prerequisites[i].first] == 0) {
                        prereqCourses.push(prerequisites[i].first);
                    }
                }
            }
        }
        return totalDegree == 0;
    }
};


