/*思路：
（1）用动态规划
（2）易证dq[i+1][i+1] >= dq[i][i]
*/
using LL = long long;

#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {//自己的超时动态规划，时间复杂度还是偏高，可以参考官解用单调栈来进一步优化
public:
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        int n = boxes.size();
        //dq[i][j]意味着已搬运了前i个箱子，再搬第（i+1）个到第j个箱子所需的最少行程（i <= j），对应在boxes中的索引为i和j-1
        //i == j时意味着不搬箱子
        vector<vector<int>> dq(n+1, vector<int>(n+1, INT_MAX));
        dq[0][0] = 0;//边界情况

        vector<LL> total_weight(n+1, 0);//total_weight[i]表示前i个箱子的总重量
        FOR (i, 1, n+1) total_weight[i] = total_weight[i-1] + boxes[i-1][1];

        int start_port = 0;//记仓库为0
        FOR (i, 1, min(maxBoxes, n)+1) {
            if (total_weight[i]-total_weight[0] > maxWeight) break;
            if (boxes[i-1][0] != start_port) dq[0][i] = dq[0][i-1]+1;
            else dq[0][i] = dq[0][i-1];
            if (start_port == 0) ++dq[0][i];//从仓库出发
            dq[i][i] = dq[0][i];
            start_port = boxes[i-1][0];
        }//把边界情况算出来
        
        FOR (i, 1, n) {
            start_port = 0;
            FOR(j, i+1, min(i+maxBoxes, n)+1) {
                if (total_weight[j]-total_weight[i] > maxWeight) break;
                if (boxes[j-1][0] != start_port) dq[i][j] = dq[i][j-1]+1;
                else dq[i][j] = dq[i][j-1];
                if (start_port == 0) ++dq[i][j];//从仓库出发
                dq[j][j] = min(dq[j][j], dq[i][j]);
                start_port = boxes[j-1][0];
            }
        }
        /*FOR (i, 0, n+1) {
            FOR (j, 0, n+1) {
                cout << dq[i][j] << " ";
            }
            cout << endl;
        }*/
        return dq[n][n];
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution02 {// 官方的动态规划加单调栈
public:
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        int n = boxes.size();
        vector<int> p(n + 1), w(n + 1), neg(n + 1);
        vector<long long> W(n + 1);
        for (int i = 1; i <= n; ++i) {
            p[i] = boxes[i - 1][0];
            w[i] = boxes[i - 1][1];
            if (i > 1) {
                neg[i] = neg[i - 1] + (p[i - 1] != p[i]);
            }
            W[i] = W[i - 1] + w[i];
        }
        
        deque<int> opt = {0};
        vector<int> f(n + 1), g(n + 1);
        
        for (int i = 1; i <= n; ++i) {
            while (i - opt.front() > maxBoxes || W[i] - W[opt.front()] > maxWeight) {
                opt.pop_front();
            }
            
            f[i] = g[opt.front()] + neg[i] + 2;
            
            if (i != n) {
                g[i] = f[i] - neg[i + 1];
                while (!opt.empty() && g[i] <= g[opt.back()]) {
                    opt.pop_back();
                }
                opt.push_back(i);
            }
        }
        
        return f[n];
    }
};


//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
