class Solution01 {//其实这是错的，自己辛辛苦苦写的，却不知道vector是不可以哈希处理的，吸取教训了
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        //哈希表，先把所有0点染色为3，以和1点区别；
        //每次扩散待遍历过的0点染为1，每次扩散待遍历过的1点染为2；
        //已经作为中心点遍历过的0点染色为-1，已经作为中心点遍历过的1点染色为-2；其余1点为0
        unordered_map<vector<int>, int> check_map;
        for (auto&& mine : mines) chech_map[mine] = 3;//先将在gird中为0的点的value染为3
        vector<int> center = {n/2, n/2};
        queue<vector<int>> qu; qu.push(center);//从中点开始遍历
        //对于扩散cnt次的圈，其可能最大k <= n/2 + 1 - cnt；因而对于ans所在圈，ans <= n/2 + 1 - cnt;
        //当出现cnt > n/2 + 1 - ans时，其实已经没有必要再遍历了，因为往后的k都不可能大于ans
        int ans = 0, cnt = 0;//cnt，cnt为已经扩散的次数，cnt最大为n/2

        while (cnt <= n/2 && cnt <= n/2 + 1 - ans){
            int m = qu.size();
            for (int i = 0; i < m; ++i){
                ans = max(ans, get_k_length.(qu.front()));//此时已经染色
                //待遍历的在gird中为1的点染色为2，并把下一轮要遍历的数（包括1点和0点）装进qu
                widen(qu.front());
                qu.pop();
            }
        }
        return ans;
    }

private:
    //从该点向四向延伸找出最大长度，返回k，并在check_map上将该点染色
    inline int get_k_length (const vector<int> &check_point){
        int k = 0;
        int x = check_point[0], y = check_point[1];
        while (x+k <= n-1 && x-k > = 0 && y+k <= n-1 && y-k >= 0){
            if (check_map[{x+k, y}] == 1 || check_map[{x-k, y}] == 1 || check_map[{x, y+k}] == 1 || check_map[{x, y-k}] == 1
            ||check_map[{x+k, y}] == -1 || check_map[{x-k, y}] == -1 || check_map[{x, y+k}] == -1 || check_map[{x, y-k}] == -1
            ||check_map[{x+k, y}] == 3 || check_map[{x-k, y}] == 3 || check_map[{x, y+k}] == 3 || check_map[{x, y-k}] == 3)
            break;
            ++k;
        }
        if (k) check_map[check_point] = -2;//check_point为1点时遍历完毕染色成-2
        else check_map[check_point] = -1;//check_point为0点时遍历完毕染色成-1
        return k;
    }

    inline void widen (const vector<int> &widen_center){
        int x = widen_center[0], y = widen_center[1];
        vector<vector<int>> widen_range = {{max(x-1, 0),max(y-1, 0)}, {x,max(y-1, 0)}, {min(x+1, n-1),max(y-1, 0)},
                                           {max(x-1, 0),y}, {min(x+1, n-1),y},
                                           {max(x-1, 0),min(y+1, n-1)}, {x,min(y+1, n-1)}, {min(x+1, n-1),min(y+1, n-1)}};
        for (auto vec : widen_range){
            //check_map[vec] < 0意味着该坐标是已经作为中心点遍历过的点，不需要操作;
            //check_map[vec] == 1 || check_map[vec] == 2意味着该点已经装进qu，不需要重复操作
            if (check_map[vec] < 0 || check_map[vec] == 1 || check_map[vec] == 2) continue;
            if (check_map[vec] == 3 ) check_map[vec] = 1;
            else check_map[vec] = 2;
            qu.push(vec);
        } 
    }
};


//自己写的傻逼超时解，严重超时，而且占用空间极大，完全不能用，只过了50个算例
struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 

class Solution02 {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        for (auto&& mine : mines) {
            pair<int,int> point_0 = make_pair(mine[0], mine[1]);
            check_map[point_0] = 3;
        }//先将在gird中为0的点的value染为3
        pair<int,int> center = make_pair(n/2, n/2);
        qu.push(center);//从中点开始遍历
        //对于扩散cnt次的圈，其可能最大k <= n/2 + 1 - cnt；因而对于ans所在圈，ans <= n/2 + 1 - cnt;
        //当出现cnt > n/2 + 1 - ans时，其实已经没有必要再遍历了，因为往后的k都不可能大于ans
        int ans = 0, cnt = 0;//cnt，cnt为已经扩散的次数，cnt最大为n/2

