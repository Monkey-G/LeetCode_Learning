using LL = long long;

const LL intmax = (LL)1 << 31;

class Solution01 {
public:
    int myAtoi(string s) {
        while (s[0] == ' ') s = s.substr(1, s.size()-1);
        int flag = 1;
        if (s[0] == '+') s = s.substr(1, s.size()-1);
        else {if (s[0] == '-') {s = s.substr(1, s.size()-1); flag = -1;}}
        int ans = 0;
        LL cnt = 0;
        while (s[0] >= 48 && s[0] <= 57) {
            cnt = cnt*10 + s[0] - '0';
            if (cnt >= intmax) {cnt = intmax; break;}
            s = s.substr(1, s.size()-1);
        }
        if (flag == 1 && cnt == intmax) cnt = intmax-1;
        ans = flag*cnt;
        return ans;
    }
};

int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();



//官方自动机，可视化更好
class Automaton {
    string state = "start";
    unordered_map<string, vector<string>> table = {
        {"start", {"start", "signed", "in_number", "end"}},
        {"signed", {"end", "end", "in_number", "end"}},
        {"in_number", {"end", "end", "in_number", "end"}},
        {"end", {"end", "end", "end", "end"}}
    };

    int get_col(char c) {
        if (isspace(c)) return 0;
        if (c == '+' or c == '-') return 1;
        if (isdigit(c)) return 2;
        return 3;
    }
public:
    int sign = 1;
    long long ans = 0;

    void get(char c) {
        state = table[state][get_col(c)];
        if (state == "in_number") {
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
        }
        else if (state == "signed")
            sign = c == '+' ? 1 : -1;
    }
};

class Solution02 {
public:
    int myAtoi(string str) {
        Automaton automaton;
        for (char c : str)
            automaton.get(c);
        return automaton.sign * automaton.ans;
    }
};
