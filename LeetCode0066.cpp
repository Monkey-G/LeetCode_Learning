#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        vector<int> ans(n, 0);
        stack<int> st;
        int index = n-1, carry = 1;
        while (index >= 0) {
            if (digits[index] + carry == 10) {st.push(0); --index;}
            else {st.push(digits[index] + carry); --index; break;}
        }
        if (index == -1) {
            if (st.top() == 0) {ans.resize(n+1); ans[0] = 1;}
            else ans[0] = st.top();
        }
        else {
            FOR (i, 0, index+1) ans[i] = digits[i];
            ++index;
            while (!st.empty()) {ans[index] = st.top(); st.pop(); ++index;}
        }
        return ans;
    }
};


class Solution02 {//官方解，简单一点
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        for (int i = n - 1; i >= 0; --i) {
            if (digits[i] != 9) {
                ++digits[i];
                for (int j = i + 1; j < n; ++j) {
                    digits[j] = 0;
                }
                return digits;
            }
        }

        // digits 中所有的元素均为 9
        vector<int> ans(n + 1);
        ans[0] = 1;
        return ans;
    }
};
