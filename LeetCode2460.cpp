class Solution01 {
public:
    vector<int> applyOperations(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;

        for (int i = 0; i < n-1; i++){
            if (nums[i] != nums[i+1]) continue;
            else {nums[i] += nums[i]; nums[i+1] = 0;}
        }//全部操作完

        for (auto&& num : nums)
        if (num) ans.push_back(num);

        while (ans.size() < n)
        ans.push_back(0);

        return ans;
    }
};
