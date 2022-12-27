class Solution01 {//暴力解法
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        string ans;
        unordered_map<string, int> dic;
        for (auto &str : dictionary) dic[str] = 1;
        //cout << dic["pxbd"] << endl;

        int n = sentence.size();
        int index = 0;
        string cnt;
        while (index < n) {
            //cout << index << " " << ans << endl;
            if (sentence[index] == ' ') {ans += cnt; ans += ' '; cnt = ""; ++index; continue;}
            cnt += sentence[index];
            if (dic[cnt] == 1) {
                ans += cnt;
                if (sentence.find(" ", index) != string::npos) {ans += ' '; index = sentence.find(" ", index)+1; cnt = ""; continue;}
                else {cnt = ""; break;}
            }
            ++index;
        }
        ans += cnt;
        return ans;
    }
};
