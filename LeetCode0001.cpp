class Solution01 {//暴力解法
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int ix,jx;
        for ( ix = 0; ix < nums.size(); ++ix ){
            for ( jx = ix + 1; jx < nums.size(); ++jx){
                if ( nums[ix] + nums[jx] == target )
                return {ix,jx};
            }
        }
        return {ix,jx};
    }
};

class Solution02 {//hashtable
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};