        while (cnt <= n/2 && cnt <= n/2 + 1 - ans){
            int m = qu.size();
            for (int i = 0; i < m; ++i){
                ans = max(ans, get_k_length(qu.front(), n));//此时已经染色
                //待遍历的在gird中为1的点染色为2，并把下一轮要遍历的数（包括1点和0点）装进qu
                widen(qu.front(), n);
                qu.pop();
            }
            ++cnt;
        }
        return ans;
    }

private:
    //哈希表，先把所有0点染色为3，以和1点区别；
    //每次扩散待遍历过的0点染为1，每次扩散待遍历过的1点染为2；
    //已经作为中心点遍历过的0点染色为-1，已经作为中心点遍历过的1点染色为-2；其余1点为0
    unordered_map<pair<int,int>, int, hash_pair> check_map;
    queue<pair<int,int>> qu; 

    //从该点向四向延伸找出最大长度，返回k，并在check_map上将该点染色
    inline int get_k_length (const pair<int,int> &check_point, const int size){
        int k = 0;
        int x = check_point.first, y = check_point.second;
        pair<int,int> check_point_left = check_point, check_point_right = check_point,
        check_point_up = check_point, check_point_down = check_point;
        while (x+k <= size-1 && x-k >= 0 && y+k <= size-1 && y-k >= 0){
            check_point_left.first = x-k;check_point_right.first = x+k;
            check_point_up.second = y-k;check_point_down.second = y+k; 
            if (check_map[check_point_left] == 1 || check_map[check_point_left] == -1 ||check_map[check_point_left] == 3 
            || check_map[check_point_right] == 1 || check_map[check_point_right] == -1 ||check_map[check_point_right] == 3
            || check_map[check_point_up] == 1 || check_map[check_point_up] == -1 ||check_map[check_point_up] == 3
            || check_map[check_point_down] == 1 || check_map[check_point_down] == -1 ||check_map[check_point_down] == 3)
            break;
            ++k;
        }
        if (k) check_map[check_point] = -2;//check_point为1点时遍历完毕染色成-2
        else check_map[check_point] = -1;//check_point为0点时遍历完毕染色成-1
        return k;
    }

    inline void widen (const pair<int,int> &widen_center, const int size){
        int x = widen_center.first, y = widen_center.second;
        vector<pair<int,int>> widen_range = {make_pair(max(x-1, 0),max(y-1, 0)), make_pair(x,max(y-1, 0)), 
        make_pair(min(x+1, size-1),max(y-1, 0)), make_pair(max(x-1, 0),y), make_pair(min(x+1, size-1),y), 
        make_pair(max(x-1, 0),min(y+1, size-1)), make_pair(x,min(y+1, size-1)), make_pair(min(x+1, size-1),min(y+1, size-1))};
        for (auto widen_label : widen_range){
            //check_map[widen_label] < 0意味着该坐标是已经作为中心点遍历过的点，不需要操作;
            //check_map[widen_label] == 1 || check_map[vec] == 2意味着该点已经装进qu，不需要重复操作
            if (check_map[widen_label] < 0 || check_map[widen_label] == 1 || check_map[widen_label] == 2) continue;
            if (check_map[widen_label] == 3 ) check_map[widen_label] = 1;
            else check_map[widen_label] = 2;
            qu.push(widen_label);
        } 
    }
};


