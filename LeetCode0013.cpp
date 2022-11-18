#define FOR(i, n) for(int i = 0; i < n; ++i)

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {
public:
    int romanToInt(string s) {
        int n = s.size();
        int ans = 0;

        FOR(i, n) {
            if (s.find("M", i) == i) {ans += 1000; continue;}
            if (s.find("M", i) == i+1) {ans += 900; ++i; continue;}//只有"M"找完了，才可能出现小于900的数

            if (s.find("D", i) == i) {ans += 500; continue;}
            if (s.find("D", i) == i+1) {ans += 400; ++i; continue;}//只有"D"找完了，才可能出现小于400的数

            if (s.find("C", i) == i) {ans += 100; continue;}
            if (s.find("C", i) == i+1) {ans += 90; ++i; continue;}//只有"C"找完了，才可能出现小于90的数

            if (s.find("L", i) == i) {ans += 50; continue;}
            if (s.find("L", i) == i+1) {ans += 40; ++i; continue;}//只有"L"找完了，才可能出现小于40的数

            if (s.find("X", i) == i) {ans += 10; continue;}
            if (s.find("X", i) == i+1) {ans += 9; ++i; continue;}//只有"X"找完了，才可能出现小于9的数

            if (s.find("V", i) == i) {ans += 5; continue;}
            if (s.find("V", i) == i+1) {ans += 4; ++i; continue;}//只有"V"找完了，才可能出现小于4的数

            if (s.find("I", i) == i) {ans += n-i; break;}
        }

        return ans;
    }
};
