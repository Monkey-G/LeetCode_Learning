using LL = long long;

#define EFOR(i, m, n) for (int i = m; i <= n; ++i)

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {//自己写的傻逼解
public:
    bool isPalindrome(int x) {
        if (x == 0) return true;
        else
        if (x > 0) {
            int n = log10(x);
            queue<int> qu;
            LL x_reverse = 0;
            EFOR(i, 0, n) x_reverse += ((LL)x % (LL)pow(10, i+1)) / (LL)pow(10, i) * (LL)pow (10, n-i);
            return (LL)x == x_reverse;
        }
        else return false;
    }
};
