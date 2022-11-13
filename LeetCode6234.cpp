//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {//自己写的严重超时解
public:
    int subarrayLCM(vector<int>& nums, int k) {
        int n = nums.size();
        int l = 0, r = 0;//滑动窗口的左右端
        int ans = 0;
        while (r < n){
            if (k % nums[r] && l == r) {++r; l = r; continue;}
            if (k % nums[r] && l != r){//不考虑所截段后续没有k的非约数的情况
                for (int i = l; i < r; ++i){//找出以i为所截段的子数列起点的所有满足最小公倍数为k的子数列数
                    int j = i;
                    while (find_mincomul(i, j, nums) < k && j < r) ++j;
                    ans += r-j;
                }
                ++r; l = r;
            }
            else ++r;
        }
        if (k % nums[n-1] == 0){//存在所截段后续没有k的非约数的情况
            for (int i = l; i < n; ++i){//找出以i为所截段的子数列起点的所有满足最小公倍数为k的子数列数
                int j = i;
                while (j < n && find_mincomul(i, j, nums) < k) ++j;
                ans += r-j;
            }
        }
        return ans;
    }

private:
    //两数之积等于两数最大公约数和最小公倍数之积
    inline int find_maxcodiv(const int &a, const int &b){
        if (a % b == 0) return b;
        else return find_maxcodiv(b, a % b);
    }
    inline int find_mincomul(const int &begin, const int &end, vector<int>& nums){
        int mincomul = nums[begin];
        for (int i = begin; i < end; ++i) mincomul = mincomul*nums[i+1]/find_maxcodiv(mincomul, nums[i+1]);
        return mincomul;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution02 {//自己写的严重超时解优化版，主要是使用了gcd()函数来替代自己写的辗转相除法的函数
public:
    int subarrayLCM(vector<int>& nums, int k) {
        int n = nums.size();
        int l = 0, r = 0;//滑动窗口的左右端
        int ans = 0;
        while (r < n){
            if (k % nums[r] && l == r) {++r; l = r; continue;}
            if (k % nums[r] && l != r){//不考虑所截段后续没有k的非约数的情况
                for (int i = l; i < r; ++i){//找出以i为所截段的子数列起点的所有满足最小公倍数为k的子数列数
                    int j = i;
                    while (find_mincomul(i, j, nums) < k && j < r) ++j;
                    ans += r-j;
                }
                ++r; l = r;
            }
            else ++r;
        }
        if (k % nums[n-1] == 0){//存在所截段后续没有k的非约数的情况
            for (int i = l; i < n; ++i){//找出以i为所截段的子数列起点的所有满足最小公倍数为k的子数列数
                int j = i;
                while (j < n && find_mincomul(i, j, nums) < k) ++j;
                ans += r-j;
            }
        }
        return ans;
    }

private:
    //两数之积等于两数最大公约数和最小公倍数之积
    inline int find_mincomul(const int &begin, const int &end, vector<int>& nums){
        int mincomul = nums[begin];
        for (int i = begin; i < end; ++i) mincomul = mincomul*nums[i+1]/gcd(mincomul, nums[i+1]);
        return mincomul;
    }
};

class Solution03 {//这个网友的思路很好，直接滑动窗口求最小公约数直至子数列都满足情况，其实和自己的思路差不多，但我的太过于复杂而且优化太差
public:
    int subarrayLCM(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            long long l = nums[i];
            for (int j = i; j < n; j++) {
                long long g = gcd(l, nums[j]);
                l = l / g * nums[j];
                if (l == k) ans++;
                // 防止溢出
                else if (l > k) break;
            }
        }
        return ans;
    }
};

#define FOR(i, m, n) for(int i = m; i < n; ++i)

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution04 {//根据网友思路做的自己的解，目前优化最好
public:
    int subarrayLCM(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        FOR(i, 0, n) {//i为滑动窗口的起点，j为滑动窗口的终点
            int subnum_mincomul = nums[i];
            FOR(j, i, n) {
                subnum_mincomul = find_mincomul(subnum_mincomul, nums[j]); 
                if (subnum_mincomul == k) ++ans;
                if (subnum_mincomul > k) break;//这步很关键，不仅防止了溢出，还节省了运行时间
            }
        }
        return ans;
    }

private:
    //两数之积等于两数最大公约数和最小公倍数之积
    inline int find_mincomul(const int &a, const int &b){
        return a * b / gcd(a, b);
    }
};
