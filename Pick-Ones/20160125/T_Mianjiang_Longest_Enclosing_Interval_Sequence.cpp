/*
Given a list of intervals, return the longest enclosing interval sequence in which the ith interval encloses the (i+1)th interval.

Example: Given [[-100, 100], [-5, 10], [1, 5], [-5, 10]], return [[-100, 100], [-5, 10], [1, 5]], length = 3.

Link: http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=146237&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26searchoption[3086][value]%3D5%26searchoption[3086][type]%3Dradio%26searchoption[3087][value]%3D4%26searchoption[3087][type]%3Dradio%26searchoption[3046][value]%3D20%26searchoption[3046][type]%3Dradio%26sortid%3D311
*/

/* Analysis:
This feels like the ski problem. In this case, monotonicity is translated to interval enclosure. 
As a first step, we compute the length of the longest enclosing interval sequence. The implementation runs in O(n^2) time, where 
n = number of intervals. 
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

int dfs(unordered_map<int, vector<int>> &ht, int curNode, vector<bool> &visited, vector<int> &dp) {
    if (visited[curNode]) return dp[curNode];
    
    if (ht.find(curNode) != ht.end()) {
        for (int i = 0; i < ht[curNode].size(); i++) {
            int nb = ht[curNode][i];
            dp[curNode] = max(dp[curNode], 1 + dfs(ht, nb, visited, dp));
        }
    }
    
    visited[curNode] = true;
    return dp[curNode];
}

int longestEnclosingIntervals(vector<Interval> &intervals) {
    if (intervals.empty() || intervals.size() == 1) return intervals.size();
    // sort intervals
    sort(intervals.begin(), intervals.end(), [](Interval i1, Interval i2) {return i1.start < i2.start || (i1.start == i2.start && i1.end < i2.end);});
    unordered_map<int, vector<int>> ht;
    for (int i = 0; i < intervals.size(); i++) {
        for (int j = i+1; j < intervals.size(); j++) {
            // intervals[i].start <= intervals[j].start already
            if (intervals[i].end >= intervals[j].end) {
                // interval i encloses j
                ht[i].push_back(j);
            }
        }
    }
    if (ht.empty()) return 1;
    // run 1D ski problem on ht
    // dp[i] = length of the longest enclosing sequence starting from interval i
    vector<int> dp(intervals.size(), 1);
    vector<bool> visited(intervals.size(), false);
    int maxLen = INT_MIN;
    for (auto it = ht.begin(); it != ht.end(); it++) {
        maxLen = max(maxLen, dfs(ht, it->first, visited, dp));
    }
    return maxLen;
}

int main() {
	Interval i1(1, 3);
	Interval i2(2, 4);
	Interval i3(3, 6);
	Interval i4(4, 7);
	vector<Interval> intervals = {i1, i2, i3, i4};
	cout << longestEnclosingIntervals(intervals) << endl;
	return 0;
}

