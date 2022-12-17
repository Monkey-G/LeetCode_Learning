class Solution01 {
public:
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        int m = groups.size(), n = nums.size();
        int l = 0, r = 0, cnt = 0;
        while (l < n && r < n && cnt < m) {
            while (l < n && nums[l] != groups[cnt][0]) ++l;
            if (l == n) break;
            //cout << l << " ";
            r = l;
            for (int num : groups[cnt]) {if (nums[r] == num && r < n) ++r; else break;}
            //cout << r << " ";
            if (r-l == groups[cnt].size()) {++cnt; l = r;}
            else ++l;
            //cout << cnt << endl;
        }
        return cnt == m;
    }
};

class Solution02 {//官方贪心 + 双指针
public:
    bool check(vector<int> &g, vector<int> &nums, int k) {
        if (k + g.size() > nums.size()) {
            return false;
        }
        for (int j = 0; j < g.size(); j++) {
            if (g[j] != nums[k + j]) {
                return false;
            }
        }
        return true;
    }

    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        int i = 0;
        for (int k = 0; k < nums.size() && i < groups.size();) {
            if (check(groups[i], nums, k)) {
                k += groups[i].size();
                i++;
            } else {
                k++;
            }
        }
        return i == groups.size();
    }
};


class Solution03 {//官方KMP 匹配算法
public:
    int find(vector<int> &nums, int k, vector<int> &g) {
        int m = g.size(), n = nums.size();
        if (k + g.size() > nums.size()) {
            return -1;
        }
        vector<int> pi(m);
        for (int i = 1, j = 0; i < m; i++) {
            while (j > 0 && g[i] != g[j]) {
                j = pi[j - 1];
            }
            if (g[i] == g[j]) {
                j++;
            }
            pi[i] = j;
        }
        for (int i = k, j = 0; i < n; i++) {
            while (j > 0 && nums[i] != g[j]) {
                j = pi[j - 1];
            }
            if (nums[i] == g[j]) {
                j++;
            }
            if (j == m) {
                return i - m + 1;
            }
        }
        return -1;
    }

    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        int k = 0;
        for (int i = 0; i < groups.size(); i++) {
            k = find(nums, k, groups[i]);
            if (k == -1) {
                return false;
            }
            k += groups[i].size();
        }
        return true;
    }
};
