/*思路：
（1）应该是用dfs递归来做
（2）先做个gird，然后根据edges把存在的点间连点全部染为0（没有就不然gird[i][j]的0的个数是两点间点的个数，
当i=j时，认为点个数为1）；每次走完一个点就把该点染为1，要注意从ui点出发去vi点（ui != vi）gird[ui][ui][0]
须先为1（该方案不行）
（3）基于（2）的失败，应该是先把grid[0][0][0]染色为1，然后每次能走的时候（即两点间存在连点且连点未走完的情况），
在走完之后我们若还有步数且终点仍为0，则这个时候就染为1
（4）在debug过程中把两点相连但不存在连点的情况归到了不相连的情况导致部分该染色的点未染色
（5）出现了Stack overflow 的问题，是在处理两点相连但不存在连点的情况出现了死循环
*/

#define FOR(i, m, n) for (int i = m; i < n; ++i)
#define FORR(i, m, n) for (int i = n-1; i >= m; --i)

class Solution01 {//自己写的超时解，无效计算太多了
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        int ans = 0;
        vector<vector<vector<int>>> grid(n, vector<vector<int>>(n));
        //不同点间连点染色，grid[ui][vi][k]以为ui和vi两点间有k个连点（ui != vi && 0 < k < edge[2]+1），
        //grid[ui][vi][0]grid[ui][vi][edge[2]+1]表示为正向和反向连接的一个连接点
        for (auto edge : edges) { FOR(i, 0, edge[2] + 2) grid[edge[0]][edge[1]].push_back(0); }


        FOR(i, 0, n) grid[i][i].push_back(0);//点自身染色

        grid[0][0][0] = 1;

        move(0, 0, grid, n, maxMoves);

        FOR(i, 0, n) {
            FOR(j, 0, n) {
                if (!grid[i][j].empty()) {
                    if (i == j) { ans += grid[i][j][0]; continue; }
                    int size = grid[i][j].size();
                    FOR(k, 1, size - 1)  ans += grid[i][j][k];
                }
            }
        }

        return ans;
    }

    inline void move(int ui, int vi, vector<vector<vector<int>>>& grid, const int& n, int step) {
        /*cout << "before" << ui << " " << vi << endl;
        FOR(i, 0, n) {
            FOR(j, 0, n) {
                if (!grid[i][j].empty()) {
                    for (auto it = grid[i][j].begin(); it != grid[i][j].end(); ++it) cout << *it << " ";
                    cout << endl;
                }
            }
        }
        cout << step << endl;*/

        if (!step) return;//无路走了
        if (grid[ui][vi].empty() && grid[vi][ui].empty()) return;//两点间没有连接
        int m = max(grid[ui][vi].size(), grid[vi][ui].size());//m >= 2

        if (ui < vi) {//正向开走！！！
            grid[ui][vi][0] = 1;//先把正向连接点染色
            FOR(i, 1, m - 1) {
                if (!grid[ui][vi][i]) grid[ui][vi][i] = 1; 
                --step; 
                if (!step) break;
            }
            if (step) {
                grid[ui][vi][m - 1] = 1; grid[vi][vi][0] = 1; --step;
            }
        }

        if (ui > vi) {//反向开走！！！
            grid[vi][ui][m - 1] = 1;//先把反向连接点染色
            FORR(i, 1, m - 1) {
                if (!grid[vi][ui][i]) grid[vi][ui][i] = 1;
                --step;
                if (!step) break;
            }
            if (step) {
                grid[vi][ui][0] = 1; grid[vi][vi][0] = 1; --step;
            }
        }

        /*cout << "after" << ui << " " << vi << endl;
        FOR(i, 0, n) {
            FOR(j, 0, n) {
                if (!grid[i][j].empty()) {
                    for (auto it = grid[i][j].begin(); it != grid[i][j].end(); ++it) cout << *it << " ";
                    cout << endl;
                }
            }
        }
        cout << step << endl;*/

        if (!step) return;//无路走了
        int index = 0;
        while (index < n) { if (index != vi) move(vi, index, grid, n, step); ++index; }
    }
};



#define FOR(i, m, n) for (int i = m; i < n; ++i)
#define FORR(i, m, n) for (int i = n-1; i >= m; --i)

