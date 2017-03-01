/*
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18]. 
*/

// Time: O(nlogn), Space: O(1). n = number of intervals.
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> res;
        if (intervals.empty()) return res;
        sort(intervals.begin(), intervals.end(), [](Interval i1, Interval i2){return i1.start < i2.start || i1.start == i2.start && i1.end < i2.end;});
        res.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            if (res.back().end < intervals[i].start) res.push_back(intervals[i]);
            else res.back().end = max(res.back().end, intervals[i].end);
        }
        return res;
    }
};
