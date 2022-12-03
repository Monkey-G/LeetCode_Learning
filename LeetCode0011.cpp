class Solution01 {
public:
    int maxArea(vector<int>& height) {
        int ans = 0;
        //双指针，l为容器左壁，r为右壁
        int l = 0, r = height.size()-1;
        while (l < r) {
            ans = max(ans, min(height[l], height[r]) * (r-l));
            if (height[l] >= height[r]) --r; 
            else ++l;
        }
        return ans;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
