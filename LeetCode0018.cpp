using LL = long long;

#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        int n = nums.size();
        if (n < 4) return ans;
        sort(nums.begin(), nums.end());
        FOR (i, 0, n-3) {
            if ((LL)nums[i]+nums[i+1]+nums[i+2]+nums[i+3] > target) break;//已经不可能有解了
            if (i > 0 && nums[i] == nums[i-1]) continue;//跳过重复数
            if ((LL)nums[i]+nums[n-3]+nums[n-2]+nums[n-1] < target) continue;//这个i太小了没有解
            FOR (j, i+1, n-2) {
                if ((LL)nums[i]+nums[j]+nums[j+1]+nums[j+2] > target) break;//已经不可能有解了
                if (j > i+1 && nums[j] == nums[j-1]) continue;//跳过重复数
                if ((LL)nums[i]+nums[j]+nums[n-2]+nums[n-1] < target) continue;//这个i太小了没有解
                int l = j+1, r = n-1;
                while (l+1 <= r) {
                    if ((LL)nums[i]+nums[j]+nums[l]+nums[r] < target) {
                        ++l; while (nums[l] == nums[l-1] && l+1 <= r) ++l;
                    }
                    else {
                        if ((LL)nums[i]+nums[j]+nums[l]+nums[r] > target) {
                            --r; while (nums[r] == nums[r+1] && l+1 <= r) --r;
                        }
                        else {
                            ans.push_back({nums[i],nums[j],nums[l],nums[r]}); //cout << i << j << l << r << endl; 
                            --r; while (nums[r] == nums[r+1] && l+1 <= r) --r;
                        }
                    }
                }
            }
        }
        return ans;
    }
};


class Solution02 {//网友解，差不多一样的
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        if(nums.size() < 4){
            return ans;
        }
        for(int i=0;i<n-3;i++){
            if(i > 0 && nums[i] == nums[i-1]){
                continue;
            }
            if((long)nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target){
                break;
            }
            if((long)nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target){
                continue;
            }
            for(int j=i+1;j<n-2;j++){
                if(j > i+1 && nums[j] == nums[j-1]){
                    continue;
                }
                if((long)nums[i] + nums[j] + nums[j+1] + nums[j+2] > target){
                    break;
                }
                if((long)nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target){
                    continue;
                }
                int left = j + 1, right = n - 1;
                while(left < right){
                    long sum = (long)nums[i] + nums[j] + nums[left] + nums[right];
                    if(sum == target){
                        ans.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while(left < right && nums[left] == nums[left+1]){
                            left++;
                        }
                        left++;
                        while(left < right && nums[right] == nums[right-1]){
                            right--;
                        }
                        right--;
                    }
                    else if(sum < target){
                        left++;
                    }
                    else{
                        right--;
                    }

                }
            }
        }
        return ans;
    }
};
