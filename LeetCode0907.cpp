class Solution01 {//暴力解法三重嵌套，严重超时
public:
    int sumSubarrayMins(vector<int>& arr) {
        int min_num = 0;//最小数记录
        auto it_min_num = arr.begin();//最小数对应指针
        int n = arr.size();
        long long ans = 0;
        long long mod = 1e9 + 7;
        
        //arr从头开始，统计包含i对应点的子数组，以该点为子数组的起点
        for (auto it_i = arr.begin(); it_i != arr.end(); ++it_i){
            min_num = *it_i;//每次循环先初始化最小数
            it_min_num = it_i;//每次循环先初始化最小数对应指针

            for (auto it_j = it_i; it_j != arr.end(); ++it_j){//以j对应点为子数组的终点
                for (auto it_k = it_i; it_k != (it_j + 1); ++it_k){//子数组内遍历
                //(it_j + 1)可以这么写是因为arr是int类型的vector
                    //根据情况更新min_sqe和min_num
                    if (min_num == *it_k){
                        it_min_num = it_k;
                    }
                    if (min_num > *it_k){
                        it_min_num = it_k;
                        //min_sqe对应点前边的数只会比最小值大
                        min_num = *min_element(it_min_num, it_k); 
                    }
                }//最后会得出该子数组的最小数
                ans = (ans + (long long)min_num) % mod;
            }
        }
        return ans;
    }
};

