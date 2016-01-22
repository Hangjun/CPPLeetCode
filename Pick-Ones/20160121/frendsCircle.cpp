/*
(A, B)，(B, C)是朋友，那么(A, C)也是朋友。自己跟自己也是朋友输入是一个matrix, Y代表是朋友，N代表不是。比方说：
YYNY
YYNY
NNYN
YYNY
返回2
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int find(vector<int> &parent,  int t) {
    if (t != parent[t]) {
        // path compression from t --> ultimate parent of t
        parent[t] = find(parent, parent[t]);
    }
    return parent[t];
}

void unite(vector<int> &parent, int t, int nt) {
    int pt = find(parent, t);
    int pnt = find(parent, nt);
    if (pt != pnt) {
        parent[pt] = min(pt, pnt);
        parent[pnt] = min(pt, pnt);
    }
}

int friendsCircle(vector<string> &matrix) {
    int n = matrix.size();
    vector<vector<char>> friends(n, vector<char>(n));
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            friends[i][j] = matrix[i][j];
        }
    }
    vector<int> parent(n);
    // initialize parent of person i to be i itself
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (friends[i][j] == 'Y') {
                // merge i's circle with j's circle
                unite(parent, i, j);
            }
        }
    }
    
    // count the number of friends circles
    unordered_set<int> count;
    for (int i = 0; i < n; i++) {
        count.insert(find(parent, i));
    }
    return count.size();
}

int main() {
	vector<string> matrix;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
	    string s;
	    cin >> s;
	    matrix.push_back(s);
	}
	cout << friendsCircle(matrix) << endl;
	return 0;
}

