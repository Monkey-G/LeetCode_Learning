/*思路：
（1）显然，对于每一个长度大于1的数组，其再分为任意两个子数组的平均值之和一定比其平均值大，所以最大分数一定是把nums分成k段
（2）那么怎么分k段呢，应该是动态规划，即前边的规划会影响到后边的规划
（3）分k段，本质上就是在nums上选定（k-1）个点，以起终点和这（k-1）个点为每一分段的起终点来进行分割，为了方便运算，应先算出所有前缀和
（4）动态规划最重要的一步是写出状态方程，并联构得出解。
（5）设dq[i][j]为将[0, i-1]范围的数组分为j段所得的平均值最大之和，那么当j等于1的时候直接求平均值就行，当j>1时，我们就不断地尾端分出一段来求最优
（6）状态方程dq[i][j] = max{dq[x][j-1] + sum([x, i-1])/(i-x)}，其中显然1<j<=(x+1)<=i；dq[i][j] = sum([0, i-1])/i，其中j=1
*/

#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {//自己看了一下官方思路写的动态规划解
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> Prefix_Sum(n+1);
        Prefix_Sum[0] = 0.0;//前缀和边界
        FOR (i, 1, n+1) Prefix_Sum[i] = Prefix_Sum[i-1] + (double)nums[i-1];//求出所有前缀和
        
        vector<vector<double>> dq(n+1, vector<double>(k+1));
        FOR (i, 1, n+1) dq[i][1] = Prefix_Sum[i] / (double)i;//分为1段一定为该段的平均值
        FOR (j, 2, k+1) {
            FOR(i, j, n+1) {//i<j没有意义
                dq[i][j] = max_aver(i, j, dq, Prefix_Sum);
            }
        }
        
        /*FOR (j, 0, k+1) {
            FOR(i, j, n+1) {//i<j没有意义
                cout << dq[i][j] << " ";
            }
            cout << endl;
        }*/
        return dq[n][k];
    }

private:
    inline double max_aver(const int &i, const int &j, vector<vector<double>> &dq, vector<double> &Prefix_Sum) {
        double res = 0.0;
        FOR (x, j-1, i) res = max(res, dq[x][j-1] + (Prefix_Sum[i] - Prefix_Sum[x]) / (double)(i-x));
        return res;
    }
};


class Solution01 {//网友解
public:
    
double prolsoa(vector<int>& nums, int k, int index, vector<vector<double>>& dp) {
    if (dp[index][k] != -1) {
        return dp[index][k];
    }
    if (index == nums.size()) {
        dp[index][k] = 0;
        return 0;
    }
    if (k == 0) {
        dp[index][k] = INT_MIN;
        return INT_MIN;
    }
    double sum = 0;
    double val = 0;
    for (int i = index; i < nums.size() - k + 1; i++) {
        sum += nums[i];
        double tmp = sum;
        sum /= (i + 1 - index);
        val = max(val, prolsoa(nums, k - 1, i + 1,dp)+sum);
        sum = tmp;
    }
    dp[index][k] = val;
    return val;
}

double largestSumOfAverages(vector<int> nums, int k) {
    vector<vector<double>> dp(nums.size() + 1, vector<double>(k + 1, -1));
    return prolsoa(nums, k, 0,dp);
}
};
