//参考了官方的动态规划思路和矩阵法自己写的代码
using LL = long long;

#define REP(i, n) for (LL i = 0; i < n; ++i)

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

constexpr LL mod = 1e9 + 7;

class Solution01 {
public:
    int numTilings(int n) {
        vector<vector<LL>> state_transform_matrix = {
            {0, 0, 0, 1},
            {1, 0, 1, 0},
            {1, 1, 0, 0},
            {1, 1, 1, 1}
        };
        vector<vector<LL>> result_matrix = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        while (n) {
            if (n & 1) {
                result_matrix = matrix_multiply(result_matrix, state_transform_matrix);
            }
            state_transform_matrix = matrix_multiply(state_transform_matrix, state_transform_matrix);
            n >>= 1;
        }
        return result_matrix[3][3];
    }

private:
    vector<vector<LL>> matrix_multiply (const vector<vector<LL>> &matrix1, const vector<vector<LL>> &matrix2) {
        int m = matrix1.size(), p = matrix2.size(), n = matrix2[0].size();
        vector<vector<LL>> matrix_res(m, vector<LL>(n));//矩阵乘法所得矩阵
        REP(i, m) REP(j, n) REP(k, p) matrix_res[i][j] = (matrix_res[i][j] + matrix1[i][k] * matrix2[k][j]) % mod;
        return matrix_res;
    }
};


//根据矩阵推出函数关系来制表查表法
using LL = long long;

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

constexpr LL MOD = 1e9 + 7;
LL f[1001];
int init = []() {
    f[0] = f[1] = 1;
    f[2] = 2;
    for (int i = 3; i <= 1000; ++i)
        f[i] = (f[i - 1] * 2 + f[i - 3]) % MOD;
    return 0;
}();

class Solution02 {
public:
    int numTilings(int n) {
        return f[n];
    }
};

//官方解，使用哈希表记录值实现动态规划
using LL = long long;

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

constexpr LL mod = 1e9 + 7;

class Solution03 {
public:
    int numTilings(int n) {
        vector<vector<LL>> dp(n + 1, vector<LL>(4));
        dp[0][3] = 1;
        for (int i = 1; i <= n; i++) {
            dp[i][0] = dp[i - 1][3];
            dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % mod;
            dp[i][2] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
            dp[i][3] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][3]) % mod;
        }
        return dp[n][3];
    }
};
