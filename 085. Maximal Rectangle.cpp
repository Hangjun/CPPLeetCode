/*
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 6.
*/

/*
Time: O(n^2), Space: O(n).
*/

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> heights(n, 0);
        int maxArea = 0;
        
        for (int i = 0; i < m; i++) {
            // update height map
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') heights[j]++;
                else heights[j] = 0; // need to zero out previous heights
            }
            maxArea = max(maxArea, largestRectangleArea(heights));
        }
        
        return maxArea;
    }
    
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
