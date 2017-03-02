/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:
  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
*/

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        if (tokens.empty()) return 0;
        stack<int> st;
        for (string c : tokens) {
            if (!validOperator(c)) {
                st.push(stoi(c));
            } else {
                int y = st.top();
                st.pop();
                int x = st.top();
                st.pop();
                st.push(eval(x, y, c));
            }
        }
        return st.top();
    }
private:
    int eval(int x, int y, string op) {
        if (op == "+") return x + y;
        else if (op == "-") return x - y;
        else if (op == "*") return x * y;
        return x / y;
    }
    
    bool validOperator(string op) {
        return op == "+" || op == "-" || op == "*" || op == "/";
    }
};

