class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int ans = 0;
        for (string &operation : operations) {
            if (operation[1] == '+') ++ans;
            else --ans;
        }
        return ans;
    }
};
