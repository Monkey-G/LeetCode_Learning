class Solution01 {
public:
    int climbStairs(int n) {
        unordered_map<int, int> dq;//dq[i]意味着上i阶有几种办法
        dq[0] = 1; dq[1] = 1;
        for (int i = 2; i < n+1; ++i) dq[i] = dq[i-1]+dq[i-2];
        return dq[n];
    }
};
