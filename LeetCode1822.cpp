class Solution01 {//自己写的垃圾代码
public:
    int arraySign(vector<int>& nums) {
        int result = 1;//默认最后结果初始值为1

        for (auto it = nums.begin(); it != nums.end(); it++){
            if (*it == 0){
                result = 0;
                break;
            }
            
            else
            if (*it < 0)
            result = -result;
        }

        return result;
    }
};
