/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.
*/

// Solution #1: Min heap. Time: O(nlogn) on average, Space: O(n). Here n = number of intervals.
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

class myCompare {
public:
    bool operator()(const Interval &i1, const Interval &i2)
    {
        return i1.end > i2.end; // min heap
    }
};

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        if (intervals.empty()) return 0;
        sort(intervals.begin(), intervals.end(), [](Interval i1, Interval i2){return i1.start < i2.start || i1.start == i2.start && i1.end < i2.end;});
        priority_queue<Interval, vector<Interval>, myCompare> pq;
        
        pq.push(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            // get the meeting room that finishes earilest
            Interval curMeeting = pq.top();
            pq.pop();
            if (intervals[i].start >= curMeeting.end) curMeeting.end = intervals[i].end; // no need to allocate more room
            else pq.push(intervals[i]); // additional meeting room needed
            
            pq.push(curMeeting);
        }
        
        return pq.size();
    }
};

