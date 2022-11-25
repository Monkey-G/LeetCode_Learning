class Solution {
public:
    int expressiveWords(string s, vector<string>& words) {
        int ans = 0;
        int n = s.size();
        for (string word : words) {
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
