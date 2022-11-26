class Solution01 {//自己的解
public:
    bool check(vector<int>& nums) {
        bool ans = true;
        int cnt = 0, front_num = 0, mid_num = 0;
        for (int num : nums) {
            if (num < front_num) {
                ++cnt;
                if (cnt == 1) mid_num = nums[0];
            } 
            if (cnt == 2 || (cnt == 1 && num > mid_num)) {
                ans = false;
                break;
            }
            front_num = num;
        }
        return ans;
    }
};

class Solution02 {//网友解，快一点
public:
    bool check(vector<int>& nums) {
        int len = nums.size();
        int pre = nums[0];
        for(int i = 1; i < len; ++i)
        {
            if(nums[i] < pre)
            {
                int pree = nums[i];
                for(int j = i + 1; j < len; ++j)
                {
                    if(nums[j] < pree) return false;
                    pree = nums[j];
                }
                for(int j = 0; j < i; ++j)
                {
                    if(nums[j] < pree) return false;
                    pree = nums[j];
                }
                return true;
            }
            pre = nums[i];
        }
        return true;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
