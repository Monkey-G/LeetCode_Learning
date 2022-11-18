int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
} ();

class Solution01 {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string str_0 = strs[0];
        int n = str_0.size();
        string ans;

        int index = 0;
        bool flag = true;
        while (index < n && flag){
            for (string str : strs) {
                if (index >= str.size() || str[index] != str_0[index]) {flag = false; break;}
            }
            if (flag) ans += str_0[index];
            ++index;
        }
        
        return ans;
    }
};
