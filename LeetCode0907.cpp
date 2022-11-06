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

class Solution02 {//单调栈
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();//数组长度
        vector<int> monoStack;//单调栈
        //以arr[i]为最小元素，left[i]和right[i]的含义分别是
        //以arr[i]为右端点和左端点的子数列数量
        //!!为防止重复计算，左子数列不可以存在与arr[i]相同，右子数列则可以
        vector<int> left(n), right(n);
        long long ans = 0;
        long long mod = 1e9 + 7;
        
        for (int i = 0; i < n; i++){//求左数列
            //monoStack是一定单调递增的，它每个元素所对应的arr[monoStack[x]]也是递增的，
            //每次判断arr[i]的左数列时，都会把monoStack内arr[monoStack[x]]大于等于arr[i]的x删掉。
            //如果while结束后，monoStack是空的，则arr[i]必定小于等于前边的所有数；
            //如果while结束后，monoStack不是空的，则arr[i]必定小于等于monoStack.back()和i之间的所有数，
            //而大于arr[monoStack.back()]。因此我们可以根据monoStack.empty()的结果判断left[i]的大小。
            while (!monoStack.empty() && arr[i] <= arr[monoStack.back()])
            monoStack.pop_back();

            left[i] = i - (monoStack.empty() ? -1 : monoStack.back());
            monoStack.push_back(i);
        }

        monoStack.clear();//必须清空monoStack防止有残值影响求右数列

        for (int i = n-1; i >= 0; i--){//求右数列
            //monoStack是一定单调递减的，而它每个元素所对应的arr[monoStack[x]]是递增的，
            //每次判断arr[i]的右数列时，都会把monoStack内arr[monoStack[x]]大于arr[i]的x删掉。
            //如果while结束后，monoStack是空的，则arr[i]必定小于后边的所有数；
            //如果while结束后，monoStack不是空的，则arr[i]必定小于i和monoStack.back()之间的所有数，
            //而大于等于arr[monoStack.back()]。因此我们可以根据monoStack.empty()的结果判断right[i]的大小。
            while (!monoStack.empty() && arr[i] < arr[monoStack.back()])
            monoStack.pop_back();

            right[i] = (monoStack.empty() ? n : monoStack.back()) - i;
            monoStack.push_back(i);
        }

        for (int i = 0; i < n; i++) {
            ans = (ans + (long long)left[i] * right[i] * arr[i]) % mod; 
        }
        return ans;
    }
};

class Solution03 {//动态规划
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();//数组长度

        stack<int> monoStack;//单调栈
        //dp[i]是指以arr[i]为右端点的子数组的最小值之和
        vector<int> dp(n);
       
        long long ans = 0;
        long long mod = 1e9 + 7;

        for (int i = 0; i < n; i++) {
            //monoStack从后进顺序看单调递增，对应的arr[i]单调递减
            while (!monoStack.empty() && arr[i] < arr[monoStack.top()])
            //把monoStack中元素对应大于arr[i]的都删掉
                monoStack.pop();
            //如果monoStack是空的，则说明arr[i]一定小于前边所有数
            //如果monoStack不是空的，则说明arr[i]小于等于monoStack.top()到i之间的数
            //而arr[i] >= arr[monoStack.top()]
            
            int k = monoStack.empty() ? (i+1) : (i-monoStack.top());
            dp[i] = k*arr[i] + (monoStack.empty() ? 0 : dp[i-k]);//dp[i-k]前边一定已经计算出来了

            monoStack.emplace(i);

            ans = (ans + dp[i]) % mod;
        }
        return ans;
    }
};
