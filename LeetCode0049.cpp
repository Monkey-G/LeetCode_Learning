#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {//自己的傻逼解
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        unordered_map<string, vector<string>> str_hash;
        FOR (i, 0, strs.size()) {
            unordered_map<char, int> ch_hash;
            for (auto &&ch : strs[i]) ++ch_hash[ch];
            string tmp;
            FOR (j, 0, 26) {char ch = 'a'+j; FOR (k, 0, ch_hash[ch]) tmp += ch;}
            str_hash[tmp].push_back(strs[i]);
        }
        for (auto it = str_hash.begin(); it != str_hash.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};


class Solution02 {//官方排序解
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (string& str: strs) {
            string key = str;
            sort(key.begin(), key.end());
            mp[key].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};



class Solution03 {//官方计数解
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 自定义对 array<int, 26> 类型的哈希函数
        auto arrayHash = [fn = hash<int>{}] (const array<int, 26>& arr) -> size_t {
            return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num) {
                return (acc << 1) ^ fn(num);
            });
        };

        unordered_map<array<int, 26>, vector<string>, decltype(arrayHash)> mp(0, arrayHash);
        for (string& str: strs) {
            array<int, 26> counts{};
            int length = str.length();
            for (int i = 0; i < length; ++i) {
                counts[str[i] - 'a'] ++;
            }
            mp[counts].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};
