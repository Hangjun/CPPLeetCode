/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.


The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!
*/

/*
Analysis: An element of array can store water if there are higher bars on left and right. We can find amount of water to be 
stored in every element by finding the heights of bars on left and right sides. The idea is to compute amount of water that 
can be stored in every element of array. For example, consider the array {3, 0, 0, 2, 0, 4}, we can store two units of water 
at indexes 1 and 2, and one unit of water at index 2.

A Simple Solution is to traverse every array element and find the highest bars on left and right sides. Take the smaller of 
two heights. The difference between smaller height and height of current element is the amount of water that can be stored in 
this array element. Time complexity of this solution is O(n^2).

An Efficient Solution is to prre-compute highest bar on left and right of every bar in O(n) time. Then use these pre-computed 
values to find the amount of water in every array element.

Time: O(n), Space: O(n). 3 Passes.
*/
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() < 2) return 0;
        int n = height.size();
        int water = 0;
        vector<int> left(n, 0); // left[i] contains height of tallest bar to the left of i'th bar including itself
        vector<int> right(n, 0); // right[i] contains height of tallest bar to the right of i'th bar including itself
        
        left[0] = height[0];
        for (int i = 1; i < n; i++) left[i] = max(left[i-1], height[i]);
        
        right[n-1] = height[n-1];
        for (int j = n-2; j >= 0; j--) right[j] = max(right[j+1], height[j]);
        
        for (int k = 0; k < n; k++)  water += min(left[k], right[k])-height[k];
        return water;
    }
    
};

/*
Analysis: Can we do better than this? It turns out that we do not need to spare O(n) to store the maximum heights to the left and to the right. Instead we can first scan the whole array to find the maximum height. Then we traverse the array the second time. If the current index is less than the maximum element’s index, we only need to know the maximum height to its left, which can be gather while we traverse up to that element. Here is a constant space solution.

Time: O(n), Space: O(1). 2 Passes.
*/
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 2) return 0;
        
        int water = 0;
        int maxIndex = findMaxIndex(height);
        int maxHeight = height[maxIndex];
        int maxLeftHeight = height[0], maxRightHeight = height[n-1];
        for (int i = 1; i <= maxIndex; i++) { // we can skip the first index
            maxLeftHeight = max(maxLeftHeight, height[i]);
            water += min(maxLeftHeight, maxHeight)-height[i];
        }
        for (int j = n-2; j > maxIndex; j--) { // we can skip the last index
            maxRightHeight = max(maxRightHeight, height[j]);
            water += min(maxRightHeight, maxHeight)-height[j];
        }
        return water;
    }
    
    int findMaxIndex(vector<int> &height) {
        int maxHeight = height[0];
        int maxIndex = 0;
        for (int i = 1; i < height.size(); i++) {
            if (height[i] > maxHeight) {
                maxHeight = height[i];
                maxIndex = i;
            }
        }
        return maxIndex;
    }
};

/*
Can we do even better? This problem looks really similar to the Container with Most Water problem, where we used two pointers and performed a single pass to solve. Can we use two pointers and a single pass here as well? Suppose we start from the two ends. We can transform our analysis above to the following implementation:

Time: O(n), Space: O(1). 1 Pass. Colliding two pointers.
*/
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 2) return 0;
        
        int water = 0;
        int left = 0, right = n-1;
        while (left < right) {
            if (height[left] < height[right]) { // can drop water from the left since the right height is a valid right bound
                int tmpLeftHeight = height[left++];
                while (left < right && height[left] <= tmpLeftHeight) { // while tmpLeftHeight is a valid left bound
                    water += tmpLeftHeight-height[left++];
                }
            } else { // can drop water from the right since the left height is a valid left bound
                int tmpRightHeight = height[right--];
                while (left < right && height[right] <= tmpRightHeight) { // while tmpRightHeight is a valid right bound
                    water += tmpRightHeight-height[right--];
                }
            }
        }
        return water;
    }
};

/* 
Remark: the key takeaway of this problem is to note that, we drop water from the smaller height direction within. For each 
iteration, we first identify which side has a smaller heighter, and we can safely pouring water since we know that the other 
side has bigger height and can thus be provide a valid boundary. This realization is critical for the part II of this problem 
(https://leetcode.com/problems/trapping-rain-water-ii/?tab=Description).
*/
