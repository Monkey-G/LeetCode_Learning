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
