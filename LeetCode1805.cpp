#define FOR(i, n) for (int i = 0; i < n; ++i)

class Solution01 {
public:
    int numDifferentIntegers(string word) {
        int ans = 0;
        unordered_set<string> nstr_set;
        int n = word.size(), index = 0;
        string nstr = "";
        while (index < n) {
            if (islower(word[index])) {
                if (nstr != "") {
                    while (nstr.size() > 1 && nstr[0] == '0') nstr = nstr.substr(1, nstr.size()-1);
                    if (!nstr_set.count(nstr)) {++ans; nstr_set.emplace(nstr);}
                    nstr = "";
                }
                ++index; continue;
            }
            nstr += word[index];
            ++index;
            if (index == n) {
                while (nstr.size() > 1 && nstr[0] == '0') nstr = nstr.substr(1, nstr.size()-1);
                if (!nstr_set.count(nstr)) ++ans; 
            }
        }
        return ans;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
