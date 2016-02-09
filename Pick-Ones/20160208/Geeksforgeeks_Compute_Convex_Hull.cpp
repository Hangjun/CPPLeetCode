/*
Given a set of n points in a plane, compute its convex hull in O(nlogn) time.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

class Point {
public:
    int x;
    int y;
    
    Point(int _x = 0, int _y = 0) {
        x = _x;
        y = _y;
    }
};

Point p0; // global variable used as starting point
enum Orientation {clockwise, counterclockwise, colinear};

int computeOrientation(Point p1, Point p2, Point p3) {
    int val = (p2.y - p1.y) * (p3.x - p2.x) - (p3.y - p2.y) * (p2.x - p1.x);
    if (val < 0) return counterclockwise;
    if (val == 0) return colinear;
    if (val > 0) return clockwise;
}

int dist(Point p, Point q) {
    return (q.y - p.y) * (q.y - p.y) + (q.x - p.x) * (q.x - p.x);
}

int myCompare (const void *vp1, const void *vp2) {
    Point p1 = *(Point *)vp1;
    Point p2 = *(Point *)vp2;
    int o = computeOrientation(p0, p1, p2);
    if (o == colinear) {
        return dist(p0, p1) < dist(p0, p2) ? -1 : 1;
    }
    return o == counterclockwise ? -1 : 1;
}

void swap(vector<Point> &points, int i, int j) {
    Point temp = points[i];
    points[i] = points[j];
    points[j] = temp;
}

Point nextToTop(stack<Point> &st) {
    Point t = st.top();
    st.pop();
    Point nt = st.top();
    st.push(t);
    return nt;
}

vector<Point> convexHull (vector<Point> points) {
    vector<Point> ch;
    if (points.empty()) return ch;
    // find the lower left point as our starting point
    int yMinVal = points[0].y;
    int yminIndex = 0;
    for (int i = 1; i < points.size(); i++) {
        if (points[i].y < yMinVal || points[i].y == yMinVal && points[i].x < points[yminIndex].x) {
            yMinVal = points[i].y;
            yminIndex = i;
        }
    }
    
    swap(points, 0, yminIndex);

    // sort the points in increasing counterclockwise angle w.r.t. points[0], our starting pivot
    // points with the same angle are sorted in increasing distance from points[0]
    p0 = points[0];
    qsort(&points[1], points.size() -1, sizeof(Point), myCompare);
    
    // de-dup points with the same angle
    int m = 1;
    for (int i = 1; i < points.size(); i++) {
        while (i < points.size()-1 && computeOrientation(points[0], points[i], points[i+1]) == colinear) {
            i++;
        }
        points[m++] = points[i];
    }
    
    if (m < 3) return ch;
    
    stack<Point> st;
    st.push(points[0]);
    st.push(points[1]);
    st.push(points[2]);
    
    for (int i = 3; i < m; i++) {
        // if previous point, current point and next point do not form a counterclockwise configuration
        // remove current point
        while (st.size() > 1 && computeOrientation(nextToTop(st), st.top(), points[i]) != counterclockwise) {
            st.pop();
        }
        // otherwise push next point onto the stack
        st.push(points[i]);
    }
    
    while (!st.empty()) {
        ch.push_back(st.top());
        st.pop();
    }
    return ch;
}

int main() {
	Point p1(0,3);
	Point p2(1,1);
	Point p3(2,2);
	Point p4(4,4);
	Point p5(0,0);
	Point p6(1,2);
	Point p7(3,1);
	Point p8(3,3);
	vector<Point> points;
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	points.push_back(p5);
	points.push_back(p6);
	points.push_back(p7);
	points.push_back(p8);
    vector<Point> ch = convexHull(points);
    for (int i = 0; i < ch.size(); i++) {
        cout << ch[i].x << ", " << ch[i].y << endl;
    }
	return 0;
}
