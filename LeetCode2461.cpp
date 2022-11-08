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

class Solution03 {//参考网友解改进的自己的解，注意sum的计算一定不要每次都重新来而是滑动进行，以减少计算规模
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        //这是一个显然的滑动窗口的问题，而且由于不能重复数，那就意味着有查表的需要，如果是使用vector索引必须从头起效率很低，因此该用哈希表
        int n = nums.size();
        unordered_map<int, int> nums_map;//哈希表
        long long ans = 0, sum = 0;
        int l = 0, r = 0;//滑动窗口的左右端索引

        while (r < n){
            if (l > n-k) break;//左索引大于n-k时，子数列长度一定不足k
            sum += nums[r]; ++nums_map[nums[r]];
            while (nums_map[nums[r]] > 1 || r-l+1 > k) {sum -= nums[l]; --nums_map[nums[l++]];}//若出现重复数或者长度超限就滑动左窗口，将重复数消出去
            if (r-l+1 == k) ans = max(ans, sum);
            ++r;
        }
        return ans;
    }
};
