class Solution01 {
public:
    string largestMerge(string word1, string word2) {
        string ans;
        while (word1 != ""|| word2 != "") {
            if (word1 == "") {ans += word2; break;}
            if (word2 == "") {ans += word1; break;}
            int m = word1.size(), n = word2.size();
            if (word1[0] > word2[0]) {
                ans += word1[0]; 
                if (m == 1) word1 = "";
                else word1 = word1.substr(1, m-1);
            }
            else {
                if (word1[0] < word2[0]) {
                    ans += word2[0]; 
                    if (n == 1) word2 = "";
                    else word2 = word2.substr(1, n-1);
                }
                else {//word1[0] == word2[0]
                    int index = 1;
                    while (index < m && index < n && word1[index] == word2[index]) ++index;
                    if (index == m) {
                        ans += word2[0];
                        if (n == 1) word2 = "";
                        else word2 = word2.substr(1, n-1);
                        continue;
                    }
                    if (index == n) {
                        ans += word1[0];
                        if (m == 1) word1 = "";
                        else word1 = word1.substr(1, m-1); 
                        continue;
                    }
                    if (word1[index] > word2[index]) {ans += word1[0]; word1 = word1.substr(1, m-1);}
                    else {ans += word2[0]; word2 = word2.substr(1, n-1);}
                }
            }
            /*cout << ans << endl;
            cout << word1 << "   " << word2 << endl;
            cout << endl;*/
        }
        return ans;
    }
};
