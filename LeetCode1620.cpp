class Solution01 {//自己写的垃圾代码，以后在写代码一定要多注意合理使用引用，无论是循环如auto&&和函数时使用引用，都可以大大减少内存占用和运行时间
public:
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        int max_power = 0;
        int ans_x = 0, ans_y = 0;
        int Max_x = -1, Min_x = 51, Max_y = -1, Min_y = 51;

        for (auto&& tower : towers){
            Max_x = max(Max_x, tower[0]);
            Min_x = min(Min_x, tower[0]);
            Max_y = max(Max_y, tower[1]);
            Min_y = min(Min_y, tower[1]);
        }//找出包括所有信号塔的范围（最大信号必定存在于该范围内）

        for (int x = Min_x; x <= Max_x; x++){//算出范围内所有坐标的信号强度，并不断更新最大信号坐标
           for (int y = Min_y; y <= Max_y; y++){
               int power = 0;
               for (auto&& tower : towers){
                   double dist = distance(x, y, tower);
                   if (dist <= radius)
                   power += floor((double)tower[2] / (1 + dist));
               }

               if (power > max_power){
                   max_power = power;
                   ans_x = x;
                   ans_y = y;
               }
           }
        }

        return {ans_x, ans_y};
    }

double distance(const int &x, const int &y, const vector<int> &tower){
        return sqrt((x - tower[0]) * (x - tower[0]) + (y - tower[1]) * (y - tower[1]));
    }
};

class Solution02 {//网友写的神仙代码，不知道为什么比自己要快些，或许是函数那块更快些吧（猜的）
public:
    double funcL(int x1, int y1, int x2, int y2) {
        //if (x1 == x2 && y1 == y2) return 0;
        return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    }
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        int n = towers.size(), ans = 0, ansX=0,ansY=0;
        int x1=INT_MAX,x2=INT_MIN,y1=INT_MAX,y2=INT_MIN;
        for (auto &item : towers) {
            x1=min(x1,item[0]);
            x2=max(x2,item[0]);
            y1=min(y1,item[1]);
            y2=max(y2,item[1]);
        }
        for (int i=x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                int sum = 0;
                for (auto &tow :towers) {
                    double len = funcL(i,j,tow[0],tow[1]);
                    if (len > radius || tow[2] == 0) continue;
                    sum += (tow[2] / (1+len));
                }
                //if (i >= 17)cout << i << " " << j << " " << sum << endl;
                if (sum > ans) {
                    ans = sum;
                    ansX = i;   ansY = j;
                }
            }
        }
        return {ansX,ansY};
    }
};

class Solution03 {//真正神仙写的神级代码，这个我真看不太懂，貌似是先找出一个所谓最优点？然后算最优点的强度再与各个塔点处的强度比较，这样确实计算规模很小，但为什么可以这样？
public:

    double getDistance(int x1, int y1, int x2, int y2){
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }

    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {

        int best = 0;
        int cx = towers[0][0];
        int cy = towers[0][1];
        int sumX = cx;
        int sumY = cy;
        int count = 1;

        for(int i = 1; i < towers.size(); i ++){
            
            double dist = getDistance(towers[i][0], towers[i][1], cx, cy);
            if(dist <= 2 * radius){
                sumX += towers[i][0];
                sumY += towers[i][1];
                count ++;
                cx = sumX / count;
                cy = sumY / count;
            }
            
        }
        for(int i = 0; i < towers.size(); i ++){
            double dist = getDistance(towers[i][0], towers[i][1], cx, cy);
            if(dist <= radius){
                best += floor(towers[i][2] / (1 + dist));
            }
        }

        for(int i = 0; i < towers.size(); i ++){
            int xi = towers[i][0];
            int yi = towers[i][1];
            int signal = 0;
            for(int j = 0; j < towers.size(); j ++){
                double dist = getDistance(towers[j][0], towers[j][1], xi, yi);
                if(dist <= radius){
                    signal += floor(towers[j][2] / (1 + dist));
                }
            }
            if(best > signal){
                continue;
            }
            if(best == signal){
                if(xi > cx || (xi == cx && yi > cy))
                    continue;
            }
            best = signal;
            cx = xi;
            cy = yi;
        }
        if(best == 0) return{0, 0};
        return {cx, cy};

    }
};
