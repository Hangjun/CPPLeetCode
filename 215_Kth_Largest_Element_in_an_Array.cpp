/*
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note: 
You may assume k is always valid, 1 ≤ k ≤ array's length.
*/

// Time: O(nlogn), Space: O(n)
class myCompare {
public: 
    bool operator()(int &a, int &b) {
        return a > b;
    }
};

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>> maxHeap;
        for (int i = 0; i < nums.size(); i++)
            maxHeap.push(nums[i]);
            
        int counter = 0;
        while (counter < k-1) {
            maxHeap.pop();
            counter++;
        }
        
        return maxHeap.top();
    }
};

// Quick select: Time: O(n) average, O(n^2) worse case, Space: O(1). T(n) = T(n/2) + O(n).
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size()-1;
        while (true) {
            int pos = partition(nums, left, right);
            if (pos == k-1) return nums[pos];
            else if (pos > k-1) right = pos-1;
            else left = pos+1;
        }
    }
private:
    int partition(vector<int> &nums, int left, int right) {
        // partition nums such that [>= pivot, pivot, <= pivot] since we are looking for the kth largest
        int pivot = nums[left];
        int l = left+1, r = right;
        while (l <= r) {
            if (nums[l] < pivot && nums[r] > pivot) swap(nums[l++], nums[r--]);
            if (nums[l] >= pivot) l++;
            if (nums[r] <= pivot) r--;
        }
        swap(nums[left], nums[r]);
        return r;
    }
};
