/*
Total Accepted: 114860
Total Submissions: 426358
Difficulty: Easy
Contributors: Admin
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.
*/

/*
Analysis: The idea is to use an auxiliary data structure to keep track of the minimum value current in the stack. The first idea is to use an int to store the global minimum. However, if this global min is popped, we have to spend another O(n) time recomputing it. Thus we need to have a data structure that keeps track of the minimum values after every push. This gives rise to the idea of using another stack.
*/

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        if (minRecord.empty() || x <= minRecord.top()) minRecord.push(x);
        st.push(x);
    }
    
    void pop() {
        if (st.empty()) return;
        if (st.top() == minRecord.top()) minRecord.pop();
        st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minRecord.top();
    }
private:
    stack<int> st;
    stack<int> minRecord;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
