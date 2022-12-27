class Solution01 {
public:
    int minimumMoves(string s) {
        int ans = 0;
        s += 'O'; s += 'O';
        int n = s.size();
        for (int i = 0; i < n-2; ++i) if (s[i] == 'X') {++ans; i += 2;}
        return ans;
    }
};
