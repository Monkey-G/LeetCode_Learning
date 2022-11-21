/*分析：
（1）这类问题一般是用dfs进行递归遍历或者进行动态规划，但应该注意————无论何种都应该做一个表来计算过往遍历值以减少对同一情况的无意义重复计算
（2）自己写多个超时解就是没有做好表去储存过往遍历值，有大量重复的无意义计算，所以会导致超时
*/

class Solution01 {//自己写的超时解，有大量的无意义重复计算
public:
    double soupServings(int n) {
        distribute(n, n, 0);
        return ans;
    }

private:
    double ans = 0.0;

    inline void distribute(int a, int b, int index) {
        if (a <= 0 && b > 0) {ans += 1.0 / pow(4, index);}//汤A先分配完
        else{
            if (a <= 0 && b <= 0) {ans += 0.5 / pow(4, index);}//汤A、B同时分配完
            else {
                if (a > 0 && b > 0) {
                    distribute(a-100, b, index+1);
                    distribute(a-75, b-25, index+1);
                    distribute(a-50, b-50, index+1);
                    distribute(a-25, b-75, index+1);
                }
            }
        }
    }
};

class Solution02 {//自己写的超时解，有大量的无意义重复计算
public:
    double soupServings(int n) {
        if (n > 4800) return 1.0;
        else return distribute(n, n);;
    }

private:
    inline double distribute(int a, int b) {
        if (a <= 0 && b > 0) return 1.0;//汤A先分配完
        else{
            if (a <= 0 && b <= 0) return 0.5;//汤A、B同时分配完
            else if (b <= 0) return 0.0;
        }
        return 0.25*(distribute(a-100, b) + distribute(a-75, b-25) + distribute(a-50, b-50) + distribute(a-25, b-75));
    }
};

/*根据官方的记忆化搜索做的一个解，其实一开始做的递归思想是对的，但是解法过于暴力，无意义的重复计算太多，
应当配一个表把过往的遍历值记录下来，便于多次计算*/

class Solution03 {
public:
    double soupServings(int n) {
        n = ceil((double) n/25);
        if (n > 193) return 1.0;//当n > 4800时，其概率真值与1.00000的差距小于0.5*0.00001
        distribute_map = vector<vector<double>> (n+1, vector<double>(n+1));
        return distribute(n, n);
    }

private:
    vector<vector<double>> distribute_map;

    inline double distribute(int a, int b) {
        if (a <= 0 && b > 0) return 1.0;//汤A先分配完
        else {
            if (a <= 0 && b <= 0) return 0.5;//汤A、B同时分配完
            else if (a > 0 && b <= 0) return 0.0;//汤B先分配完
        }

        if (distribute_map[a][b] > 0.0) return distribute_map[a][b];
        distribute_map[a][b] = 0.25*(distribute(a-4, b) + distribute(a-3, b-1) + distribute(a-2, b-2) + distribute(a-1, b-3));
        return distribute_map[a][b];
    }
};

class Solution04 {//动态规划
public:
    double soupServings(int n) {
        n = ceil((double) n / 25);
        if (n >= 179) {
            return 1.0;
        }
        vector<vector<double>> dp(n + 1, vector<double>(n + 1));
        dp[0][0] = 0.5;
        for (int i = 1; i <= n; i++) {
            dp[0][i] = 1.0;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = (dp[max(0, i - 4)][j] + dp[max(0, i - 3)][max(0, j - 1)] +
                           dp[max(0, i - 2)][max(0, j - 2)] + dp[max(0, i - 1)][max(0, j - 3)]) / 4.0;
            }
        }
        return dp[n][n];
    }
};
