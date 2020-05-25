/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.


Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].


The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given heights = [2,1,5,6,2,3],
return 10.
*/

/*
A brute-force solution is to consider every possible index pair (i, j) and compute the max area enclosed within.

Time: O(n^2), Space: O(1). TLE.
*/
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxArea = 0;
        int n = heights.size();
        for (int i = 0; i < n; i++) {
            if (heights[i] && maxArea/heights[i] >= n - i) continue; // early stopping
            int minHeight = INT_MAX;
            for (int j = i; j < n; j++) {
                minHeight = min(minHeight, heights[j]);
                maxArea = max(maxArea, minHeight * (j - i + 1));
            }
        }
        return maxArea;
    }
};

/*
Solution using Divide-and-Conquer.This approach relies on the observation that the rectangle with maximum area will be the maximum of:
1. The widest possible rectangle with height equal to the height of the shortest bar.
2. The largest rectangle confined to the left of the shortest bar(subproblem).
3. The largest rectangle confined to the right of the shortest bar(subproblem).

Time: Average Case: O(nlogn), Worst Case: O(n^2). If the numbers in the array are sorted, we don't gain the advantage of divide and conquer.
Space: O(n). Recursion with worst case depth n.

TLE.
*/
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        return maxAreaRecur(heights, 0, heights.size()-1);
    }
    
    int maxAreaRecur(vector<int> &heights, int start, int end) {
        if (start > end) return 0;
        int minIndex = start;
        for (int i = start+1; i <= end; i++) {
            if (heights[i] < heights[minIndex]) minIndex = i;
        }
        return max(heights[minIndex]*(end-start+1), max(maxAreaRecur(heights, start, minIndex-1), maxAreaRecur(heights, minIndex+1, end)));
    }
};

/*
Remark: You can observe that in the Divide and Conquer Approach, we gain the advantage, since the large problem is divided 
into substantially smaller subproblems. But, we won't gain much advantage with that approach if the array happens to be 
sorted in either ascending or descending order, since every time we need to find the minimum number in a large subarray which 
takes O(n). Thus, the overall complexity becomes O(n^2) in the worst case. We can reduce the time complexity by using a 
Segment Tree to find the minimum every time which can be done in O(logn) time. The overall time complexity is then reduced to 
O(nlogn).
*/

/*
Analysis: In this approach, we maintain a stack. Initially, we push a -1 onto the stack to mark the end. We start with the 
leftmost bar and keep pushing the current bar's index onto the stack until we get two successive numbers in descending order, 
i.e. until we get a[i-1] > a[i]. Now, we start popping the numbers from the stack until we hit a number stack[j]stack[j] on 
the stack such that a\big[stack[j]\big] \leq a[i]a[stack[j]]≤a[i]. Every time we pop, we find out the area of rectangle formed 
using the current element as the height of the rectangle and the difference between the the current element's index pointed 
to in the original array and the element stack[top-1] -1stack[top−1]−1 as the width i.e. if we pop an element 
stack[top]stack[top] and i is the current index to which we are pointing in the original array, the current area of the 
rectangle will be considered as (i-stack[top-1]-1) \times a\big[stack[top]\big](i−stack[top−1]−1)×a[stack[top]].

Further, if we reach the end of the array, we pop all the elements of the stack and at every pop, this time we use the 
following equation to find the area: (stack[top]-stack[top-1]) \times a\big[stack[top]\big](stack[top]−stack[top−1])×a[stack[top]], 
where stack[top]stack[top] refers to the element just popped. Thus, we can get the area of the of the largest rectangle by 
comparing the new area found everytime.

Here is a really nice blog in Chinese that describes this algorithm in detail: http://www.cnblogs.com/lichen782/p/leetcode_Largest_Rectangle_in_Histogram.html.

Time: O(n), Space: O(n).
*/
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxArea = 0;
        stack<int> st;
        st.push(-1);
        for (int i = 0; i < heights.size(); i++) {
            while (st.top() != -1 && heights[st.top()] >= heights[i]) {
                int t = st.top();
                st.pop();
                maxArea = max(maxArea, heights[t] * (i - st.top() - 1));
            }
            st.push(i);
        }
        
        int lastIndex = st.top();
        while (st.top() != -1) {
            int t = st.top();
            st.pop();
            maxArea = max(maxArea, heights[t] * (lastIndex - st.top()));
        }
        
        return maxArea;
    }
};
