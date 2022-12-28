class Solution01 {//自己的解
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        vector<int> ans, cnts;
        int n = nums.size();
        for (int i = 0; i < n; ++i) if (nums[i] == key) cnts.push_back(i);
        for (auto &cnt : cnts) add_index(cnt, ans, k, n);
        return ans;
    }

private:
    inline void add_index(const int index, vector<int> &ans, const int k, const int n) {
        //cout << index << " ";
        for (int i = max(index-k, 0); i < min(index+k+1, n); ++i) {
            if (!ans.empty() && i <= ans.back()) continue;
            ans.push_back(i);
        }
    }
};


class Solution02 {//网友解
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        vector<int> res;
        int right = 0;  // 未被检查过的最小下标
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] == key) {
                int left = max(right, i - k);
                right = min(n - 1, i + k) + 1;
                for (int j = left; j < right; j++) {
                    res.push_back(j);
                }
            }    
        }
        return res;
    }
};
