class Solution01 {
public:
    bool checkIfPangram(string sentence) {
        bool ans = false;
        unordered_map<char, int> char_cnt;
        int cnt = 0;
        for (char ch : sentence) {
            ++char_cnt[ch];
            if (char_cnt[ch] == 1) ++cnt;
            if (cnt == 26) {ans = true; break;}
        }
        return ans;
    }
};
