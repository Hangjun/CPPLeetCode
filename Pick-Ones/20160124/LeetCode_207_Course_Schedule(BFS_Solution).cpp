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

// We use BFS and indegree to solve this problem again.

/* Submission #1: Failed: 
Submission Result: Wrong Answer
Input: 3
[[0,1],[0,2],[1,2]]
Output: false
Expected: true 
*/
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        if (prerequisites.empty()) return true;
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
        while (!prereqCourses.empty()) {
            int curCourse = prereqCourses.front();
            prereqCourses.pop();
            for (int i = 0; i < prerequisites.size(); i++) {
                if (prerequisites[i].second == curCourse) {
                    --totalDegree;
                    if (inDegree[--prerequisites[i].first] == 0) {
                        prereqCourses.push(prerequisites[i].first);
                    }
                }
            }
        }
        return totalDegree == 0;
    }
};

/* Analysis:
Typo: line 61 should be if (--inDegree[prerequisites[i].first] == 0)
*/

// Submission #2: Accepted.
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



