/*
Given a nested list of integers represented as a string, implement a parser to deserialize it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Note: You may assume that the string is well-formed:

String is non-empty.
String does not contain white spaces.
String contains only digits 0-9, [, - ,, ].
Example 1:

Given s = "324",

You should return a NestedInteger object which contains a single integer 324.
Example 2:

Given s = "[123,[456,[789]]]",

Return a NestedInteger object containing a nested list with 2 elements:

1. An integer containing value 123.
2. A nested list containing two elements:
    i.  An integer containing value 456.
    ii. A nested list with one element:
         a. An integer containing value 789.
*/

/*
这道题让我们实现一个迷你解析器用来把一个字符串解析成NestInteger类，关于这个嵌套链表类的题我们之前做过三道，Nested List Weight Sum II，Flatten Nested List Iterator，和Nested List Weight Sum。应该对这个类并不陌生了，我们可以先用递归来做，思路是，首先判断s是否为空，为空直接返回，不为空的话看首字符是否为'['，是的话说明s为一个整数，我们直接返回结果。如果首字符是'['，且s长度小于等于2，说明没有内容，直接返回结果。反之如果s长度大于2，我们从i=1开始遍历，我们需要一个变量start来记录某一层的其实位置，用cnt来记录跟其实位置是否为同一深度，cnt=0表示同一深度，由于中间每段都是由逗号隔开，所以当我们判断当cnt为0，且当前字符是逗号或者已经到字符串末尾了，我们把start到当前位置之间的字符串取出来递归调用函数，把返回结果加入res中，然后start更新为i+1。如果遇到'['，计数器cnt自增1，若遇到']'，计数器cnt自减1。参见代码如下：
*/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    NestedInteger deserialize(string s) {
        if (s.empty()) return NestedInteger();
        if (s[0] != '[') return NestedInteger(stoi(s));
        if (s.size() <= 2) return NestedInteger();
        
        NestedInteger res;
        int start = 1, depthDiff = 0;
        for (int i = 1; i < s.size(); i++) {
            if (depthDiff == 0 && (s[i] == ',' || i == s.size()-1)) {
                res.add(deserialize(s.substr(start, i-start)));
                start = i+1;
            } else if (s[i] == '[') depthDiff++;
            else if (s[i] == ']') depthDiff--;
        }
        
        return res;
    }
};

/*
我们也可以使用迭代的方法来做，这样就需要使用栈来辅助，变量start记录起始位置，我们遍历字符串，如果遇到'['，我们给栈中加上一个空的NestInteger，如果遇到的字符数逗号或者']'，如果i>start，那么我们给栈顶元素调用add来新加一个NestInteger，初始化参数传入start到i之间的子字符串转为的整数，然后更新start=i+1，当遇到的']'时，如果此时栈中元素多于1个，那么我们将栈顶元素取出，加入新的栈顶元素中通过调用add函数，参见代码如下：
*/

class Solution {
public:
    NestedInteger deserialize(string s) {
        if (s.empty()) return NestedInteger();
        if (s[0] != '[') return NestedInteger(stoi(s));
        stack<NestedInteger> st;
        int start = 1;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '[') {
                st.push(NestedInteger());
                start = i + 1;
            } else if (s[i] == ',' || s[i] == ']') {
                if (i > start) {
                    st.top().add(NestedInteger(stoi(s.substr(start, i - start))));
                }
                start = i + 1;
                if (s[i] == ']') {
                    if (st.size() > 1) {
                        NestedInteger t = st.top(); st.pop();
                        st.top().add(t);
                    }
                }
            }
        }
        return st.top();
    }
};
