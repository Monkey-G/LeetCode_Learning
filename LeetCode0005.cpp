#define FOR(i, m, n) for (int i = m; i < n; ++i)
#define FORR(i, m, n) for (int i = n-1; i >= m; --i)

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution03 {//最终参考官方解自己写的解
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n == 1) return s;
        vector<vector<int>> dq(n, vector<int>(n, 0));//dq[i][j]表示以i点为起点，j点为终点的子串是不是回文子串（对应1和0），0 <= i <= j < n
        int begin_index = 0, length = 1;

        FOR (i, 0, n) ++dq[i][i];

        FOR (j, 0, n) {//求以i开头，以j结尾的最长回文串
            FOR (i, 0, j) {
                if (s[i] != s[j]) continue;
                else {
                    if (j-i < 3) ++dq[i][j];
                    else dq[i][j] = dq[i+1][j-1];//dq[i+1][j-1]先于dq[i][j]确定
                }
                if (dq[i][j] && j-i+1 > length) {begin_index = i; length = j-i+1;}
            }
        }

        /*FOR (i, 0, n) {//求以i开头，以j结尾的最长回文串
            FOR (j, 0, n) {
                cout <<dq[i][j] << " ";
            }
            cout << endl;
        }*/

        return s.substr(begin_index, length);
    }
};




class Solution04 {//网友的神级解
public:
    string longestPalindrome(string s) {
         if (s.empty()) return "";
        if (s.size() == 1) return s;
        int len = s.size(), start = 0, maxLength = 1, left, right;
        for (unsigned int i = 0; i < len && len - i > maxLength / 2;) 
        {
            left = right = i;
            while (right < len - 1 && s[right + 1] == s[right]) ++right;
            i = right + 1;
            while (right < len - 1 && left > 0 && s[right + 1] == s[left - 1]) 
            {
                ++right;
                --left;
            }
            if (maxLength < right - left + 1) 
            {
                start = left;
                maxLength = right - left + 1;
            }
        }
        return s.substr(start, maxLength);
    }
};
