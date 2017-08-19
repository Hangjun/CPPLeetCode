/*
Given m arrays, and each array is sorted in ascending order. Now you can pick up two integers from two different arrays (each array picks one) and calculate the distance. We define the distance between two integers a and b to be their absolute difference |a-b|. Your task is to find the maximum distance.

Example 1:
Input: 
[[1,2,3],
 [4,5],
 [1,2,3]]
Output: 4
Explanation: 
One way to reach the maximum distance 4 is to pick 1 in the first or third array and pick 5 in the second array.
Note:
Each given array will have at least 1 number. There will be at least two non-empty arrays.
The total number of the integers in all the m arrays will be in the range of [2, 10000].
The integers in the m arrays will be in the range of [-10000, 10000].
*/

/*
Solution:
As discussed already, in order to find out the maximum distance between any two arrays, we need not compare every element of the arrays, since the arrays are already sorted. Thus, we can consider only the extreme points in the arrays to do the distance calculations.

Further, the two points being considered for the distance calculation should not both belong to the same array. Thus, for arrays aa and bb currently chosen, we can just find the maximum out of a[n-1]-b[0] and b[m-1]-a[0] to find the larger distance. Here, nn and mm refer to the lengths of arrays aa and bb respectively.

But, we need not compare all the array pairs possible to find the maximum distance. Instead, we can keep on traversing over the arrays in the listlist and keep a track of the maximum distance found so far.

To do so, we keep a track of the element with minimum value(min\_valmin_val) and the one with maximum value(max\_valmax_val) found so far. Thus, now these extreme values can be treated as if they represent the extreme points of a cumulative array of all the arrays that have been considered till now.

For every new array, aa considered, we find the distance a[n-1]-min\_vala[n−1]−min_val and max\_val - a[0]max_val−a[0] to compete with the maximum distance found so far. Here, nn refers to the number of elements in the current array, aa. Further, we need to note that the maximum distance found till now needs not always be contributed by the end points of the distance being max\_valmax_val and min\_valmin_val.

But, such points could help in maximizing the distance in the future. Thus, we need to keep track of these maximum and minimum values along with the maximum distance found so far for future calculations. But, in general, the final maximum distance found will always be determined by one of these extreme values, max\_valmax_val and min\_valmin_val, or in some cases, by both of them.
*/
