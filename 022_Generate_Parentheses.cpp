/*
 Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()" 
*/

This is an obvious backtracking problem. The question is in what order do we generate all the parentheses. 
A first idea is to generate (n-1) pairs first, and then loop on the possible positions to insert the nth. But not only is this 
too complicated, it is also time consuming since inserting a character into a string is a linear operation.

Another idea is then to generate the left parentheses independently of the right parentheses. Then the key is to understand what 
are the constraints in terms of the order in which left and right parentheses can be generated. It is not hard to notice that as 
long as the number of left parentheses is less than $n$, we can also push \verb+'('+ into a local solution and get a legal string.
On the other hand, to be able to push \verb+')'+ to a local solution, we need to make sure that the number of \verb+'('+'s is 
larger than the number of \verb+')'+'s. And that is also a sufficient condition. 

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        if (n <= 0) return res;
        string curSoln;
        generateDFS(n, 0, 0, curSoln, res);
        return res;
    }
    
    void generateDFS(int n, int nleft, int nright, string &curSoln, vector<string> &res) {
        // terminate condition
        if (nleft == n && nright == n) {
            res.push_back(curSoln);
            return;
        }
        if (nleft < n) {
            curSoln.push_back('(');
            generateDFS(n, nleft+1, nright, curSoln, res);
            curSoln.pop_back();
        }
        if (nleft > nright) {
            curSoln.push_back(')');
            generateDFS(n, nleft, nright+1, curSoln, res);
            curSoln.pop_back();
        }
    }
};