//自己写的那个从中点开始扩散的思路终于多次改版可以使用了，虽然还是占用内存极大而且运行很慢，但终于过了感动
//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution03 {
public:
    //从该点向四向延伸找出最大长度，返回k，并在check_map上将该点染色
    inline int get_k_length (const int &x, const int &y, vector<vector<int>> &grid, const int &n){
        int k = 0;
        while (x+k <= n-1 && x-k >= 0 && y+k <= n-1 && y-k >= 0){
            int left = x-k, right = x+k, up = y-k, down = y+k;
            if (grid[left][y] == 1 || grid[left][y] == -1 || grid[left][y] == 3 
            || grid[right][y] == 1 || grid[right][y] == -1 || grid[right][y] == 3
            || grid[x][up] == 1 || grid[x][up] == -1 || grid[x][up] == 3
            || grid[x][down] == 1 || grid[x][down] == -1 || grid[x][down] == 3)
            break;
            ++k;
        }
        if (k) grid[x][y] = -2;//check_point为1点时遍历完毕染色成-2
        else grid[x][y] = -1;//check_point为0点时遍历完毕染色成-1
        return k;
    }

    inline void widen (const int &x, const int &y, vector<vector<int>> &grid, queue<int> &qu, const int &n){
        vector<vector<int>> widen_range = {{max(x-1, 0), max(y-1, 0)}, {x, max(y-1, 0)}, {min(x+1, n-1), max(y-1, 0)}, 
                                                     {max(x-1, 0), y},                   {min(x+1, n-1), y}, 
                                          {max(x-1, 0),min(y+1, n-1)}, {x,min(y+1, n-1)}, {min(x+1, n-1),min(y+1, n-1)}};
        for (auto label : widen_range){
            int label_x = label[0], label_y = label[1];
            //grid[label_x][label_y] < 0意味着该坐标是已经作为中心点遍历过的点，不需要操作;
            //grid[label_x][label_y] == 1 || grid[label_x][label_y] == 2意味着该点已经装进qu，不需要重复操作
            if (grid[label_x][label_y] < 0 || grid[label_x][label_y] == 1 || grid[label_x][label_y] == 2) continue;
            if (grid[label_x][label_y] == 3 ) grid[label_x][label_y] = 1;
            else grid[label_x][label_y] = 2;
            qu.push(label_x); qu.push(label_y);
        } 
    }

    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        //哈希表，先把所有点染为0，再把0点染色为3，以和1点区别；
        //每次扩散待遍历过的0点染为1，每次扩散待遍历过的1点染为2；
        //已经作为中心点遍历过的0点染色为-1，已经作为中心点遍历过的1点染色为-2；其余1点为0
        vector<vector<int>> grid(n, vector<int>(n, 0));
        for (auto& mine : mines) grid[mine[0]][mine[1]] = 3;//先将在gird中为0的点的value染为3
        
        int center_x = n/2, center_y = n/2;//从中点开始遍历
        queue<int> qu;//qu用于储存要遍历的点的x和y
        qu.push(center_x);qu.push(center_y);
        //对于扩散cnt次的圈，其可能最大k <= n/2 + 1 - cnt；因而对于ans所在圈，ans <= n/2 + 1 - cnt;
        //当出现cnt > n/2 + 1 - ans时，其实已经没有必要再遍历了，因为往后的k都不可能大于ans
        int ans = 0, cnt = 0;//cnt，cnt为已经扩散的次数，cnt最大为n/2

        while (cnt <= n/2 && cnt <= n/2 + 1 - ans){
            int m = qu.size();
            for (int i = 0; i < m/2; ++i){
                int check_point_x = qu.front(); qu.pop(); 
                int check_point_y = qu.front(); qu.pop();
                ans = max(ans, get_k_length(check_point_x, check_point_y, grid, n));//此时已经染色
                //待遍历的在gird中为1的点染色为2，并把下一轮要遍历的数（包括1点和0点）装进qu
                widen(check_point_x, check_point_y, grid, qu, n);
            }
            ++cnt;
        }
        return ans;
    }
};

//CK写的暴力解，自己懒得写，思路很简单
class Solution04 {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        int ret = 0;
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};
        vector<vector<int>> grid(n, vector<int>(n, 1));
        for(auto &mine: mines){ grid[mine[0]][mine[1]] = 0; }
        // for(int i = 0; i < n; ++i){
        //     for(int j = 0; j < n; ++j){
        //         cout << grid[i][j] << '\t';
        //     }
        //     cout << endl;
        // }
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j] == 0){ continue; }
                int k = 0;
                bool flag = true;
                do{
                    ++k;
                    for(int idx = 0; idx < 4; ++idx){
                        int x = i + dx[idx] * (k - 1), y = j + dy[idx] * (k - 1);
                        if(x <= -1 || x >= n || y <= -1 || y >= n || grid[x][y] == 0){
                            flag = false;
                            break;
                        }
                    }
                }while(flag);
                ret = ret > (k - 1)? ret: (k - 1);
            }
        }
        return ret;
    }
};

//官方的动态规划方法，其实这个很不错，因为他是依次遍历每个点四个方向的最大长度取最小来得到该点对应k，再取最大k
class Solution05 {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        vector<vector<int>> dp(n, vector<int>(n, n));
        unordered_set<int> banned;
        for (auto &&vec : mines) {
            banned.emplace(vec[0] * n + vec[1]);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int count = 0;
            /* left */
            for (int j = 0; j < n; j++) {
                if (banned.count(i * n + j)) {
                    count = 0;
                } else {
                    count++;
                }
                dp[i][j] = min(dp[i][j], count);
            }
            count = 0;
            /* right */ 
            for (int j = n - 1; j >= 0; j--) {
                if (banned.count(i * n + j)) {
                    count = 0;
                } else {
                    count++;
                }
                dp[i][j] = min(dp[i][j], count);
            }
        }
        for (int i = 0; i < n; i++) {
            int count = 0;
            /* up */
            for (int j = 0; j < n; j++) {
                if (banned.count(j * n + i)) {
                    count = 0;
                } else {
                    count++;
                }
                dp[j][i] = min(dp[j][i], count);
            }
            count = 0;
            /* down */
            for (int j = n - 1; j >= 0; j--) {
                if (banned.count(j * n + i)) {
                    count = 0;
                } else {
                    count++;
                }
                dp[j][i] = min(dp[j][i], count);
                ans = max(ans, dp[j][i]);
            }
        }
        return ans;
    }
};

