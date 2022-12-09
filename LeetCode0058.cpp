class Solution01 {
public:
    int lengthOfLastWord(string s) {
        while (s.rfind(" ") == s.size()-1) s = s.substr(0, s.size()-1);
        cout << s;
        if (s.rfind(" ") != string::npos) return s.size()-1-s.rfind(" ");
        else return s.size();
    }
};
