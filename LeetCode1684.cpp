class Solution01 {//字典查找法
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int ans = 0;
        for (auto&& ch : allowed) allowed_dictionary[ch];//制作字典
        for (auto&& word : words){
            ans += check_identity(word);
        }
        return ans;
    }

private:
    unordered_map<char, int> allowed_dictionary;
    inline int check_identity(const string &word){
        bool return_1 = true;
        //只有word中存在字典中没有的字符时，return_1才会变为false
        for (auto&& word_ch : word) {
            if (!allowed_dictionary.count(word_ch)) {return_1 = false; break;}
        }
        return return_1 ? 1 : 0;
    }
};

class Solution02 {//按位或
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int mask = 0;
        for (auto c : allowed) {
            mask |= 1 << (c - 'a');
        }
        int res = 0;
        for (auto &&word : words) {
            int mask1 = 0;
            for (auto c : word) {
                mask1 |= 1 << (c - 'a');
            }
            if ((mask1 | mask) == mask) {
                res++;
            }
        }
        return res;
    }
};