class Solution06 {//网友的一个好解，先是一个双重循环把每点的k求出来，再求最大k
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        vector<vector<int>> grid(n, vector<int>(n, INT_MAX)); // 注意要初始化为无穷大
        for (auto mine : mines) {
            int x = mine[0], y = mine[1];
            grid[x][y] = 0;
        }
        
        for (int i = 0; i < n; i++) {
            int up = 0, down = 0, left = 0, right = 0;
            for (int j = 0, k = n - 1; j < n; j++, k--) {
                left = grid[i][j] == 0 ? 0 : left + 1;
                right = grid[i][k] == 0 ? 0 : right + 1;
                up = grid[j][i] == 0 ? 0 : up + 1;
                down = grid[k][i] == 0 ? 0 : down + 1;
                
                grid[i][j] = min(grid[i][j], left); 
                grid[i][k] = min(grid[i][k], right);
                grid[j][i] = min(grid[j][i], up);
                grid[k][i] = min(grid[k][i], down);
            }
        }
        
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res = max(res, grid[i][j]);
            } 
        }  
        return res;
    }
};

//网友的神级代码
const int N=505,inf=~0u>>2;
struct SegTree{
	int v[N*4],M;
	void clear(int n){
		for (M=1;M-2<n;M<<=1);
		for (int i=0;i<=M*2;++i)v[i]=inf;
	}
	void modify(int x,int key){
		x+=M; v[x]=key;
		for (x>>=1;x;x>>=1)v[x]=min(v[x*2],v[x*2+1]);
	}
	int query(int l,int r){
		l+=M-1;r+=M+1;int ans=inf;
		for (;l^r^1;l>>=1,r>>=1){
			if (~l&1)ans=min(ans,v[l^1]);
			if (r&1)ans=min(ans,v[r^1]);
		}
		return ans;
	}
}up,down;
struct Info{
	int x,v;
};
vector<Info> info[N];
vector<int> row[N],col[N],tmp[N];
class Solution07 {
public:
	int orderOfLargestPlusSign(int n, vector<vector<int>>& a) {
		int m=a.size(),ans=0;
		up.clear(n); down.clear(n);
		for (int i=1;i<=n;++i)tmp[i].clear(),col[i].clear(),col[i].push_back(0);
		for (int i=0;i<m;++i)tmp[++a[i][0]].push_back(++a[i][1]);
		for (int i=1;i<=n;++i)
			for (int x:tmp[i])
				col[x].push_back(i);
		for (int i=1;i<=n;++i)tmp[i].clear(),row[i].clear(),row[i].push_back(0);
		for (int i=0;i<m;++i)tmp[a[i][1]].push_back(a[i][0]);
		for (int i=1;i<=n;++i)
			for (int x:tmp[i])
				row[x].push_back(i);
		
		for (int i=1;i<=n;++i)info[i].clear(),row[i].push_back(n+1),col[i].push_back(n+1);
		for (int i=1;i<=n;++i){
			for (int j=1;j<col[i].size();++j){
				int u=col[i][j-1]+1,v=col[i][j]-1,mid=(u+v)/2;
				if (u>v)continue;
				info[u].push_back({i,u});
				info[mid+1].push_back({i,inf});
				info[mid+1].push_back({i,-v});
				info[v+1].push_back({i,inf});
			}
		}
		
		for (int i=1;i<=n;++i){
			for (auto &t:info[i])
				if (t.v>0)up.modify(t.x,t.v);
				else down.modify(t.x,t.v);
			for (int j=1;j<row[i].size();++j){
				int u=row[i][j-1]+1,v=row[i][j]-1;
				while ((v-u+2)/2>ans){
					int l=u+ans,r=v-ans,res=max(i-up.query(l,r),-down.query(l,r)-i)+1;
					if (res>ans)++ans;
					else break;
				}
			}
		}
		return ans;
	}
};

//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();
