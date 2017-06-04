/*
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.
*/

/*
Analysis: The idea is that we want to test for every possible pair of start and end points if there is a trip that can be made from start to end. We must check all possible to pairs in order to fully traverse the circle. We know that the entir circle is traversable if start and end coinside.

Given that a pair (start, end) is traversable, we greedily extend end as far as possible until (start, end*) is no longer traversable in which case we backtract start. The loop invariant is always that [start, end] is a traversable path.

Time: O(n), Space: O(1).
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int start = gas.size()-1, end = 0;
        int sum = gas[start] - cost[start];
        while (start > end) {
            if (sum >= 0) {
                // can proceed from start, move end ahead by 1
                sum += gas[end] - cost[end];
                ++end;
            } else {
                // cannot proceed further from start, backtrack start one step
                --start;
                sum += gas[start] - cost[start];
            }
        }
        return sum >= 0 ? start : -1;
    }
};
