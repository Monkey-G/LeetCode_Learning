class Solution01 {//BFS+BFS
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dirs = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };//四向扩散
        vector<pair<int, int>> island;//储存小岛格子的容器
        queue<pair<int, int>> qu;//操作用容器

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {//从头遍历找到小岛的一格
                    qu.emplace(i, j);
                    grid[i][j] = -1;//将初始小岛格子染色成-1

                    while (!qu.empty()) {//一直找到所有小岛格子
                        auto [x, y] = qu.front();
                        qu.pop();
                        island.emplace_back(x, y);//将上一轮找到的小岛格子存进小岛容器（第一格也是在这步存进去）
                        for (int k = 0; k < 4; k++) {
                            int nx = x + dirs[k][0];
                            int ny = y + dirs[k][1];
                            if (nx >= 0 && ny >= 0 && nx < n && ny < n && grid[nx][ny] == 1) {//本质上是一轮以现有小岛往外扩散一圈，检查这一圈中是否有小岛格子，并存进queue
                                qu.emplace(nx, ny);
                                grid[nx][ny] = -1;
                            }
                        }
                    }//运行完就完成了整个小岛的遍历和储存

                    for (auto&& [x, y] : island) {
                        qu.emplace(x, y);
                    }//把小岛格子存进queue

                    int step = 0;
                    while (!qu.empty()) {
                        int sz = qu.size();
                        for (int i = 0; i < sz; i++) {
                            auto [x, y] = qu.front();
                            qu.pop();
                            for (int k = 0; k < 4; k++) {//本质上是一轮以现有小岛往外扩散一圈，检查这一圈中是否有小岛格子，若有则return；若无将其外一圈水（0）格子存进queue
                                int nx = x + dirs[k][0];
                                int ny = y + dirs[k][1];
                                if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
                                    if (grid[nx][ny] == 0) {
                                        qu.emplace(nx, ny);
                                        grid[nx][ny] = -1;
                                    }
                                    else if (grid[nx][ny] == 1) {
                                        return step;
                                    }
                                }
                            }
                        }
                        step++;
                    }
                }
            }
        }
        return 0;
    }
};

class Solution02 {DFS+BFS
public:
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        std::function<void(int,int)> dfs = [&](int x,int y){
            grid[x][y]=-1;
            for(int i=0;i<4;i++)
            {
                int xx = x+dx[i];
                int yy = y+dy[i];
                if(xx<0 || xx>=n || yy<0 || yy>=n || grid[xx][yy]==0 || grid[xx][yy]==-1) continue;
                dfs(xx,yy);
            }
        };
        int cnt = 0;
        queue<int> q;
        for(int i=0;i<n;i++)for(int j=0;j<n;j++)
        {
            if(grid[i][j]==1)
            {
                if(!cnt)
                {
                    dfs(i,j);
                    cnt++;
                }else
                {
                    q.push(101*i+j);
                }
            }
        }
        int ans = 0;
        while(q.size())
        {
            int size = q.size();
            ans++;
            for(int i=0;i<size;i++)
            {
                int t = q.front();
                q.pop();
                for(int k=0;k<4;k++)
                {
                    int xx = t/101 + dx[k];
                    int yy = t%101 + dy[k];
                    if(xx<0 || xx>=n || yy<0 || yy>=n || grid[xx][yy]==1) continue;
                    
                    if(grid[xx][yy] == -1) return ans-1;

                    grid[xx][yy]=1;
                    q.push(101*xx+yy);
                }

            }
        }

        return ans;

    }
};

class Solution03 {//DFS+BFS
public:
    void dfs(int x, int y, vector<vector<int>>& grid, queue<pair<int, int>>& qu) {
        if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] != 1) {
            return;
        }
        qu.emplace(x, y);
        grid[x][y] = -1;
        dfs(x - 1, y, grid, qu);
        dfs(x + 1, y, grid, qu);
        dfs(x, y - 1, grid, qu);
        dfs(x, y + 1, grid, qu);
    }

    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dirs = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    queue<pair<int, int>> qu;
                    dfs(i, j, grid, qu);
                    int step = 0;
                    while (!qu.empty()) {
                        int sz = qu.size();
                        for (int i = 0; i < sz; i++) {
                            auto [x, y] = qu.front();
                            qu.pop();
                            for (int k = 0; k < 4; k++) {
                                int nx = x + dirs[k][0];
                                int ny = y + dirs[k][1];
                                if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
                                    if (grid[nx][ny] == 0) {
                                        qu.emplace(nx, ny);
                                        grid[nx][ny] = -1;
                                    }
                                    else if (grid[nx][ny] == 1) {
                                        return step;
                                    }
                                }
                            }
                        }
                        step++;
                    }
                }
            }
        }
        return 0;
    }
};
