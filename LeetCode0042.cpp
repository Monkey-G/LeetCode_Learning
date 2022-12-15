class Solution01 {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int ans = 0;
        if (n < 3) return ans;
        int l1 = 0, r1 = 1, l2 = n-2, r2 = n-1;
        //如果一直找不到r1，那就证明最高塔左边是没有雨水的；同理，一直找不到l2证明最高塔右边是没有雨水的
        while (!height[l1]) ++l1; while (!height[r2]) --r2; r1 = l1+1; l2 = r2-1;
        if (l1 >= r2-1) return ans;
        int begin = l1, end = r2;
        int left_cnt = 0, right_cnt = 0;
        while (r1 <= end) {
            if (height[r1] >= height[l1]) {ans += left_cnt; left_cnt = 0; l1 = r1;}
            else left_cnt += height[l1]-height[r1];
            ++r1;
        }
        while (l2 >= l1) {
            if (height[l2] >= height[r2]) {ans += right_cnt; right_cnt = 0; r2 = l2;}
            else right_cnt += height[r2]-height[l2];
            --l2;
        }
        return ans;
    }
};
