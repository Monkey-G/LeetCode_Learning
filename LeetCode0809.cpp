class Solution01 {//自己的解
public:
    int expressiveWords(string s, vector<string>& words) {
        int ans = 0;
        int n = s.size();
        for (string &word : words) {
            int m = word.size();
            if (m > n) continue;
            int s_l = 0, s_r = 0, word_l = 0, word_r = 0;
            while (s_r < n && word_r < m) {
                if (s[s_l] != word[word_l]) break;
                char check_ch = s[s_l];
                while (s_r < n) {if (s[s_r] == check_ch) ++s_r; else break;}
                while (word_r < m) {if (word[word_r] == check_ch) ++word_r; else break;}
                //cout << s_l << " " << s_r << " " << word_l << " " << word_r << endl;
                if (s_r-s_l == word_r-word_l || (s_r-s_l > word_r-word_l && s_r-s_l >= 3)) {s_l = s_r; word_l = word_r;}
                else break;
            }
            if (s_l == n && word_l == m) ++ans;
            //cout << ans << endl;
        }
        return ans;
    }
};

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();



class Solution02 {// 网友解更快一点
public:
    int expressiveWords(string s, vector<string>& words) {
        int ans = 0;
        for(string &w : words)ans+=check(s,w);
        return ans;
    }
    
    bool check(string &s, string &w) {
        if (w.size() > s.size() || s[0] != w[0]) return false;  // 长度不匹配或第一个字符不同
        int i = 0, j = 0, len1 = w.size(), len2 = s.size();
        while (j < len2) {  // 字符串s遍历结束终止
            if (w[i] == s[j]) i++, j++;  // 两指针指向字符相同，同时向后移动
            else {  // 统计j指向位置相同字符的个数是否大于等于3
                int k = j, cnt = 1;
                while (k > 0 && s[k] == s[k - 1]) k--, cnt++;
                k = j;
                while (k < len2 - 1 && s[k] == s[k + 1]) k++, cnt++;
                if (cnt < 3) return false;  // 个数小于3, 不能通过扩充得到
                j = k + 1;  // 个数大于等于3, 从下一个新的字符开始匹配
                if (w[i] != s[j]) return false; // 新的字符也匹配失败, 返回false
            }
        }
        return i == len1;   // 如果最后w遍历到末尾， 说明匹配成功
    }

};

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
