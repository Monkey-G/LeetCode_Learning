class Solution01 {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;
        int ans = 0;
        int l = 1, r = 1;
        while (r < n) {
            if (nums[r] != nums[l-1]) {
                if (r != l) nums[l] = nums[r];
                ++l; ++r;
            }
            else ++r;
        }
        ans = l;
        return ans;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
