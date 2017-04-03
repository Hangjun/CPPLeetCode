/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
*/

/*
Analysis: Recall that in Problem 20. Valid Parentheses we used a stack to detect whether a given string is full of valid parentheses. We can use the same stack here with the key observation that the index "gap" between the indcies in the stack that cannot be matched and poped are the lengths of valid parentheses intervals. We can keep track of these lenghts as we scan the string.

Time: O(n), Space: O(n).
*/

class Solution {
public:
    int longestValidParentheses(string s) {
        int maxLen = 0;
        stack<int> st;
        st.push(-1);
        
        for (int i = 0; i < s.size(); i++) {
            int t = st.top();
            if (t != -1 && s[i] == ')' && s[t] == '(') {
                st.pop();
                maxLen = max(maxLen, i - st.top());
            } else {
                st.push(i);
            }
        }
        
        return maxLen;
    }
};
