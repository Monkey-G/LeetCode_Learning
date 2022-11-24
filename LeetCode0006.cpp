#define FOR(i, n) for (int i = 0; i < n; ++i)

class Solution01 {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;

        int n = s.size();
        vector<string> row_str(numRows, "");
        int cycle = ceil((double)n/(numRows-1)); bool flag;//注意(double)不能少
        FOR (i, cycle) {
            if (i % 2 == 0) flag = true;
            else flag = false;
            FOR (j, numRows-1) {
                if (i*(numRows-1) + j == n) break;
                if (flag) row_str[j].push_back(s[i*(numRows-1) + j]);
                if (!flag) row_str[numRows-1-j].push_back(s[i*(numRows-1) + j]);
            }
        }

        string ans = "";
        for (string& str : row_str) ans += str;

        return ans;
    }
};

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();


#define FOR(i, n) for (int i = 0; i < n; ++i)

class Solution02 {
public:
    string convert(string s, int numRows) {//用数组会比vector更快
        if(numRows<2) return s;
        int i=0, flag=-1;
        string res[numRows];
        FOR(j, s.size()) {
            res[i] += s[j];
            if(i == 0 || i == numRows - 1) flag = -flag;
            i += flag;
        }
        string ans="";
        for(int i=0;i<numRows;i++)
            ans += res[i];
        return ans;
    }
};

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
