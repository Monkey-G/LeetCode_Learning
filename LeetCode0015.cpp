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



class Solution03 {//官方排序+双指针
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        // 枚举 a
        for (int first = 0; first < n; ++first) {
            // 需要和上一次枚举的数不相同
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            // c 对应的指针初始指向数组的最右端
            int third = n - 1;
            int target = -nums[first];
            // 枚举 b
            for (int second = first + 1; second < n; ++second) {
                // 需要和上一次枚举的数不相同
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                // 需要保证 b 的指针在 c 的指针的左侧
                while (second < third && nums[second] + nums[third] > target) {
                    --third;
                }
                // 如果指针重合，随着 b 后续的增加
                // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
                if (second == third) {
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    ans.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return ans;
    }
};



class Solution04 {//网友基于排序+双指针的进一步优化解
public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        int n = nums.size();
        for (int i = 0; i < n - 2; ++i) {
            int x = nums[i];
            if (i && x == nums[i - 1]) continue; // 跳过重复数字
            if (x + nums[i + 1] + nums[i + 2] > 0) break; // 优化一
            if (x + nums[n - 2] + nums[n - 1] < 0) continue; // 优化二
            int j = i + 1, k = n - 1;
            while (j < k) {
                int s = x + nums[j] + nums[k];
                if (s > 0) --k;
                else if (s < 0) ++j;
                else {
                    ans.push_back({x, nums[j], nums[k]});
                    for (++j; j < k && nums[j] == nums[j - 1]; ++j); // 跳过重复数字
                    for (--k; k > j && nums[k] == nums[k + 1]; --k); // 跳过重复数字
                }
            }
        }
        return ans;
    }
};
