using LL = long long;

class Solution {
public:
    int minimumBoxes(int n) {
        LL m = 0;
        while (m*(m+1)*(m+2)/6 < n) ++m;
        //cout << m << endl;
        int k = 0;
        while (k*(k+1)/2 < n-(m-1)*m*(m+1)/6) ++k;
        //cout << k << endl;
        return m*(m-1)/2+k;
    }
};
