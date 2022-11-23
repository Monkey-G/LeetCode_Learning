#define FOR(i, n) for (int i = 0; i < n; ++i)

class Solution01 {//自己的解
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        int n = nums1.size();
        unordered_map<int, int> sum_12;
        int ans = 0;

        FOR(i, n) FOR(j, n) ++sum_12[nums1[i] + nums2[j]];
        FOR(i, n) FOR(j, n) ans += sum_12[-nums3[i]-nums4[j]];

        return ans;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
