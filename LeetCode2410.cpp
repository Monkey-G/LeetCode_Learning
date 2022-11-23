class Solution01 {//自己写的垃圾解
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(players.begin(), players.end(), [](int &a, int &b){ return a < b; });
        sort(trainers.begin(), trainers.end(), [](int &a, int &b){ return a < b; });
        int m = players.size(), n = trainers.size();
        int player_index = 0, trainer_index = 0;
        int ans = 0;

        while (player_index < m && trainer_index < n) {
            while (trainer_index < n) {
                if (players[player_index] > trainers[trainer_index]) ++trainer_index;
                else break;
            }
            if (trainer_index == n) break;
            else {++ans; ++player_index; ++trainer_index;}
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
