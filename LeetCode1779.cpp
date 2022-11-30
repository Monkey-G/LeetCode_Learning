#define FOR(i, n) for (int i = 0; i < n; ++i)

class Solution {
public:
    int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
        int ans = -1;
        int min_Manhattan = INT_MAX;
        int n = points.size();
        FOR (i, n) {
            if (points[i][0] == x) {
                if (abs(points[i][1] - y) < min_Manhattan) {min_Manhattan = abs(points[i][1] - y); ans = i;}
            }
            if (points[i][1] == y) {
                if (abs(points[i][0] - x) < min_Manhattan) {min_Manhattan = abs(points[i][0] - x); ans = i;}
            }
        }
        return ans;
    }
};

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
