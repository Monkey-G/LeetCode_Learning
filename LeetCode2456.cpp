class Solution01 {
public:
    vector<vector<string>> mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views) {
        int n = creators.size();
        unordered_map<string, long long> Sum_of_views;//储存每个作者他的总播放量
        unordered_map<string, int> Max_view_minindex;//储存每个作者他的最大播放量视频对应下标

        vector<vector<string>> answer;//答案

        for (int i = 0; i < n; i++){
            string &creator_i = creators[i];
            Sum_of_views[creator_i] += views[i];
            if (Max_view_minindex.count(creator_i)){
                int &t = Max_view_minindex[creator_i];
                if (views[i] > views[t] || (views[i] == views[t] && ids[i] < ids[t]))
                t = i;
            }
            else
            Max_view_minindex[creator_i] = i;
        }

        long long max_popularity = -1;//最大播放量
        for (auto it = Sum_of_views.begin(); it != Sum_of_views.end(); ++it)
        max_popularity = max(max_popularity, it->second);//求出最大播放量

        for (auto it = Sum_of_views.begin(); it != Sum_of_views.end(); ++it)
        if (it->second == max_popularity)
        answer.push_back({it->first, ids[Max_view_minindex[it->first]]});//把达到最大播放量的作者都列出来

        return answer;
    }
};
