/*
Assume you have an array of length n initialized with all 0's and are given k update operations.

Each operation is represented as a triplet: [startIndex, endIndex, inc] which increments each element of subarray A[startIndex ... endIndex] (startIndex and endIndex inclusive) with inc.

Return the modified array after all k operations were executed.

Example:

Given:

    length = 5,
    updates = [
        [1,  3,  2],
        [2,  4,  3],
        [0,  2, -2]
    ]

Output:

    [-2, 0, 3, 5, 3]
Explanation:

Initial state:
[ 0, 0, 0, 0, 0 ]

After applying operation [1, 3, 2]:
[ 0, 2, 2, 2, 0 ]

After applying operation [2, 4, 3]:
[ 0, 2, 5, 5, 3 ]

After applying operation [0, 2, -2]:
[-2, 0, 3, 5, 3 ]
*/

/*
The idea seems tricky at first look but is actually simple after you understand it, basically we want to achieve the final result array in two passes:

Iterate through the k update operations and "somehow" mark them in the [0, 0, 0, 0, 0] array (using length 5 for example), for each operation, only update startIndex and endIndex + 1. this is O(k) in total.
iterate through the marked array and "somehow" transforms it to the final result array. this is O(n) in total (n = length).
All in all it is O(n + k).
Now think in a simpler way first, if you have only one update operation, suppose input is (n = 5, updates = { {1, 3, 2} }), what does the O(n + k) solution do?

Initialize the result array as length of n + 1, because we will operate on endIndex + 1:
result = [0, 0, 0, 0, 0, 0]
Then marks index 1 as 2 and marks index 3+1 as -2:
result = [0, 2, 0, 0, -2, 0]
Next, iterate through result, and accumulates previous sum to current position, just like 303. Range Sum Query - Immutable:
result = [0, 0 + 2, 0 + 2, 0 + 2, 2 + (-2), 0] = [0, 2, 2, 2, 0, 0]
Finally, trivial work to discard the last element because we don't need it:
result = [0, 2, 2, 2, 0], which is the final result.
Now you might see why we do "puts inc at startIndex and -inc at endIndex + 1":

Put inc at startIndex allows the inc to be carried to the next index starting from startIndex when we do the sum accumulation.
Put -inc at endIndex + 1 simply means cancel out the previous carry from the next index of the endIndex, because the previous carry should not be counted beyond endIndex.
And finally, because each of the update operation is independent and the list operation is just an accumulation of the "marks" we do, so it can be "makred" all at once first and do the range sum at one time at last step.

Time: O(n+k), Space: O(1).
*/
class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> res(length+1, 0);
        for (int i = 0; i < updates.size(); i++) {
            res[updates[i][0]] += updates[i][2];
            res[updates[i][1]+1] -= updates[i][2]; // used to cancel out the update effect from updates[i][1]+1 and onward
        }
        
        // compute the "net effect" of all the updates
        for (int j = 1; j < length; j++) res[j] += res[j-1];
            
        res.pop_back();
        return res;
    }
};
