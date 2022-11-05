class Solution01 {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long> preSumArr(n+1);//preSumArr[i]的含义是前i个数的前缀和
        preSumArr[0] = 0;
        for (int i = 0; i < n; i++){//求出所有前缀和
            preSumArr[i+1] = preSumArr[i] + nums[i];
        }

        int length = n+1;//初始化认为所求子数组的长度为（n+1），因为length可能的最大长度就为n
        deque<int> qu;//qu的所存数列一定是单调递增的，而且其对应的preSumArr一定也是单调递增的
        for (int i = 0; i <= n; i++){
            long curSum = preSumArr[i];

            while(!qu.empty() && curSum - preSumArr[qu.front()] >= k){
                //qu从头开始一直找到刚刚好符合题意的那个起点（如有），此起点对于该终点是最短的
                //再把这个距离和以往所记录的最短距离进行比较
                length = min(length, i-qu.front());
                qu.pop_front();
            }

            while (!qu.empty() && curSum <= preSumArr[qu.back()])
            //删除比curSum大的preSumArr的相对应下标，保持qu的双重单调性
            qu.pop_back();

            qu.push_back(i);
        }

        return (length == n+1) ? -1 : length;
    }
};


//网友的神仙代码
int init_io = []() {
    cin.tie(nullptr)->sync_with_stdio(false);
    return 0;
}();//这段好像是加速cin和cout的，以后再加以研究

class Solution02 {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        long p[100001];
        int i, len = nums.size();
        p[0] = 0;
        for (i = 0; i < len; i++)
        {
            if (nums[i] >= k) return 1;
            p[i + 1] = p[i] + nums[i];
        }//求出所有前缀和
        int q[100001], ql = 0, qr = 0;
        q[qr++] = 0;
        int r = 0;
        int NO_ANS = 1e9, ans = NO_ANS;
        while (1)
        {
            while (r < len && p[r + 1] - p[q[ql]] < k)//这一阶段ql是不变的，所以q[ql]=q[0]
            {//这段循环的作用是，做一个双重单调递增的单调栈q，从p[0]到p[len-1]一直检查,
            //第i次进栈时，把栈内等于大于p[i-1]的前缀和所对应的下标依次推出直至空栈或者栈内刚好小于p[i-1]的
            //那个前缀和对应下标之前，将p[i-1]的对应下标(i-1)入栈；从而在遍历过程中，栈的第一位一定是目前遍历下的最小前缀和
            //而这些循环持续到超出遍历索引或者找到刚好和目前所遍历最小前缀和匹配的一个前缀和。
                while (qr > ql && p[q[qr - 1]] >= p[r + 1]) qr--;
                q[qr++] = r + 1;
                r++;
            }
            if (r >= len) break;//遍历完毕所有前缀和
            while (p[r + 1] - p[q[ql]] >= k) 
            {//找出该r值对应最大ql，进而得出相应的最小字数列长度
                ans = min(ans, r + 1 - q[ql]);
                ql++;
            }
        }
        return ans == NO_ANS ? -1 : ans;
    }
};
