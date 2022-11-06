class Solution01 {//自己写的垃圾代码
public:
    int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
        unordered_map<string, int> dictionary = {{"type", 0}, {"color", 1}, {"name", 2}};
        int result = 0, index = dictionary[ruleKey];

        for (auto && item : items)
        if (item[index] == ruleValue)
        result++;

        return result;
    }
};

class Solution02 {//神仙网友写的超简便代码
public:
    int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
        int idx = ruleKey == "type" ? 0 : ruleKey == "color" ? 1 : 2;
        return count_if(items.begin(), items.end(), [&](auto strs) { return strs[idx] == ruleValue; });
        //[&]表示以引用的方式传递参数
    }
};
