"""
Given two 1d vectors, implement an iterator to return their elements alternately.

 

Example:

Input:
v1 = [1,2]
v2 = [3,4,5,6] 
Output: [1,3,2,4,5,6]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,3,2,4,5,6].
 

Follow up:

What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question:
The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example:

Input:
[1,2,3]
[4,5,6,7]
[8,9]

Output: [1,4,8,2,5,9,3,6,7].
"""

# The trick is to recycle the iterator by appending it back to the queue after popping one element out.
# Time: O(max(m, n)) for each next() call, Space: O(m+n).
from collections import deque
class ZigzagIterator(object):

    def __init__(self, v1, v2):
        """
        Initialize your data structure here.
        :type v1: List[int]
        :type v2: List[int]
        """
        self.data = deque([(len(v), iter(v)) for v in (v1, v2) if v])

    def next(self):
        """
        :rtype: int
        """
        _len, _iter = self.data.popleft()
        
        # If current list still has element, push it back to the end of the deque
        if _len > 1:
            self.data.append((_len-1, _iter))
        return next(_iter)

    def hasNext(self):
        """
        :rtype: bool
        """
        return self.data
        

# Your ZigzagIterator object will be instantiated and called as such:
# i, v = ZigzagIterator(v1, v2), []
# while i.hasNext(): v.append(i.next())
