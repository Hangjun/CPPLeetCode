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
        // slope->frequency
        unordered_map<float, int> ht;
        int res = 2;
        for (int i = 0; i < points.size(); i++) {
            ht.clear();
            int dup = 1;
            // no slope = INT_MIN; used to handle all dups or empty points case
            ht[INT_MIN] = 0; 
            for (int j = 0; j < points.size(); j++) {
                if (j == i) continue;
                if (points[j].x == points[i].x && points[j].y == points[i].y) {
                    dup++;
                    continue;
                }
                int dx = points[j].x - points[i].x;
                int dy = points[j].y - points[i].y;
                float slope = (dx == 0) ? INT_MAX : (float)dy/dx;
                ht[slope]++;
            }
            unordered_map<float, int>::iterator it;
            for (it = ht.begin(); it != ht.end(); it++) {
                res = max(res, it->second + dup);
            }
        }
        return res;
    }
};
