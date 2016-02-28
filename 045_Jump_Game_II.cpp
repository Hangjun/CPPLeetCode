/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)

Note:
You can assume that you can always reach the last index.
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        /*  curMaxIndex = current most number of steps we can
            jump by checking all possible steps we can take
            given by lastMaxIndex
        */
        int curMaxIndex = 0, lastMaxIndex;
        int njumps = 0, i = 0;
        while (curMaxIndex < nums.size()-1) {
            lastMaxIndex = curMaxIndex;
            for (; i <= lastMaxIndex; i++)
                curMaxIndex = max(curMaxIndex, i + nums[i]);
            //we cannot get to the last entry, return -1
            if (curMaxIndex == lastMaxIndex) return -1;
            njumps++;
        }
        return njumps;
    }
};
