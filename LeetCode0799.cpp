/*分析：（by monkey_sakura）
（1）首先，我先从第一层开始遍历，计算该层每个杯子从上一层继承得来的酒，减去自身容量若有多余向下左右两杯分
（第1层假设从第0层继承poured杯）
（2）01为三角形遍历，所有酒杯都遍历；02为菱形遍历，只会遍历倒酒数对应的有可能存在酒的酒杯（03是小改进）；04为网友提供的改进三角形遍历；05为根据04做的改进菱形遍历
*/


/*思路：（by monkey_sakura）
（1）首先，我先从第一层开始遍历，计算该层每个杯子从上一层继承得来的酒，减去自身容量若有多余向下左右两杯分
（第1层假设从第0层继承poured杯）
*/
#define FOR(i, n) for (int i = 0; i < n; ++i)

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
} ();

class Solution01 {自己写的三角形遍历，所有酒杯都遍历
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<vector<double>> pour_map(101, vector<double>(101, 0.0));
        int index = 0;
        pour_map[0][0] = (double)poured;
        while (index < 100) {//倒酒
            FOR (i, index+1) {
                if (pour_map[index][i] > 1.0) {
                    pour_map[index+1][i] += (pour_map[index][i] - 1.0) / 2.0; 
                    pour_map[index+1][i+1] += (pour_map[index][i] - 1.0) / 2.0;
                    pour_map[index][i] = 1.0;
                }
            }
            ++index;
        }
        return pour_map[query_row][query_glass];
    }
};


/*思路：（by monkey_sakura）
（1）首先，我先从第一层开始遍历，计算该层每个杯子从上一层继承得来的酒，减去自身容量若有多余向下左右两杯分
（第1层假设从第0层继承poured杯）
*/
#define FOR(i, m, n) for (int i = m; i <= n; ++i)

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
} ();

class Solution02 {自己写的菱形遍历，只会遍历倒酒数对应的有可能存在酒的酒杯
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<vector<double>> pour_map(101, vector<double>(101, 0.0));
        pour_map[0][0] = (double)poured;
        int index = 0;
        int start_point = 0, end_point = 0;
        bool flag = true;
        
        while (index < 100 && flag) {//倒酒
            flag = false;
            FOR (i, start_point, end_point) {
                if (pour_map[index][i] > 1.0) {
                    pour_map[index+1][i] += (pour_map[index][i] - 1.0) / 2.0; 
                    pour_map[index+1][i+1] += (pour_map[index][i] - 1.0) / 2.0;
                    pour_map[index][i] = 1.0;
                    if (!flag) {start_point = i; end_point = index-i; flag = true;}
                }
            }
            ++index;
        }
        return pour_map[query_row][query_glass];
    }
};

/*思路：（by monkey_sakura）
（1）首先，我先从第一层开始遍历，计算该层每个杯子从上一层继承得来的酒，减去自身容量若有多余向下左右两杯分
（第1层假设从第0层继承poured杯）
*/
#define FOR(i, m, n) for (int i = m; i <= n; ++i)

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
} ();

class Solution03 {//基于02的略微改进，对于query_row以下的酒不做处理了
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<vector<double>> pour_map(101, vector<double>(101, 0.0));
        pour_map[0][0] = (double)poured;
        int index = 0;
        int start_point = 0, end_point = 0;
        bool flag = true;
        
        while (index <= query_row && flag) {//倒酒
            flag = false;
            FOR (i, start_point, end_point) {
                if (pour_map[index][i] > 1.0) {
                    pour_map[index+1][i] += (pour_map[index][i] - 1.0) / 2.0; 
                    pour_map[index+1][i+1] += (pour_map[index][i] - 1.0) / 2.0;
                    pour_map[index][i] = 1.0;
                    if (!flag) {start_point = i; end_point = index-i; flag = true;}
                }
            }
            ++index;
        }
        return pour_map[query_row][query_glass];
    }
};

class Solution04 {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        double v[101][101] = {0.0};
        v[0][0] = poured;

        for (int i = 0; i < query_row; ++i) {
            for (int j = 0; j <= i; ++j) {
                double q = (v[i][j] - 1.0 ) / 2.0;
                if (q > 0){
                    v[i+1][j] += q;
                    v[i+1][j+1] += q;
                }
            }
        }
        return min(1.0, v[query_row][query_glass]);
    }
};

/*思路：（by monkey_sakura）
（1）首先，我先从第一层开始遍历，计算该层每个杯子从上一层继承得来的酒，减去自身容量若有多余向下左右两杯分
（第1层假设从第0层继承poured杯）
*/
#define FOR(i, m, n) for (int i = m; i < n; ++i)

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
} ();

class Solution05 {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        double v[101][101] = {0.0};
        v[0][0] = poured;

        int start_point = 0, end_point = 0;
        bool flag = true;

        FOR(i, 0, query_row) {
            flag = false;
            FOR(j, start_point, end_point+1) {
                double q = (v[i][j] - 1.0 ) / 2.0;
                if (q > 0){
                    v[i+1][j] += q;
                    v[i+1][j+1] += q;
                    if (!flag) {start_point = j; end_point = i-j; flag = true;}
                }
            }
        }
        return min(1.0, v[query_row][query_glass]);
    }
};
