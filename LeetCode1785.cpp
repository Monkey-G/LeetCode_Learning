using LL = long long;

class Solution01 {
public:
    int minElements(vector<int>& nums, int limit, int goal) {
        LL sum = 0;
        for (int num : nums) sum += num;
        if (abs(goal-sum)%limit) return abs(goal-sum)/limit + 1;
        else return abs(goal-sum)/limit;
    }
};
