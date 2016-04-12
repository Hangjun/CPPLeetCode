/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // reverse scan array to locate the first out-of-order pair
        int len = nums.size();
        if (len == 0 || len == 1) return;
        int i = len - 1; 
        while (i > 0) {
            if (nums[i-1] < nums[i]) {
                int j = len-1;
                while (nums[j] <= nums[i-1]) {j--;}
                //now nums[j] > nums[i-1], swap nums[i-1] with nums[j]
                int tmp = nums[i-1];
                nums[i-1] = nums[j];
                nums[j] = tmp;
                //reverse nums[i, ..., len-1]
                reverseArray(nums, i, len-1);
                return;
            } else
                i--;
        }
        //i == 0 now
        reverseArray(nums, 0, len-1);
    }
    
    void reverseArray(vector<int>& nums, int left, int right) {
        int len = nums.size();
        if (len == 0 || len == 1)
            return;
        int begin = left % len, end = right % len;
        while (begin < end) {
            int tmp = nums[end];
            nums[end] = nums[begin];
            nums[begin] = tmp;
            begin++;
            end--;
        }
    }
};
