/*
 There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

For example:

2, [[1,0]]

There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]

There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.

click to show more hints.
Hints:

    This problem is equivalent to finding the topological order in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
    Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
    Topological sort could also be done via BFS.
*/

/* Submission #1: Falied:
Submission Result: Wrong Answer
Input: 2
[[1,0]]
Output: [0]
Expected: Special judge: No expected output available.
*/
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> order;
        if (prerequisites.empty()) {
            for (int i = 0; i < numCourses; i++) {
                order.push_back(i);
            }
            return order;
        }
        // construct in-degree table
        vector<int> inDegree(numCourses, 0);
        for (int i = 0; i < prerequisites.size(); i++) {
            inDegree[prerequisites[i].first]++;
        }
        int totalDegree = 0;
        queue<int> prereqCourses;
        for (int i = 0; i < numCourses; i++) {
            totalDegree += inDegree[i];
            if (inDegree[i] == 0) {
                prereqCourses.push(i);
            }
        }
        if (prereqCourses.empty()) {
            return order;
        }
        while (totalDegree != 0 && !prereqCourses.empty()) {
            int curCourse = prereqCourses.front();
            prereqCourses.pop();
            order.push_back(curCourse);
            for (int i = 0; i < prerequisites.size(); i++) {
                if (prerequisites[i].second == curCourse) {
                    totalDegree--;
                    if (--inDegree[prerequisites[i].first] == 0) {
                        prereqCourses.push(prerequisites[i].first);
                    }
                }
            }
        }
        if (totalDegree != 0) {
            order.clear();
            return order;
        }
        return order;
    }
};

/* Analysis:
The while-loop terminated before we have a chance to push course 1 into the final order. Also checking total != 0 in the while-loop is 
redundent.
*/

// Submission #2: Accepted.
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> order;
        if (prerequisites.empty()) {
            for (int i = 0; i < numCourses; i++) {
                order.push_back(i);
            }
            return order;
        }
        // construct in-degree table
        vector<int> inDegree(numCourses, 0);
        for (int i = 0; i < prerequisites.size(); i++) {
            inDegree[prerequisites[i].first]++;
        }
        int totalDegree = 0;
        queue<int> prereqCourses;
        for (int i = 0; i < numCourses; i++) {
            totalDegree += inDegree[i];
            if (inDegree[i] == 0) {
                prereqCourses.push(i);
            }
        }
        if (prereqCourses.empty()) {
            return order;
        }
        while (!prereqCourses.empty()) {
            int curCourse = prereqCourses.front();
            order.push_back(curCourse);
            prereqCourses.pop();
            for (int i = 0; i < prerequisites.size(); i++) {
                if (prerequisites[i].second == curCourse) {
                    totalDegree--;
                    if (--inDegree[prerequisites[i].first] == 0) {
                        prereqCourses.push(prerequisites[i].first);
                    }
                }
            }
        }
        if (totalDegree != 0) {
            order.clear();
            return order;
        }
        return order;
    }
};
