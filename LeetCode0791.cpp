#define REP(i, n) for (int i = 0; i < n; ++i)

int __FAST_IO__ = [](){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {//自己做的垃圾解，先根据order做表再对s排序
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

class Solution02 {//先遍历s对字符进行计数，然后遍历order来对结果进行填充，再遍历一次s对结果进行补充，这个方法可以略优于上一个
public:
    string customSortString(string order, string s) {
        string ans;

        unordered_map<char, int> ch_count;
        for (auto ch : s) ++ch_count[ch];

        for (auto ch : order) if (ch_count[ch] > 0) {ans += string(ch_count[ch], ch); ch_count[ch] = 0;}
        //在第二次遍历s时必须要把遍历的字符对应字典清零
        for (auto ch : s) if (ch_count[ch] > 0) {ans += string(ch_count[ch], ch); ch_count[ch] = 0;}

        return ans;
    }
};
