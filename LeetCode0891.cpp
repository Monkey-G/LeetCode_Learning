/*思路分析：（by Monkey_G）
（1）首先，要确定的是，子序列一定是2^n-1个*（不包含空序列）
（2）对于每一个元素来说，包含该元素的序列数一定是2^(n-1)个
（3）要明确一点就是，所有序列的最大数和最小数都是分布到具体各个数上的，因此，遍历每个数，找出其为最大数和最小数的情况即可
（4）当该数为第i小的数时，若该数为最小数，对应有2^(n-i)个序列；若该数为最大数，对应有2^(i-1)个序列。
从而对该数来说其对ans的贡献为 num_i * (2^(i-1) - 2^(n-i))（num_i为该数的值）。
（5）遇到了数组溢出范围的问题，想了一下可以这样，认为2^y = k*mode+b，显然2^(2y) % mode = b^2 % mode.
*/
using LL = long long;

#define FOR(i, n) for (int i = 0; i < n; ++i)

const LL mode = 1e9 + 7;

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {
public:
    int sumSubseqWidths (vector<int>& nums) {
        LL ans = 0;
        sort(nums.begin(), nums.end(), [](int &a, int &b){ return a < b; });//先对数组进行排序
        int n = nums.size();

        FOR(i, n/2) ans = (ans + (nums[n-1-i] - nums[i]) * num_i_coefficient(n-1-i, i)) % mode;

        return ans;
    }

private:
    //该函数主要是为了解决(LL)pow(2, n-1-i) - (LL)pow(2, i)的溢出问题
    //2^30刚好大于mode
    inline LL num_i_coefficient (const int &a, const int &b) {
        LL res = 0;
        int a_tmp = a, b_tmp = b;
        LL a_mode = 1, b_mode = 1;

        while (a_tmp != 0) {
            if (a_tmp > 30) {a_mode = (a_mode<<30) % mode; a_tmp -= 30;}
            else {a_mode = (a_mode<<a_tmp) % mode; break;}
        }

        while (b_tmp != 0) {
            if (b_tmp > 30) {b_mode = (b_mode<<30) % mode; b_tmp -= 30;}
            else {b_mode = (b_mode<<b_tmp) % mode; break;}
        }

        if (a_mode < b_mode) res += a_mode - b_mode + mode;
        else res += a_mode - b_mode;
        return res;
    }
    
};
