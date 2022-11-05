class Solution01 {//自己写的垃圾解，从头以每个数为末段求其最长字串，再比较得出答案
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        unordered_map<char, vector<int>> string_count;
        int length = 0;
        int start_point = -1;

        for (int i = 0; i < n; i++) {//以string[i]为最末的最长字串
            char char_i = s[i];
            if (!string_count[char_i].empty() && string_count[char_i].back() > start_point) {
                start_point = string_count[char_i].back();//寻找字串起点
            }
            length = max(length, i - start_point);
            string_count[char_i].push_back(i);
        }

        return length;
    }
};

class Solution02 {//自己写的垃圾解，基于01的优化，一个减少了占用的内存空间string_count的value变为int而非 vector<int>；使用auto也更快更简洁
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> string_count;
        int length = 0;
        int index = 1;
        int cut_point = 0;

        for (auto&& ch : s) {
            if (string_count[ch]) cut_point = max(cut_point, string_count[ch]);
            length = max(length, index - cut_point);

            string_count[ch] = index;
            ++index;
        }

        return length;
    }
};

class Solution03 {//网友的神仙代码之一，由于没有用到map，内存占用进一步减少，而且不知道为啥特别快（比我写的快多了），可能是字符串操作会更快
public:
    int lengthOfLongestSubstring(string s) {
        int pos = 0;
        int count = 0;
        if(s == " "){
            return 1;
        }
        string ss;
        for(int i=0;i<s.size();i++){
            pos = ss.find(s[i]);
            if(pos == string::npos){
                ss += s[i];
            } else {
                if(count <= ss.size()){
                    count = ss.size();
                }
                ss.erase(0,pos+1);
                ss += s[i];
            }
        }
        return count > ss.size() ? count : ss.size();
    }
};

class Solution04 {//网友的神仙代码之一，利用ASCII码配合容器运行会更快
public:
    int lengthOfLongestSubstring(string s) {
    vector<int> record(128,-1);//ASCII码，牛逼了我的妈啊
    int ans=0;
    for(int i=0,j=0;i<s.length();i++){
    j=max(j,record[s[i]]+1);
    //仅有s[i]重复出现才可能使j变化，j意味着将前一个与s[i]的数之前的那段截取后第一个数的索引
    ans=max(ans,i-j+1); 
    record[s[i]]=i;
}
    return ans;
    }
};
