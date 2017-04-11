/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.
Example:
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.
*/

// Time: log(n) for query and update. Space: O(2^n).
class SegmentTreeNode {
public:
    int low;
    int high;
    int sum;
    SegmentTreeNode *left;
    SegmentTreeNode *right;
    
    SegmentTreeNode(): left(NULL), right(NULL) {}
};

class NumArray {
public:
    NumArray(vector<int> nums) {
        if (nums.empty()) return;
        root = createSegmentTree(nums, 0, nums.size()-1);
        v = nums;
        return;
    }
    
    void update(int i, int val) {
        if (i < 0 || i >= v.size() || v[i] == val) return;
        int delta = val - v[i];
        v[i] = val; // Don't forget to update upfront
        SegmentTreeNode *curNode = root;
        while (true) {
            if (i >= curNode->low && i <= curNode->high) curNode->sum += delta;
            if (curNode->low == curNode->high) break;
            
            if (i <= curNode->left->high) curNode = curNode->left;
            else curNode = curNode->right;
        }
    }
    
    int sumRange(int i, int j) {
        if (i > j || i < 0 || j >= v.size()) return 0;
        return sumRangeRecur(root, i, j);
    }
    
private:
    SegmentTreeNode *root;
    vector<int> v;
    
    SegmentTreeNode *createSegmentTree(vector<int> &v, int l, int h) {
        SegmentTreeNode *root = new SegmentTreeNode();
        root->low = l; root->high = h;
        if (l == h) {
            root->sum = v[l];
            return root;
        }
        root->left = createSegmentTree(v, l, l+(h-l)/2);
        root->right = createSegmentTree(v, l+(h-l)/2+1, h);
        root->sum = root->left->sum + root->right->sum;
        return root;
    }
    
    int sumRangeRecur(SegmentTreeNode *curNode, int l, int r) {
        // basecase
        if (curNode->low == l && curNode->high == r) return curNode->sum;
        if (l > curNode->left->high) return sumRangeRecur(curNode->right, l, r);
        if (r < curNode->right->low) return sumRangeRecur(curNode->left, l, r);
        return sumRangeRecur(curNode->left, l, curNode->left->high) + sumRangeRecur(curNode->right, curNode->right->low, r);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */
