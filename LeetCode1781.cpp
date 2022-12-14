#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {//暴力解，时间都到1000ms以上了.....
public:
    int beautySum(string s) {
        int ans = 0;
        int n = s.size();
        vector<vector<int>> char_hash(n+1, vector<int>(26));//char_hash[i]对应前i个数的情况，char_hash[i][j]对应前i个数中j对应字符出现次数
        FOR (i, 1, n+1) {char_hash[i] = char_hash[i-1]; ++char_hash[i][s[i-1]-'a'];}

        //FOR (i, 0, n+1) {FOR (j, 0, 26) {cout << char_hash[i][j];} cout << endl;}

        FOR (i, 0, n-2) {
            FOR (j, i+3, n+1) {
                int max_freq = 0, min_freq = 501;
                FOR (k, 0, 26) {
                    max_freq = max(max_freq, char_hash[j][k]-char_hash[i][k]); 
                    if (char_hash[j][k]-char_hash[i][k] > 0) min_freq = min(min_freq, char_hash[j][k]-char_hash[i][k]);
                }
                ans += max_freq-min_freq;
                //cout << i << "  " << j << "  " << max_freq-min_freq << endl;
            }
        }
        return ans;
    }
};


class Solution02 {//官方暴力解，其实思路和我一样，但是hash作为了局部变量，调用更快点
public:
    int beautySum(string s) {
        int res = 0;
        for (int i = 0; i < s.size(); i++) {
            vector<int> cnt(26);
            int maxFreq = 0;
            for (int j = i; j < s.size(); j++) {
                cnt[s[j] - 'a']++;
                maxFreq = max(maxFreq, cnt[s[j] - 'a']); 
                int minFreq = s.size();
                for (int k = 0; k < 26; k++) {
                    if (cnt[k] > 0) {
                        minFreq = min(minFreq, cnt[k]);
                    }
                }
                res += maxFreq - minFreq;
            }
        }
        return res;
    }
};


class Solution03 {//网友神解
public:
    int beautySum(string s) {
        short length = s.length();
        int answer = 0;
        if (length <= 2) {
            return answer;
        }

        for (short i = 0; i < length; i++) {
            short max = 1;
            short min = 1;
            char minFrequenceChar = s[i];
            short charFrequence[26] = {0};
            charFrequence[s[i] - 'a']++;
            for (short j = i + 1; j < length; j++) {
                short frequenceIndex = s[j] - 'a';
                charFrequence[frequenceIndex]++;
                if (charFrequence[frequenceIndex] == 1) {
                    min = 1;
                    minFrequenceChar = s[j];
                    answer += max - min;
                    continue;
                }
                if (s[j] == minFrequenceChar) {
                    min++;
                    for (char k = 0; k < 26; k++) {
                        if (charFrequence[k] > 0 && charFrequence[k] < min) {
                            min = charFrequence[k];
                            minFrequenceChar = 'a' + k;
                            break;
                        }
                    }
                }
                if (charFrequence[frequenceIndex] > max) {
                    max = charFrequence[frequenceIndex];
                }
                answer += max - min;
            }
        }

        return answer;
    }
};
