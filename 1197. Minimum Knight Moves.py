"""
In an infinite chess board with coordinates from -infinity to +infinity, you have a knight at square [0, 0].

A knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.



Return the minimum number of steps needed to move the knight to the square [x, y].  It is guaranteed the answer exists.

 

Example 1:

Input: x = 2, y = 1
Output: 1
Explanation: [0, 0] → [2, 1]
Example 2:

Input: x = 5, y = 5
Output: 4
Explanation: [0, 0] → [2, 1] → [4, 2] → [3, 4] → [5, 5]
 

Constraints:

|x| + |y| <= 300
"""

# BFS with simple pruning.
from collections import deque
class Solution(object):
    def minKnightMoves(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: int
        """
        moves = [[2, 1], [1, 2], [-1, 2], [-2, 1], [-2, -1], [-1, -2], [1, -2], [2, -1]]
        # search the variant in the first quadrant
        x = abs(x)
        y = abs(y)
        
        queue = deque([(0, 0)])
        visited = set()
        visited.add((0, 0))
        distance = 0
        while queue:
            curSize = len(queue)
            for _ in range(curSize):
                a, b = queue.popleft()
                if a == x and b == y:
                    return distance
                for da, db in moves:
                    na = a + da
                    nb = b + db
                    if (na, nb) not in visited and na >= -1 and nb >= -1:
                        visited.add((na, nb))
                        queue.append((na, nb))
            distance += 1
        return -1
