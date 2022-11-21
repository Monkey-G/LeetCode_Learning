/*思路：
（1）由于a,b的最小公倍数为a*b / gcd(a, b), 记为lcm，显然在k*lcm和(k+1)*lcm之间
（不包含k*lcm）有(a+b) / gcd(a, b) - 1个满足题意的数；而每段之间数的排列是固定的
*/
using LL = long long;

const LL mode = 1e9+7;

class Solution01 {//自己的找规律解
public:
    int nthMagicalNumber(int n, int a, int b) {
        LL ans;
        if (a > b) {int tmp = a; a = b; b = tmp;}
        LL lcm = a * b / gcd(a, b), lcm_cnt = (a + b) / gcd(a, b) - 1;
        LL lcm_cycle_cnt = n / lcm_cnt, lcm_index = n % lcm_cnt;

        ans = (lcm * lcm_cycle_cnt) % mode;

        int a_index = 0, b_index = 0;
        while (lcm_index) {//不可能相等
            if (a * (a_index+1) < b * (b_index+1)) ++a_index;
            else ++b_index;
            --lcm_index;
        }

        ans = (max(a * a_index, b * b_index) + ans) % mode;

        return ans;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();


class Solution02 {//官方的容斥原理 + 二分查找
public:
    const int MOD = 1e9 + 7;
    int nthMagicalNumber(int n, int a, int b) {
        long long l = min(a, b);
        long long r = (long long) n * min(a, b);
        int c = lcm(a, b);
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long cnt = mid / a + mid / b - mid / c;
            if (cnt >= n) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return (r + 1) % MOD;
    }
};


class Solution03 {//官方的找规律解
public:
    const int MOD = 1e9 + 7;
    int nthMagicalNumber(int n, int a, int b) {
        int c = lcm(a, b);
        int m = c / a + c / b - 1;
        int r = n % m;
        int res = (long long) c * (n / m) % MOD;
        if (r == 0) {
            return res;
        }
        int addA = a, addB = b;
        for (int i = 0; i <  r - 1; ++i) {
            if (addA < addB) {
                addA += a;
            } else {
                addB += b;
            }
        }
        return (res + min(addA, addB) % MOD) % MOD;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
