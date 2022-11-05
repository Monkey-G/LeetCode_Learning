class Solution {
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
