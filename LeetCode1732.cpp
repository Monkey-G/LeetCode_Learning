int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int max_altitude = 0;
        int altitude = 0;
        for (int altitude_change : gain) {
            altitude += altitude_change; max_altitude = max(max_altitude, altitude);
        }
        return max_altitude;
    }
};
