/*
Given a nested list of positive integers: {{1,1},2,{1,1}}
Compute the reverse depth sum of a nested list meaning the reverse depth of
each node (ie, 1 for leafs, 2 for parents of leafs, 3 for parents of parents
of leafs, etc.) times the value of that node.
For example:
{{1,1},2,{1,1}}
=> 1*1 + 1*1 + 2*2 + 1*1 + 1*1 = 8.
{1,{4,{6}}}
=> 6*1 + 4*2 + 1*3 = 6+8+3 = 17
*/

#include <iostream>
#include <list>

using namespace std;

class NestedInteger {
public:
    bool isInteger() { return children.empty(); }
    int getInteger() { return val; }
    list<NestedInteger> getList() { return children; }
    NestedInteger(int v): val(v) {}
    NestedInteger(list<NestedInteger> l): children(l) {}
private:
    int val;
    list<NestedInteger> children;
};

class Solution {
public:
    int depthSum(list<NestedInteger> lis) {
        return depthSumHelper(lis, 0);
    }
    int reverseDepthSum(list<NestedInteger> lis) {
        int maxdepth = 0;
        int totalSum = 0;
        int dSum = 0;
        rdSumHelper(lis, 0, maxdepth, totalSum, dSum);
        return (maxdepth + 1) * totalSum - dSum;
    }
private:
    int depthSumHelper(list<NestedInteger> lis, int level) {
        int sum = 0;
        for (auto it = lis.begin(); it != lis.end(); it++) {
            if (it->isInteger()) { sum += (level + 1) * it->getInteger(); }
            else { sum += depthSumHelper(it->getList(), level + 1); }
        }
        return sum;
    }
    void rdSumHelper(list<NestedInteger> lis, int level, int& maxdepth, int& totalSum, int& dSum) {
        for (auto it = lis.begin(); it != lis.end(); it++) {
            if (it->isInteger()) {
                totalSum += it->getInteger(); 
                dSum += (level + 1) * it->getInteger(); 
            }
            else { 
                rdSumHelper(it->getList(), level + 1, maxdepth, totalSum, dSum); 
            }
        }
        maxdepth = max(maxdepth, level + 1);
    }
};

int main() {
	// your code goes here
	/*
	NestedInteger a1(1);
	NestedInteger a2(1);
	list<NestedInteger> la;
	la.push_back(a1);
	la.push_back(a2);
	NestedInteger a(la);
	NestedInteger b(2);
	NestedInteger c1(1);
	NestedInteger c2(1);
	list<NestedInteger> lc;
	lc.push_back(c1);
	lc.push_back(c2);
	NestedInteger c(lc);
	list<NestedInteger> abc;
	abc.push_back(a);
	abc.push_back(b);
	abc.push_back(c);
	*/
	NestedInteger a(1);
	NestedInteger b(4);
	NestedInteger c(6);
	list<NestedInteger> cl;
	cl.push_back(c);
	list<NestedInteger> bl;
	bl.push_back(b);
	bl.push_back(cl);
	list<NestedInteger> abc;
	abc.push_back(a);
	abc.push_back(bl);
	Solution s;
	cout << s.reverseDepthSum(abc) << endl;
	return 0;
}
