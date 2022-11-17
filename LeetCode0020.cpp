//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {
public:
    bool isValid(string s) {
        int n = s.size();
        bool ans = true;
        if (n % 2 == 1) ans = false;
        else{
            stack<char> st;
            int index = 0;
            while (index < n){
                if (st.empty()) {
                    if (s[index] == ')' || s[index] == ']' || s[index] == '}') {ans = false; break;}
                    st.push(s[index]); ++index; continue;
                }

                if (!st.empty() && st.top() == '('){
                    if (s[index] == ']' || s[index] == '}') {ans = false; break;}
                    if (s[index] == ')') {st.pop(); ++index; continue;}
                    st.push(s[index]); ++index; continue;
                }

                if (!st.empty() && st.top() == '['){
                    if (s[index] == ')' || s[index] == '}') {ans = false; break;}
                    if (s[index] == ']') {st.pop(); ++index; continue;}
                    st.push(s[index]); ++index; continue;
                }

                if (!st.empty() && st.top() == '{'){
                    if (s[index] == ')' || s[index] == ']') {ans = false; break;}
                    if (s[index] == '}') {st.pop(); ++index; continue;}
                    st.push(s[index]); ++index; continue;
                }
            }
            if (!st.empty()) ans = false;
        }
        return ans;
    }
};
