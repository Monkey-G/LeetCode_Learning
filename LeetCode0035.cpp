class Solution01 {//自己的解
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        
        if (target > nums[n-1]) return n;
        if (target == nums[n-1]) return n-1;
        if (target <= nums[0]) return 0;

        int ans = 0;
        int begin = 0, end = n-1;
        int mid;
        while (begin+1 < end) {
            mid = (begin+end)/2;
            if (target == nums[mid]) {ans = mid; break;}
            if (target > nums[mid]) begin = mid;
            if (target < nums[mid]) end = mid;
        }
        if (begin+1 == end) ans = end;
        return ans;
    }
};

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution02 {//网友的解，更加简化
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int l=0,r=n-1;
        while(l<=r){
            int mid=l+(r-l)/2;
            if(nums[mid]<target)
                l=mid+1;
            else r=mid-1;
        }
        return l;
    }
};

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
