Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.


/* O(n^3) Time, O(n) Space */
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point>& points) {
        if (points.size() <= 2) return points.size();
        // coordinate->frequency
        unordered_map<int, int> htx;
        unordered_map<int, int> hty;
        for (int i = 0; i < points.size(); i++) {
            htx[points[i].x]++;
            hty[points[i].y]++;
        }
        int res = 2; // at least two points
        // first check for points with the same x or y coord
        for (int i = 0; i < points.size(); i++) {
            res = max(res, htx[points[i].x]);
            res = max(res, hty[points[i].y]);
        }
        // for each pair of poines (thus determines a line), check colinearity
        for (int i = 0; i < points.size() - 1; i++) {
            for (int j = i+1; j < points.size(); j++) {
                int dx = points[j].x - points[i].x;
                int dy = points[j].y - points[i].y;
                if (dx == 0 || dy == 0) continue; // already computed in res
                int count = 0;
                // it's ok to not distinguish k from i and j, since we 
                // are taking max(res, count) at the end
                for (int k = 0; k < points.size(); k++) {
                    // compute slope of points[k] with points[j]
                    int tx = points[k].x - points[j].x;
                    int ty = points[k].y - points[j].y;
                    // colinearity iff tx/ty == dx/dy
                    if (tx * dy == dx * ty) count++;
                }
                res = max(res, count);
            }
        }
        return res;
    }
};


We can improve the time complexity to O(n^2):

/* O(n^2) Time, O(n) Space */
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point>& points) {
        if (points.size() <= 2) return points.size();
        int res = 2; // at least two points
        unordered_map<long double, int> ht; // slope->frequency
        for (int i = 0; i < points.size(); i++) {
            // compute the number points on the lines eminating from points[i]
            ht.clear();
            int dup = 1;
            ht[INT_MIN] = 0; // in case all points are the same point
            for (int j = i+1; j < points.size(); j++) {
                int dx = points[j].x - points[i].x;
                int dy = points[j].y - points[i].y;
                if (dx == 0 && dy == 0) {
                    dup++;
                    continue;
                }
                auto slope = (dx == 0) ? INT_MAX : static_cast<long double> (dy) / dx; // increase precision to pass newly added test case
                ht[slope]++;
            }
            for (auto n : ht) {
                res = max(res, n.second+dup);
            }
        }
        
        return res;
    }
};
