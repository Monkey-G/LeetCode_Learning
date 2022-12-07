#define FOR(i, m, n) for (int i = m; i < n; ++i)
#define FORR(i, m, n) for (int i = n-1; i >= m; --i)

class Solution01 {//自己写的超时解
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int n = nums.size();
        //0 <= i < j < k <= n-1
        unordered_map <int, vector<int>> sum_inverse_ij;
        unordered_set<int> i_visited, j_visited, k_visited;
        FOR (i, 0, n-2) {
            if (i_visited.count(nums[i])) continue;
            i_visited.emplace(nums[i]);
            j_visited.clear();
            FOR (j, i+1, n-1) {
                if (j_visited.count(nums[j])) continue;
                j_visited.emplace(nums[j]);
                //cout << i << " " << j << " " << nums[i] << " " << nums[j] << " " << -nums[i]-nums[j] << endl;
                sum_inverse_ij[-nums[i]-nums[j]].push_back(i); sum_inverse_ij[-nums[i]-nums[j]].push_back(j);
            }
        }
        FORR (k, 0, n) {
            if (k_visited.count(nums[k])) continue;
            //cout << k << " ";
            if (sum_inverse_ij[nums[k]].empty()) continue;
            int m = sum_inverse_ij[nums[k]].size(), index = 0;
            while (index < m) {
                int i = sum_inverse_ij[nums[k]][index], j = sum_inverse_ij[nums[k]][index+1];
                if (k > i && k > j) {
                    ans.push_back({nums[i], nums[j], nums[k]});
                    //cout << nums[i] << " " << nums[j] << " " << nums[k] << endl;
                }
                index += 2;
            }
            k_visited.emplace(nums[k]);
        }
        return ans;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();





#define FOR(i, m, n) for (int i = m; i < n; ++i)
#define FORR(i, m, n) for (int i = n-1; i >= m; --i)

class Solution02 {//多次优化下终于跑过所有算例的垃圾解，1900ms....
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int n = nums.size();
        //0 <= i < j < k <= n-1
        unordered_map <int, vector<int>> sum_inverse_ij;
        int i_visited = INT_MIN, j_visited = INT_MIN, k_visited = INT_MIN;
        FOR (i, 0, n-2) {
            if (nums[i] > 0) break;
            if (nums[i] == i_visited) continue;
            i_visited = nums[i];
            j_visited = INT_MIN;
            FOR (j, i+1, n-1) {
                if (nums[j] == j_visited) continue;
                j_visited = nums[j];
                //cout << i << " " << j << " " << nums[i] << " " << nums[j] << " " << -nums[i]-nums[j] << endl;
                sum_inverse_ij[-nums[i]-nums[j]].push_back(i); sum_inverse_ij[-nums[i]-nums[j]].push_back(j);
            }
        }
        FORR (k, 2, n) {
            if (nums[k] == k_visited || nums[k] < 0) continue;
            //cout << k << " ";
            if (sum_inverse_ij[nums[k]].empty()) continue;
            int index = 0;
            while (index < sum_inverse_ij[nums[k]].size()) {
                int i = sum_inverse_ij[nums[k]][index], j = sum_inverse_ij[nums[k]][index+1];
                if (k > j) {//一定有i < j <= k，且nums[i] <= nums[j] <= nums[k]
                    ans.push_back({nums[i], nums[j], nums[k]});
                    //cout << nums[i] << " " << nums[j] << " " << nums[k] << endl;
                }
                index += 2;
            }
            k_visited = nums[k];
        }
        return ans;
    }
};

//加速
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();
