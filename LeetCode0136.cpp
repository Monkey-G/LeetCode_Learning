class Solution01 {//位运算
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0;
        for (auto &&e: nums) ret ^= e;
        return ret;
    }
};
