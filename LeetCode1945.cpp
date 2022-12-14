class Solution01 {
public:
    int getLucky(string s, int k) {
        int ans = 0;
        for (char ch : s) ans += (ch-'a'+1)/10 + (ch-'a'+1)%10;
        for (int i = 0; i < k-1; ++i) {
            if (ans < 10) break;
            int tmp = 0;
            while (ans > 0) {tmp += ans%10; ans /= 10;}
            ans = tmp;
        }
        return ans;
    }
};
