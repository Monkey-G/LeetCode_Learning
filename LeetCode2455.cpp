class Solution01 {
public:
    int averageValue(vector<int>& nums) {
        int sum_of_manysix = 0;
        int cnt = 0;

        for (auto it = nums.begin(); it != nums.end(); ++it){
            if (!(*it % 6)){
                sum_of_manysix += *it;
                ++cnt;
            }
        }

        
        int ans = cnt ? sum_of_manysix/cnt : 0;

        return ans;
    }
};
