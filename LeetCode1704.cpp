class Solution01 {
public:
    bool halvesAreAlike(string s) {
        int n = s.size();
        string a = s.substr(0, n/2), b = s.substr(n/2, n/2);
        return (check_vowel(a) == check_vowel(b));
    }

private:
    inline int check_vowel (const string &str){
        int vowel_num = 0;
        for (auto&& ch : str)
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'
         || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
        ++vowel_num;
        return vowel_num;
    }
};
