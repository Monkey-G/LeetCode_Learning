int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {//自己写的解
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int ans = 0;
        for (string &word : words) {
            if (s.size() == 1) {if (word == s) ++ans;}
            else{
                int index = 0;
                int cnt = 0;
                for (char &ch : word) {
                    index = s.find(ch,index);
                    if (index == string::npos) break;//没找出来
                    else {++cnt; ++index;}
                }  
                if (cnt == word.size()) ++ans;
            }   
        }
        return ans;
    }
};
