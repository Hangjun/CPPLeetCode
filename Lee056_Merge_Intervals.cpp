/*
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18]. 
*/


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
        Interval lastInterval = intervals[0];
        for (int i = 1; i < intervals.size(); i++) {
            if (lastInterval.end >= intervals[i].start && lastInterval.start <= intervals[i].end) {
                lastInterval.start = min(lastInterval.start, intervals[i].start);
                lastInterval.end = max(lastInterval.end, intervals[i].end);
            } else {
                res.push_back(lastInterval);
                lastInterval = intervals[i];
            }
        }
        res.push_back(lastInterval);
        return res;
    }
};
