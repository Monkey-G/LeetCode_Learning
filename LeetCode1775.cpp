#define FOR(i, m, n) for(int i = m; i < n; ++i)
#define FORR(i, m, n) for(int i = n-1; i >= m; --i)

class Solution01 {//自己的铸币解
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        if (n1 > 6*n2 || 6*n1 < n2) return -1;
        unordered_map<int, int> num_cnt;//nums2的i归算为nums1的7-i
        int sum1 = 0, sum2 = 0;
        FOR (i, 0, n1) {++num_cnt[nums1[i]]; sum1 += nums1[i];}
        FOR (i, 0, n2) {++num_cnt[7-nums2[i]]; sum2 += nums2[i];}
        int diff = sum1 - sum2;
        int ans = 0;
        if (diff < 0) {
            FOR (i, 1, 6) {
                if ((6-i)*num_cnt[i] + diff >= 0) {ans += (-diff+(6-i)-1)/(6-i); break;}
                else {ans += num_cnt[i]; diff += (6-i)*num_cnt[i];}
            }
        }
        if (diff > 0) {
            FORR (i, 2, 7) {
                if (diff - (i-1)*num_cnt[i] <= 0) {ans += (diff+(i-1)-1)/(i-1); break;}
                else {ans += num_cnt[i]; diff -= (i-1)*num_cnt[i];}
            }
        }
        return ans;
    }
};



class Solution02 {//官方解更简约
public:
    int help(vector<int>& h1, vector<int>& h2, int diff) {
        vector<int> h(7, 0);
        for (int i = 1; i < 7; ++i) {
            h[6 - i] += h1[i];
            h[i - 1] += h2[i];
        }
        int res = 0;
        for (int i = 5; i && diff > 0; --i) {
            int t = min((diff + i - 1) / i, h[i]);
            res += t;
            diff -= t * i;
        }
        return res;
    }

    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        if (6 * n < m || 6 * m < n) {
            return -1;
        }
        vector<int> cnt1(7, 0), cnt2(7, 0);
        int diff = 0;
        for (auto& i : nums1) {
            ++cnt1[i];
            diff += i;
        }
        for (auto& i : nums2) {
            ++cnt2[i];
            diff -= i;
        }
        if (!diff) {
            return 0;
        }
        if (diff > 0) {
            return help(cnt2, cnt1, diff);
        }
        return help(cnt1, cnt2, -diff);
    }
};



// https://space.bilibili.com/206214
int init = []() {
    cin.tie(nullptr)->sync_with_stdio(false);
    return 0;
}();

class Solution03 {//网友的数组解
public:
    int minOperations(vector<int> &nums1, vector<int> &nums2) {
        if (6 * nums1.size() < nums2.size() || 6 * nums2.size() < nums1.size())
            return -1;
        int d = accumulate(nums2.begin(), nums2.end(), 0) - accumulate(nums1.begin(), nums1.end(), 0);
        if (d < 0) {
            d = -d;
            swap(nums1, nums2);
        }
        int cnt[6]{}, ans = 0;
        for (int x: nums1) ++cnt[6 - x];
        for (int x: nums2) ++cnt[x - 1];
        for (int i = 5;; --i) {
            if (i * cnt[i] >= d)
                return ans + (d + i - 1) / i;
            ans += cnt[i];
            d -= i * cnt[i];
        }
    }
};