class Solution02 {//基于上一个超时解优化简化的超时解，优化明显但无效计算依旧很多
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        int ans = 0;
        vector<vector<vector<int>>> grid(n, vector<vector<int>>(n));
        //grid[edge[0]][edge[1]][0]、grid[edge[0]][edge[1]][1]和grid[edge[0]][edge[1]][2]
        //分别表示这两点的连点数、从左侧已经走过的点数和从右侧已经走过的点数;
        for (auto edge : edges) {
            grid[edge[0]][edge[1]].push_back(edge[2]);
            grid[edge[0]][edge[1]].push_back(0);
            grid[edge[0]][edge[1]].push_back(0);
        }
        //grid[i][i][0]和grid[i][i][1]分别表示走过该点所剩的最大step和该点是否被走过;
        FOR(i, 0, n) {
            grid[i][i].push_back(0);
            grid[i][i].push_back(0);
        }

        grid[0][0][1] = 1;

        move(0, 0, grid, n, maxMoves);

        FOR(i, 0, n) FOR(j, 0, n) {
            if (!grid[i][j].empty()) {
                if (i == j) ans += grid[i][j][1];
                else ans += min(grid[i][j][0], grid[i][j][1] + grid[i][j][2]);
            }
        }

        return ans;
    }

    inline void move(int ui, int vi, vector<vector<vector<int>>>& grid, const int& n, int step) {
        /*cout << "before" << ui << " " << vi << endl;
        FOR(i, 0, n) {
            FOR(j, 0, n) {
                if (!grid[i][j].empty()) {
                    for (auto it = grid[i][j].begin(); it != grid[i][j].end(); ++it) cout << *it << " ";
                    cout << endl;
                }
            }
        }
        cout << step << endl;*/
        
        if (step < grid[ui][ui][0]) return;//step不大于走过该点所剩的最大step，没必要再走
        grid[ui][ui][0] = step;//更新走过该点所剩的最大step
        if (grid[ui][vi].empty() && grid[vi][ui].empty()) return;//两点间没有连接，走不了
        
        if (ui < vi) {//左侧开走！！！
            //step不超过已经走过的点数量
            if (step <= grid[ui][vi][1])  return;
            //step超过已经走过的点数量，但不超过连点个数，更新已经走过的点数量
            if (step > grid[ui][vi][1] && step <= grid[ui][vi][0]) { grid[ui][vi][1] = step; return; }
            
            //step == grid[ui][vi][0]+1，证明连点全部走完而且能刚好走到终点那个点
            if (step == grid[ui][vi][0] + 1) { grid[ui][vi][1] = grid[ui][vi][0]; grid[vi][vi][1] = 1; return; }
            if (step > grid[ui][vi][0] + 1) { grid[ui][vi][1] = grid[ui][vi][0]; grid[vi][vi][1] = 1; step -= grid[ui][vi][0] + 1; }
        }
        
        if (ui > vi) {//右侧开走！！！
            //step不超过已经走过的点数量
            if (step <= grid[vi][ui][2]) return;
            //step超过已经走过的点数量，但不超过连点个数，更新已经走过的点数量
            if (step > grid[vi][ui][2] && step <= grid[vi][ui][0]) { grid[vi][ui][2] = step; return; }
            //step == grid[vi][ui][0]+1，证明连点全部走完而且能刚好走到终点那个点
            if (step == grid[vi][ui][0] + 1) { grid[vi][ui][2] = grid[vi][ui][0]; grid[vi][vi][1] = 1; return; }
            if (step > grid[vi][ui][0] + 1) { grid[vi][ui][2] = grid[vi][ui][0]; grid[vi][vi][1] = 1; step -= grid[vi][ui][0] + 1; }
        }

        /*cout << "after" << ui << " " << vi << endl;
        FOR(i, 0, n) {
            FOR(j, 0, n) {
                if (!grid[i][j].empty()) {
                    for (auto it = grid[i][j].begin(); it != grid[i][j].end(); ++it) cout << *it << " ";
                    cout << endl;
                }
            }
        }
        cout << step << endl;*/

        int index = 0;
        while (index < n) { if (index != vi) move(vi, index, grid, n, step); ++index; }
    }
};
