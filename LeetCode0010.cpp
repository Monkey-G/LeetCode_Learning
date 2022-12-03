/*思路：
（1）用动态规划，dq[i][j]为s前i个数和p前j个数的匹配情况
（2）dq[i][j]的取值要分情况讨论：
1. 一般情况
if (p[j-1] != '*') {
    if (islower(p[j-1]) && p[j-1] != s[i-1]) dq[i][j] = false;
    else dq[i][j] = dq[i-1][j-1];//dq[i-1][j-1]应在dq[i][j]前计算出来，下边同理
}
else {//p[j-1] == '*'
    //因为p[j-1]和p[j-2]的组合不匹配任何s[i]的部分，dq[i][j] = dq[i][j-2]
    if (islower(p[j-2]) && p[j-2] != s[i-1]) dq[i][j] = dq[i][j-2];
    //dq[i][j] = dq[i][j-2]即p[j-1]和p[j-2]的组合不匹配任何s[i-1]以回的部分，
    //dq[i][j] = dq[i-1][j]即p[j-1]和p[j-2]的组合匹配s[i-1]以回的一部分，s[i-1]与p[j-2]匹配，所以dq[i][j] = dq[i-1][j]
    else dq[i][j] = dq[i][j-2] || dq[i-1][j];
}
2.边界情况
dq[0][0] = true;dq[0][j] (j!=0) 需要特殊处理
*/

#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dq(m+1, vector<bool>(n+1));
        dq[0][0] = true;
        FOR (i, 0, m+1) {
            FOR (j, 1, n+1) {
                if (p[j-1] != '*') {
                    if (i == 0) {dq[i][j] = false; continue;}
                    if (islower(p[j-1]) && p[j-1] != s[i-1]) dq[i][j] = false;
                    else dq[i][j] = dq[i-1][j-1];//dq[i-1][j-1]应在dq[i][j]前计算出来，下边同理
                }
                else {//p[j-1] == '*'
                    if (i == 0) {dq[i][j] = dq[i][j-2]; continue;}
                    //因为p[j-1]和p[j-2]的组合不匹配任何s[i-1]以回的部分，dq[i][j] = dq[i][j-2]
                    if (islower(p[j-2]) && p[j-2] != s[i-1]) dq[i][j] = dq[i][j-2];
                    //dq[i][j] = dq[i][j-2]即p[j-1]和p[j-2]的组合不匹配任何s[i-1]以回的部分，
                    //dq[i][j] = dq[i-1][j]即p[j-1]和p[j-2]的组合匹配s[i-1]以回的一部分，s[i-1]与p[j-2]匹配，所以dq[i][j] = dq[i-1][j]
                    else dq[i][j] = dq[i][j-2] || dq[i-1][j];
                }
                //cout << dq[i][j] << " ";
            }
            //cout << endl;
        }
        return dq[m][n];
    }
};




class Solution02 {//简单递归
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        
        auto first_match = !s.empty() && (s[0] == p[0] || p[0] == '.');
        
        if (p.length() >= 2 && p[1] == '*') {
            return isMatch(s, p.substr(2)) || (first_match && isMatch(s.substr(1), p));
        } else {
            return first_match && isMatch(s.substr(1), p.substr(1));
        }
    }
};




class Solution03 {//优化递归
public:
    bool isMatch(string s, string p) {
        return isMatch(s.c_str(), p.c_str());
    }
    
    bool isMatch(const char* s, const char* p) {
        if(*p == 0) return *s == 0;
        
        auto first_match = *s && (*s == *p || *p == '.');
        
        if(*(p+1) == '*'){
            return isMatch(s, p+2) || (first_match && isMatch(++s, p));
        }
        else{
            return first_match && isMatch(++s, ++p);
        }
    }
};
