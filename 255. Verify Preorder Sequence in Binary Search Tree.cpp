/*
Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.

You may assume each number in the sequence is unique.

Follow up:
Could you do it using only constant space complexity?
*/

/* Analysis:
The preorder array of a BST satisfies the following property: a monotonically decreasing subarray corresponds to traversing along the left nodes. The first node we reach, say A, that is larger than the previous node indicates that we are now in the right subtree of some node, and that node lies somewhere in the previous decreasing subarray. Let's call this parent node that is yet to be found node B.

For this tree to be a BST, any node in the rest of the array must be larger than B. To see this, note that A and everything in the subtree rooted at A are larger than B since A is in the right subtree. Therefore, if there is any later node that is smaller than B, preorder is not the preorder traversal of a BST. If this is the case otherwise for each such monotonically decreasing subarray followed by a node in a right subtree, then preorder is indeed the preorder traversal array.

Given A, how do we find B? If we look at the sequence of nodes leading up to A, say n1, n2, ..., nk, A, then B is the last node that is smaller than A going from nk back to n1. A stack is perfect for this task.

Time O(n), Space O(h), where h is the height of the BST.
*/

class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        int parent = INT_MIN;
        stack<int> st;
        for (int i = 0; i < preorder.size(); i++) {
            if (preorder[i] < parent) return false;
            while (!st.empty() && preorder[i] > st.top()) {
                parent = st.top();
                st.pop();
            }
            st.push(preorder[i]);
        }
        return true;
    }
};

// To optimize the space complexity, we abuse the input vector to get Time O(n), Space O(1):
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        int parent = INT_MIN;
        int i = -1;
        for (int n = 0; n < preorder.size(); n++) {
            if (preorder[n] < parent) return false;
            while (i >= 0 && preorder[n] > preorder[i]) parent = preorder[i--];
            preorder[++i] = preorder[n];
        }
        return true;
    }
};
