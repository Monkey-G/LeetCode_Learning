#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {//铸币解
public:
    vector<string> removeAnagrams(vector<string>& words) {
        int n = words.size();
        vector<string> ans;
        ans.push_back(words[0]);
        FOR (i, 0, n) {
            if (check(words[i], ans.back())) continue;
            ans.push_back(words[i]);
        }
        return ans;
    }

private:
    inline bool check (const string a, const string b) {
        bool res = true;
        unordered_map<char, int> ch_cnt;
        for (char ch : a) ++ch_cnt[ch];
        for (char ch : b) --ch_cnt[ch];
        FOR (i, 0, 26) if (ch_cnt['a'+i] != 0) {res = false; break;}
        return res;
    }
};


class Solution02 {//官方解，一样的思路，但是程序效率高好好学习
public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> res = {words[0]};   // 结果数组
        int n = words.size();
        // 判断两个单词是否为字母异位词
        auto compare = [](const string& word1, const string& word2) -> bool {
            vector<int> freq(26);
            for (char ch: word1) {
                ++freq[ch-'a'];
            }
            for (char ch: word2) {
                --freq[ch-'a'];
            }
            return all_of(freq.begin(), freq.end(), [](int x) { return x == 0; });
        };

        for (int i = 1; i < n; ++i) {
            if (compare(words[i], words[i-1])) {
                continue;
            }
            res.push_back(words[i]);
        }
        return res;
    }
};
