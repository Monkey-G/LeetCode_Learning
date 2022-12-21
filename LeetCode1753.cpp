/*
（1）设a <= b <= c，
（2）当c >= a+b时，输出a+b
（3）当c < a+b时，输出(a+b+c)/2
*/

class Solution01 {
public:
    int maximumScore(int a, int b, int c) {
        int tmp = max(a, b); tmp = max(tmp,c);
        return min((a+b+c)/2, a+b+c-tmp);
    }
};
