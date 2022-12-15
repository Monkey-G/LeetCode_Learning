#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {
public:
    bool checkXMatrix(vector<vector<int>>& grid) {
        bool ans = true;
        int n = grid.size();
        FOR (i, 0, n) {
            if (grid[i][i] == 0 || grid[i][n-1-i] == 0) {ans = false; break;}
            FOR (j, 0, n) {
                if (j == i || j == n-1-i) continue;
                if (grid[i][j] != 0) {ans = false; break;}
            }
            if (!ans) break;
        }
        return ans;
    }
};
