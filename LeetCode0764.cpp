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


//自己写的傻逼超时解，我估计是不能跑的
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
