/*思路：
（1）易知，每位数字之和最大可能值为45，最小为1，建议一个map_cnt来记录范围内的数的每位之和；
并用相应key存的value不断跟最大值结果ans比较更新按说即可，事件负责度为n(highLimit-lowLimit)
*/
#define FOR(i, m, n) for (int i = m; i <= n; ++i)

class Solution01 {//自己写的解，其实在求各位之和上可以简化优化
public:
    int countBalls(int lowLimit, int highLimit) {
        unordered_map<int, int> map_cnt;
        int ans = 0;
        FOR(i, lowLimit, highLimit) {
            ++map_cnt[num_bit_sum(i)]; 
            if (map_cnt[num_bit_sum(i)] > ans) ans = map_cnt[num_bit_sum(i)];
        }
        return ans;
    }

private:
    inline int num_bit_sum (int num){
        int res = num % 10;
        while (num / 10 != 0) {num = num / 10; res += num % 10;}
        return res;
    }
};

const int maxn = 46;
int func[maxn];

class Solution02 {// 网友解，相比自己写的解主要是在求每个数的各位之和上更加简化优化了
public:
    int countBalls(int lowLimit, int highLimit) {

        memset(func, 0, sizeof(func));

        int ans = -1;

        //计算第一个数各个位置的和
        int key = getTotal(lowLimit);
        func[key]++;

        for(int i = lowLimit + 1; i <= highLimit; i++) {

            key += 1 - (findEndZero(i) * 9);
            func[key]++;
        }

        for(int i = 1; i < maxn; i++){

            ans = max(ans, func[i]);
        }

        return ans;
    }

    //计算各个位置的数值
    int getTotal(int n) {

        int t = 0;

        while (n > 0) {

            t += n % 10;
            n = n / 10;
        }

        return t;
    }

    //找出末尾0的个数
    int findEndZero(int n) {

        int t = 0;
        
        while (n % 10 == 0) {
        
            n = n / 10;
            t++;
        }

        return t;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
