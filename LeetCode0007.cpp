int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

const int t = 1000000000;

class Solution01 {
public:
    int reverse(int x) { 
        if (check_overload(x)) return 0;
        else return get_reverse(x);
    }

private:
    inline bool check_overload (const int &x) {
        bool res = (x == INT_MIN);//默认不是overload的
        int x_abs = abs(x);//INT_MIN的绝对值是它自己本身
        if (x_abs > t) {
            int tmp = INT_MAX;
            int index = 1;
            bool flag = 0;
            while (index <= 9) {
                if (x_abs % 10 > tmp / (int)pow(10, 10-index)) {res = true; break;}
                else {
                    if (x_abs % 10 < tmp / (int)pow(10, 10-index)) break;
                    else {x_abs /= 10; tmp = tmp % (int)pow(10, 10-index); ++index;}
                }
            }
        }
        return res;
    }

    inline int get_reverse (const int &x) {
        bool sign = (x >= 0);
        int x_abs = abs(x);
        int x_reverse = 0;
        while (x_abs != 0) {
            x_reverse *= 10;
            x_reverse += x_abs % 10;
            x_abs /= 10;
        }
        if(sign) return x_reverse;
        else return -x_reverse;
    }
};
