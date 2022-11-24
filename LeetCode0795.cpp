/*思路：
（1）找出所有大于right的数k，以这些数k1，k2...作为分段点，再找出每一段（不含分段点）在[left, right]内的数如k1分段对应的k1_1，k1_2...，以每一段的k1_1，k1_2...为中点，求出k1_1，k1_2...与左右端点间的数数目（含自己本身而不含端点）之积，再把这些积加起来就是该分段的满足条件子数组个数，再相加就是题目所求了
*/

#define FOR(i, n) for (int i = 0; i < n; ++i)

class Solution01 {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        vector<int> cut_point;//记录分段点
        vector<int> nums_withinlr;//记录在[left, right]内的数
        int n = nums.size();
        int ans = 0;

        //每个cut_point对应每段的终点，在cut_point最后补上一个n，认为是最后一段对应的终点
        FOR (i, n) {
            if (nums[i] > right) {cut_point.push_back(i);  continue;}
            if (nums[i] >= left) nums_withinlr.push_back(i);
        } 
        cut_point.push_back(n);

        int m = nums_withinlr.size();
        int begin = -1, end = cut_point[0];//每段的初始起点为begin（不含该点），第一段的初始起点设为-1
        int index = 0;//遍历nums_withinlr用的索引
        FOR (i, cut_point.size()) {//计算每段满足条件的子数组数
            if (index == m) break;//遍历完了或者一个符合的点都没有

            end = cut_point[i];//该段的终点（不含该点）
            //找出该段的所有符合条件的点然后做该段的子数组计算
            while (nums_withinlr[index] > begin && nums_withinlr[index] < end) {
                ans += (nums_withinlr[index]-begin) * (end-nums_withinlr[index]);
                begin = nums_withinlr[index];
                ++index;
                if (index == m) break;
               
            }//计算完了该段的子数组数
            begin = end;//该段的终点为下一段的初始起点
            //cout << begin << endl;
        }
        return ans;
    }
};

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
