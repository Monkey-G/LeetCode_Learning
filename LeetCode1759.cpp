using LL = long long;

const LL mod = 1e9+7;

class Solution01 {
public:
    int countHomogenous(string s) {
        LL ans = 0;
        int n = s.size();
        int l = 0, r = 0;
        while (r < n) {
            //cout << l << "  " << r << endl;
            if (s[r] == s[l]) {++r; continue;}
            ans = (ans + LL(r-l)*(r-l+1)/2) % mod;
            l = r;
        }
        ans = (ans + LL(r-l)*(r-l+1)/2) % mod;
        return ans;
    }
};
