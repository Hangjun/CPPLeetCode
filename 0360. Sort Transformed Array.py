"""
Given a sorted array of integers nums and integer values a, b and c. Apply a quadratic function of the form f(x) = ax2 + bx + c to each element x in the array.

The returned array must be in sorted order.

Expected time complexity: O(n)

Example 1:

Input: nums = [-4,-2,2,4], a = 1, b = 3, c = 5
Output: [3,9,15,33]
Example 2:

Input: nums = [-4,-2,2,4], a = -1, b = 3, c = 5
Output: [-23,-5,1,7]
"""

# Binary Search + Merge Sort. Time: O(n), Space: O(1).
class Solution(object):
    def sortTransformedArray(self, nums, a, b, c):
        """
        :type nums: List[int]
        :type a: int
        :type b: int
        :type c: int
        :rtype: List[int]
        """ 
        res = []
        if a == 0:
            for n in nums:
                res.append(self.func(n, a, b, c))
            return res if b > 0 else res[::-1]
        min = b / (-2.0 * a)
        
        # Binary search to find the index for min
        left, right = 0, len(nums)
        while left < right:
            mid = left + (right-left) / 2
            if nums[mid] < min:
                left = mid + 1
            else:
                right = mid
        # merge sort nums[:right] and nums[right:]
        i, j = right-1, right
        while i >= 0 or j < len(nums):
            if i >= 0 and j < len(nums):
                if abs(nums[i] - min) < abs(nums[j] - min):
                    res.append(self.func(nums[i], a, b, c))
                    i -= 1
                else:
                    res.append(self.func(nums[j], a, b, c))
                    j += 1
            elif i >= 0:
                while i >= 0:
                    res.append(self.func(nums[i], a, b, c))
                    i -= 1
            else:
                while j < len(nums):
                    res.append(self.func(nums[j], a, b, c))
                    j += 1
        return res if a > 0 else res[::-1]
    
    def func(self, num, a, b, c):
        return a * num * num + b * num + c
