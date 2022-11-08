class Solution01 {//自己写的超时解
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> sub_nums;//key为当前子数组的元素，value为对应在nums的下标
        long long ans = 0;

        for (int i = 0; i < n; i++){
            if (sub_nums.size() == k)//如果sub_nums_map是满的就删掉第一个数
            sub_nums.erase(sub_nums.begin());

            auto it_num_i = find(sub_nums.begin(), sub_nums.end(), nums[i]);
            if (it_num_i != sub_nums.end()){//如果sub_nums_map中还存在新进来的数，就把重复的数及之前部分全部删除
                sub_nums.erase(sub_nums.begin(), it_num_i);
                sub_nums.erase(sub_nums.begin());
                sub_nums.push_back(nums[i]);
                continue;
            }
            else 
            sub_nums.push_back(nums[i]);

            long long sum = 0;
            if (sub_nums.size() == k)
            for (auto it = sub_nums.begin(); it != sub_nums.end(); ++it) sum += *it;

            ans = max(ans, sum);
        }

        return ans;
    }
};

class Solution02 {//网友解
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        unordered_map<int,int>h;   //哈希表
        long long res=0,sum=0,l=0,r=0;   //双指针
        int n=nums.size();
        while(r<n)
        {
            h[nums[r]]++;   //右边的数先进入窗口
            sum+=nums[r];

            while(r-l>k-1 || h[nums[r]]>1)   // 后出 ,判断是否需要收缩
            {                                        //这个条件太难找了，可能是研究的少，不太熟练
                h[nums[l]]--;    //窗口内数据要更新
                sum-=nums[l++];
            }
            if(r<n && r-l==k-1) res=max(res,sum);   //如果满足条件的话，就更新结果，根据实际情况确定这一步是在while循环里还是在后面
            r++;   //最后r前进一步，表示滑动窗口右边的数先进去，然后根据条件判断左边的数是否要出去

        }
        return res;
    }
};
