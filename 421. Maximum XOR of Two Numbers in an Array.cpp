/*
Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.

Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.

Could you do this in O(n) runtime?

Example:

Input: [3, 10, 5, 25, 2, 8]

Output: 28

Explanation: The maximum result is 5 ^ 25 = 28.
*/

/*
This problem is a very neat application of the trie data structure. An O(n^2) time solution is trivial. The requirement that it should run in O(n) with this type of problem hints that for every number, it should be comparing (xor in this case) with ALL other numbers at the same time. This is the only possible way to make this linear. Trie is then a very natural outcome of this thought. What are we storing in the trie? Well, if we are matching words we store characters. Now we are xor-ing bits and hence we store all the bits.

Time: O(32n), Space: O(n).
*/

class TrieNode {
public:
    TrieNode *ch[2];
    TrieNode() {
        ch[0] = NULL;
        ch[1] = NULL;
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(vector<int> &nums) {
        for (int n : nums) {
            TrieNode *curNode = root;
            for (int i = 31; i >= 0; i--) {
                int index = (n >> i) & 1;
                if (!curNode->ch[index]) curNode->ch[index] = new TrieNode();
                curNode = curNode->ch[index];
            }
        }
    }
    
    int helper(vector<int> &nums) {
        int res = INT_MIN;
        // for every number, xor it with all other numbers at the same time and record the maximum value
        for (int n : nums) {
            TrieNode *curNode = root;
            int curSum = 0;
            for (int i = 31; i >= 0; i--) {
                int curBit = (n >> i) & 1;
                /* there exists a number which the current number can xor with and get non-zero value 
                at the index^th bit
                */
                if (curNode->ch[curBit^1]) {
                    curSum += (1 << i);
                    curNode = curNode->ch[curBit^1];
                } else {
                    curNode = curNode->ch[curBit];
                }
            }
            res = max(res, curSum);
        }
        return res;
    }
    
private:
    TrieNode *root;
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        Trie T;
        T.insert(nums);
        return T.helper(nums);
    }
};
