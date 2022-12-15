class Solution01 {//自己写的四指针
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



class Solution02 {//数组实现
public:
    int trap(vector<int>& height) {
        int res = 0;
        int l[height.size()];
        int r[height.size()];
        l[0]=0;
        r[height.size()-1]=0;
        for(int i=1;i<height.size()-1;i++){
            l[i] = l[i-1]>height[i-1] ? l[i-1] : height[i-1];
        }
        for(int i=height.size()-2;i>=0;i--){
            r[i] = r[i+1]>height[i+1] ? r[i+1] : height[i+1];
        }
        for(int i=1;i<height.size()-1;i++){
            int min = l[i]>r[i] ? r[i] : l[i];
            if(min>height[i]){
                res+=(min-height[i]);
            }
        }
        return res;
    }

};


class Solution03 {//官方单调栈
public:
    int trap(vector<int>& height) {
        int ans = 0;
        stack<int> stk;
        int n = height.size();
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && height[i] > height[stk.top()]) {
                int top = stk.top();
                stk.pop();
                if (stk.empty()) {
                    break;
                }
                int left = stk.top();
                int currWidth = i - left - 1;
                int currHeight = min(height[left], height[i]) - height[top];
                ans += currWidth * currHeight;
            }
            stk.push(i);
        }
        return ans;
    }
};


class Solution04 {//官方动态规划
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) {
            return 0;
        }
        vector<int> leftMax(n);
        leftMax[0] = height[0];
        for (int i = 1; i < n; ++i) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }

        vector<int> rightMax(n);
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += min(leftMax[i], rightMax[i]) - height[i];
        }
        return ans;
    }
};
