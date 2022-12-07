class Solution01 {
public:
    bool squareIsWhite(string coordinates) {
        if ((coordinates[0]+coordinates[1]-'a'-'1') % 2) return true;
        else return false;
    }
};
