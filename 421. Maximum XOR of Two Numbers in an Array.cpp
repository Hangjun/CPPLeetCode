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
This problem is a very neat application of the trie data structure. An O(n^2) time solution is trivial. The requirement that 
it should run in O(n) with this type of problem hints that for every number, it should be comparing (xor in this case) with 
ALL other numbers at the same time. This is the only possible way to make this linear. Trie is then a very natural outcome of 
this thought. What are we storing in the trie? Well, if we are matching words we store characters. Now we are xor-ing bits 
and hence we store all the bits.

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

/*
But we are not done yet. Consider the follow up question:

Given an array of integers. find the maximum XOR subarray value in given array. Expected time complexity O(n).

Trie is still the data structure to use, but we need to store additional information into the Trie. The key is to observe that, if f(i,j) is xor subrray value from i to j, then f(i, j) = f(0, j) xor f(0, i-1). Make sure you understand why this is true.
*/
// C++ program for a Trie based O(n) solution to find max subarray XOR
class TrieNode
{
public:
	int val;
	TrieNode *ch[2];
	
	TrieNode() :val(0){
	    ch[0] = NULL;
	    ch[1] = NULL;
	}
};

class Trie {
public:
    Trie() { root = new TrieNode(); }
    
    // Inserts pre_xor (xor of nums[0...i]) to trie
    void insert(int pre_xor)
    {
	    TrieNode *curNode = root;

	    // Start from the msb, insert all bits of pre_xor into Trie
	    for (int i=31; i>=0; i--)
	    {
		    // Find current bit in given prefix
		    bool index = pre_xor & (1<<i);

		    // Create a new node if needed
		    if (!curNode->ch[index]) curNode->ch[index] = new TrieNode();
            curNode = curNode->ch[index];
	    }
	    // Store value at leaf node
	    curNode->val = pre_xor;
    }
    
    int query(int pre_xor) {
        TrieNode *curNode = root;
        for (int i = 31; i >= 0; i--) {
            int index = pre_xor & (1 << i);
            if (curNode->ch[index ^ 1]) {
                curNode = curNode->ch[index ^ 1];
            } else {
                curNode = curNode->ch[index];
            }
        }
        return pre_xor ^ curNode->val;
    }
    
private:
    TrieNode *root;
};

// Returns maximum XOR value of a subarray in nums[0..n-1]
int maxSubarrayXOR(vector<int> &nums) {
    int res = INT_MIN;
    int pre_xor = 0;
    Trie T;
    T.insert(0);
        
    for (int n : nums) {
        pre_xor ^= n;
        T.insert(pre_xor);
        res = max(res, T.query(pre_xor));
    }
    
    return res;
}

// Driver program to test above functions
int main()
{
    
	vector<int> nums = {8, 1, 2, 12};
	cout << "Max subarray XOR is " << maxSubarrayXOR(nums);
	return 0;
}
