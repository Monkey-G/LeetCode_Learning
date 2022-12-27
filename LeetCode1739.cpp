using LL = long long;

class Solution01 {
public:
    int minimumBoxes(int n) {
        LL m = 0;
        while (m*(m+1)*(m+2)/6 < n) ++m;
        //cout << m << endl;
        int k = 0;
        while (k*(k+1)/2 < n-(m-1)*m*(m+1)/6) ++k;
        //cout << k << endl;
        return m*(m-1)/2+k;
    }
};


class Solution02 {//官方找规律解
public:
    int minimumBoxes(int n) {
        int cur = 1, i = 1, j = 1;
        while (n > cur) {
            n -= cur;
            i++;
            cur += i;
        }
        cur = 1;
        while (n > cur) {
            n -= cur;
            j++;
            cur++;
        }
        return (i - 1) * i / 2 + j;
    }
};


class Solution03 {//官方二分查找法
public:
    int minimumBoxes(int n) {
        int i = 0, j = 0;
        int low = 1, high = min(n, 100000);
        while (low < high) {
            int mid = (low + high) >> 1;
            long long sum = (long long) mid * (mid + 1) * (mid + 2) / 6;
            if (sum >= n) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        i = low;
        n -= (long long) (i - 1) * i * (i + 1) / 6;
        low = 1, high = i;
        while (low < high) {
            int mid = (low + high) >> 1;
            long long sum = (long long) mid * (mid + 1) / 2;
            if (sum >= n) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        j = low;
        return (i - 1) * i / 2 + j;
    }
};


class Solution04 {//官方解方程解
public:
    int g(int x) {
        return (long long) x * (x + 1) * (x + 2) / 6;
    }

    int minimumBoxes(int n) {
        int i = pow(6.0 * n, 1.0 / 3);
        if (g(i) < n) {
            i++;
        }
        n -= g(i - 1);
        int j = ceil(1.0 * (sqrt((long long) 8 * n + 1) - 1) / 2);
        return (i - 1) * i / 2 + j;
    }
};
