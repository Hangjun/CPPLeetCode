/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.
*/

/*
这道题是之前那道Meeting Rooms的拓展，那道题只让我们是否能参加所有的会，也就是看会议之间有没有时间冲突，而这道题让我们求最少需要安排几个会议室，
有时间冲突的肯定需要安排在不同的会议室。这道题有好几种解法，我们先来看使用map来做的，我们遍历时间区间，对于起始时间，映射值自增1，对于结束时间，
映射值自减1，然后我们定义结果变量res，和房间数rooms，我们遍历map，时间从小到大，房间数每次加上映射值，然后更新结果res，遇到起始时间，映射是正数，
则房间数会增加，如果一个时间是一个会议的结束时间，也是另一个会议的开始时间，则映射值先减后加仍为0，并不用分配新的房间，而结束时间的映射值为负数更不会
增加房间数，利用这种思路我们可以写出代码如下:
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
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> m; // map will automatically sort the key
        for (auto a : intervals) {
            ++m[a.start];
            --m[a.end];
        }
        int rooms = 0, res = 0;
        for (auto it : m) res = max(res, rooms += it.second);
        
        return res;
    }
};

/*
第二种方法是用两个一维数组来做，分别保存起始时间和结束时间，然后各自排个序，我们定义结果变量res和结束时间指针endpos，然后我们开始遍历，如果当前起始时间小于结束时间指针的时间，则结果自增1，反之结束时间指针自增1，这样我们可以找出重叠的时间段，从而安排新的会议室，参见代码如下：
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
    int minMeetingRooms(vector<Interval>& intervals) {
        int res = 0;
        vector<int> startTimes;
        vector<int> endTimes;
        for (auto i : intervals) {
            startTimes.push_back(i.start);
            endTimes.push_back(i.end);
        }
        
        sort(startTimes.begin(), startTimes.end());
        sort(endTimes.begin(), endTimes.end());
        int endPos = 0;
        for (int i = 0; i < intervals.size(); i++) {
            if (startTimes[i] < endTimes[endPos]) ++res; // need to room for time window [startTimes[i], endTimes[endPos]]
            else ++endPos;
        }
        
        return res;
    }
};

// Solution #3: Min heap. Time: O(nlogn) on average, Space: O(n). Here n = number of intervals.
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

