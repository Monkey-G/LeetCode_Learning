#define REP(i, n) for (int i = 0; i < n; ++i)

int __FAST_IO__ = [](){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {//自己做的垃圾解
public:
    string customSortString(string order, string s) {
        int m = order.size();
        unordered_map<char, int> dictionary;
        REP(i, m) dictionary[order[i]] = i+1;//order[0]~order[m-1]在dictionary中对应1~m

        vector<string> s_subvec(m+1, "");//最多就m+1个部分
        for (auto ch : s) {
            if (dictionary[ch]) s_subvec[dictionary[ch]] += ch;
            else s_subvec[m] += ch;
        }

        string ans;
        for (auto s_sub : s_subvec) ans += s_sub;

        return ans;
    }
};
