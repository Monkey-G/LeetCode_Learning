#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {
public:
    vector<string> generateParenthesis(int n) {
        //dq[i][j]为已经有i位，前边有j个左括号的string集，显然(i+1)/2 <= j <= i
        vector<vector<vector<string>>> dq(2*n+1, vector<vector<string>>(n+1));
        dq[1][1] = {"("};
        FOR (i, 2, 2*n+1) {
            FOR (j, (i+1)/2, min(i+1, n+1)) {
                //显然dq[i-1][j-1], dq[i-1][j]都可能为空
                if (!dq[i-1][j-1].empty()) for (string str : dq[i-1][j-1]) dq[i][j].push_back(str+"(");
                if (!dq[i-1][j].empty()) for (string str : dq[i-1][j]) dq[i][j].push_back(str+")");
            }
        }
        return dq[2*n][n];
    }
};

class Solution02 {//网友解快一点
    void trackBack(vector<string> &ans,string &cur, int open,int close, const int &n){
        if(cur.size() == n*2){
            ans.push_back(cur);
            return;
        }
        if(open < n) {
            cur.push_back('(');
            trackBack(ans,cur,open+1,close,n);
            cur.pop_back();
        }
        if(close < open){
            cur.push_back(')');
            trackBack(ans,cur,open,close+1,n);
            cur.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string cur;
        trackBack(ans,cur,0,0,n);
        return ans;
    }
};
