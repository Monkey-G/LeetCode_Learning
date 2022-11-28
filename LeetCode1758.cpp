#define FOR(i, n) for (int i = 0; i < n; ++i)

class Solution01 {
public:
    int minOperations(string s) {
        int n = s.size();
        int ans = 0, cnt1 = 0, cnt2 = 0;
        char ch;
        FOR (i, n) {
            if (i % 2 == 0) ch = '1';
            else ch = '0';
            if (s[i] != ch) ++cnt1;
        }
        FOR (i, n) {
            if (i % 2 == 0) ch = '0';
            else ch = '1';
            if (s[i] != ch) ++cnt2;
        }
        ans = min(cnt1, cnt2);
        return ans;
    }
};

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
