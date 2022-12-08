#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {//排序+双指针
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        if (nums[0] * 3 > target || n == 3) return nums[0]+nums[1]+nums[2];
        int ans = 30001;
        FOR (i, 0, n-2) {
            if (nums[i]+nums[n-2]+nums[n-1] < target) {ans = nums[i]+nums[n-2]+nums[n-1]; continue;}
            else {
                if (nums[i]+nums[n-2]+nums[n-1] == target) {ans = target; break;}
                else {
                    int l = i+1, r = n-1;
                    while (ans != target && l+1 <= r) {
                        if (abs(nums[i]+nums[l]+nums[r] - target) < abs(ans - target)) ans = nums[i]+nums[l]+nums[r];
                        if (nums[i]+nums[l]+nums[r] < target) ++l;
                        if (nums[i]+nums[l]+nums[r] > target) --r;
                    }
                    if (ans == target) break;
                }
            }
        }
        return ans;
    }
};
