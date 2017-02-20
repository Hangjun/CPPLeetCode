/*
Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.


Example 1
Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2
Output: [0, 2]


Example 2
Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
Output: [-34, -14, -10, -10, 10]
*/

/* 
The key to solving this problem is to note that, to generate all possible ways to add parentheses is equivalent to evaluate every operation in its highest priority. The leads naturally to a recursive solution. 

Time: O(3^n), Space O(3^n).
*/

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> res;
        for (int i = 0; i < input.size(); i++) {
            char c = input[i];
            if (c == '+' || c == '-' || c == '*') {
                for (int a : diffWaysToCompute(input.substr(0, i))) {
                    for (int b : diffWaysToCompute(input.substr(i+1))) {
                        res.push_back(c == '+' ? a+b : c == '-' ? a-b : a*b);
                    }
                }
            }
        }
        return res.size() ? res : vector<int>{stoi(input)};
    }
};

/*
One way to improve the complexity is to memorize all previously computed results using a hash table.
*/
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        if (ht.find(input) != ht.end()) return ht[input];
        vector<int> res;
        for (int i = 0; i < input.size(); i++) {
            char c = input[i];
            if (c == '+' || c == '-' || c == '*') {
                for (int a : diffWaysToCompute(input.substr(0, i))) {
                    for (int b : diffWaysToCompute(input.substr(i+1))) {
                        res.push_back(c == '+' ? a+b : c == '-' ? a-b : a*b);
                    }
                }
            }
        }
        if (res.empty()) return vector<int>{stoi(input)};
        ht[input] = res;
        return res;
    }

private:
    unordered_map<string, vector<int>> ht;
};

// There is also an iterative DP solution:
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> nums;
        vector<char> ops;
        int i = 0;
        while (true) {
            int num = 0;
            while (i < input.size() && isdigit(input[i]))
                num = num * 10 + input[i++] - '0';
            nums.push_back(num);
            if (i < input.size())
                ops.push_back(input[i++]);
            else break;
        }
        int n = nums.size();
        vector<vector<vector<int>>> res(n, vector<vector<int>>(n));
        for (i = 0; i < n; i++)
        res[i][i].push_back(nums[i]);
        
        for (i = n-2; i >= 0; i--)  // for (int j = 1; j < n; j++)
            for (int j = i+1; j < n; j++) // for (i = j-1; i >= 0; i--)
                for (int k = i; k < j; k++)
                    for (int left: res[i][k])
                        for (int right: res[k+1][j])
                            res[i][j].push_back(operate(ops[k], left, right));
        
        return res[0][n-1];
  }
private:
    int operate(char op, int l, int r) {
        switch (op) {
            case '+': return l + r;
            case '-': return l - r;
            default: return l * r;
        }
    }
};
