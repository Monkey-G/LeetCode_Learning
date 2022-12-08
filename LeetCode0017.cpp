class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> ans;
        if (digits == "") return ans;
        unordered_map<char, vector<char>> dict;
        for (int i = 2; i < 10; ++i) {
            if (i < 7) {
                dict['0'+i].push_back('a'+(i-2)*3+0); dict['0'+i].push_back('a'+(i-2)*3+1); dict['0'+i].push_back('a'+(i-2)*3+2);
            }
            if (i == 7) {
                dict['0'+i].push_back('a'+(i-2)*3+0); dict['0'+i].push_back('a'+(i-2)*3+1); 
                dict['0'+i].push_back('a'+(i-2)*3+2); dict['0'+i].push_back('a'+(i-2)*3+3);
            }
            if (i == 8) {
                dict['0'+i].push_back('a'+(i-2)*3+1+0); dict['0'+i].push_back('a'+(i-2)*3+1+1); dict['0'+i].push_back('a'+(i-2)*3+1+2);
            }
            if (i == 9) {
                dict['0'+i].push_back('a'+(i-2)*3+1+0); dict['0'+i].push_back('a'+(i-2)*3+1+1);
                dict['0'+i].push_back('a'+(i-2)*3+1+2); dict['0'+i].push_back('a'+(i-2)*3+1+3);
            }
        }
        queue<string> qu;
        qu.emplace("");
        for (char digit : digits) {
            int size = qu.size();
            if (digit == '7' || digit == '9') {
                while (size != 0) {
                    string str0 = qu.front(), str1 = qu.front(), str2 = qu.front(), str3 = qu.front();
                    str0 += dict[digit][0]; str1 += dict[digit][1]; str2 += dict[digit][2]; str3 += dict[digit][3];
                    qu.emplace(str0); qu.emplace(str1); qu.emplace(str2); qu.emplace(str3); 
                    qu.pop(); --size;
                }
            }
            else {
                while (size != 0) {
                    string str0 = qu.front(), str1 = qu.front(), str2 = qu.front();
                    str0 += dict[digit][0]; str1 += dict[digit][1]; str2 += dict[digit][2];
                    qu.emplace(str0); qu.emplace(str1); qu.emplace(str2); 
                    qu.pop(); --size;
                }
            }
        }
        while (!qu.empty()) {ans.push_back(qu.front()); qu.pop();}
        return ans;
    }
};
