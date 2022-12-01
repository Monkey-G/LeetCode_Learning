#define FOR(i, m, n) for (int i = m; i <n; ++i)

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {//暴力解
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.size();
        vector<int> ans(n, 0);
        vector<int> ball_indexs;
        FOR (i, 0, n) if (boxes[i] == '1') ball_indexs.push_back(i);
        int m = ball_indexs.size();
        FOR (i, 0, n) FOR (j, 0, m) ans[i] += abs(ball_indexs[j] - i);
        return ans;
    }
};


#define FOR(i, m, n) for (int i = m; i <n; ++i)

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution02 {//根据上一个盒子的操作数推下一个盒子的操作数
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.size();
        vector<int> ans(n, 0);
        vector<int> ball_indexs;//一定是单调递增的
        FOR (i, 0, n) if (boxes[i] == '1') ball_indexs.push_back(i);
        int m = ball_indexs.size(), cnt = 0;
        if (m == 0) return ans;
        FOR (i, 0, m) ans[0] += ball_indexs[i];
        FOR (i, 1, n) {
            if (i <=  ball_indexs[min(m-1, cnt)]) ans[i] = ans[i-1] - (m-2*cnt);
            else {if (cnt < m) ++cnt; ans[i] = ans[i-1] - (m-2*cnt);}
        }
        cout << cnt;
        return ans;
    }
};
