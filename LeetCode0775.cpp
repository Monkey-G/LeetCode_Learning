#define FOR(i, n) for (int i = 0; i < n; ++i)

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {//自己写的解
public:
    bool isIdealPermutation(vector<int>& nums) {
        //当局部倒置和全局倒置的数量相同时，数列的排列情况一定是以下情况：
        //所有数先按0到（n-1）排列，然后所有的倒置情况一定是相邻两个数的倒置，且倒置的两数组合不能相交
        int n = nums.size();
        bool ans = true;

        bool flag = true;
        FOR (i, n-1) {
            if (nums[i] == i) continue;
            if (nums[i] > i+1) {ans = false; break;}
            else {
                if (nums[i] == i+1 && !flag) {ans = false; break;}
                if (nums[i] == i+1 && flag) flag = false;
                else if (nums[i] == i-1 && !flag) flag = true;
            }
        }

        return ans;
    }
};



#define FORR(i, m, n) for (int i = m; i >= n; --i)

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution02 {//网友解帮忙优化版，这个运行更快
public:
    bool isIdealPermutation(vector<int>& nums) {
        int n = nums.size();
        int mi = n;
        FORR(i, n-1, 2){
            mi = min(nums[i],mi);
            if(nums[i-2] > mi) return false;
        }
        return true;
    }
};
