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


class Solution03 {//官方解
public:
    //连线向量转换函数，由于任意不是u->v的情况都不可能与u*n+v相同，这样就可以把一个有指向性的向量转换为一个标量来用作哈希表的key
    int encode(int u, int v, int n) {
        return u * n + v;
    }

    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        //adList[i]意味着点i的邻接表，这一邻接表储存着与点i邻接的每一个点的信息，这一邻接表的每一个元素是一个pair，
        //这个pair的前一个数为两点的距离（用连点数量来表示），后一个数为与点i邻接的点序号
        vector<vector<pair<int, int>>> adList(n);
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1], nodes = edge[2];
            adList[u].emplace_back(v, nodes);
            adList[v].emplace_back(u, nodes);
        }

        unordered_map<int, int> used;//用来储存每个连线上可以到达的连点数量情况，key为u->v向量通过encode函数转换为的标量
        unordered_set<int> visited;//用来储存已经遍历过的点
        int reachableNodes = 0;//可以到达的节点数
        //pq为一个堆栈，每次取出pq的一个数就找出该点的所有未遍历邻接点再按路径大小从小到大放进pq
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, 0);//先把0点即起点存进pq
        while (!pq.empty() && pq.top().first <= maxMoves) {//从0点出发其他点都不能到达，或者存在不能到达的点
            auto [step, u] = pq.top();//从pq的栈顶取出pair，
            pq.pop();//这个点在遍历中，从pq中删除
            if (visited.count(u)) {//u点已经记录过了
                continue;
            }
            visited.emplace(u);//把u点加进visited中，避免重复计算
            reachableNodes++;//可到达的节点加一
            for (auto [v, nodes] : adList[u]) {//遍历所有与u点邻接的点
                //nodes为u、v两点的连点数，step为u点与起点的距离，+1是为了考虑v点，将v点加入pq的前提是v未遍历过
                if (nodes + step + 1 <= maxMoves && !visited.count(v)) {
                    pq.emplace(nodes + step + 1, v);//v与起点距离为nodes + step + 1
                }
                //encode(u, v, n)对应的value为这条边上可以到达的连点数
                used[encode(u, v, n)] = min(nodes, maxMoves - step);
            }
        }

        //由于used储存的向量是成对存在的，即u->v和v->u，那就意味着两个向量所记录的可到达连点数可能是存在重叠的
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1], nodes = edge[2];
            reachableNodes += min(nodes, used[encode(u, v, n)] + used[encode(v, u, n)]);//消除重叠情况
        }
        return reachableNodes;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
