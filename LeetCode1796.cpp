class Solution01 {
public:
    int secondHighest(string s) {
        int first_max = -1, secord_max = -1;
        for (char ch : s) {
            if (!islower(ch)) {
                if (first_max < ch - '0') {
                    if (first_max != -1) secord_max = first_max;
                    first_max = ch - '0';
                }
                else if (first_max > ch - '0' && secord_max < ch - '0') secord_max = ch - '0';
                if (secord_max == 8) break;
                //cout << first_max << " " << secord_max << endl;
            }
        }
        return secord_max;
    }
};
