/*思路：
（1）首先，当A.size()大于1时，A的最底下盘子要给C，那就意味着在这次交换之前，A通过C向B转移了前（n-1）个盘子，
假设move(n, A, B, C)为A通过B向C转移n个盘子，
move(n, A, B, C)一定是在move(n-1, A, C, B)的基础上再把底盘给B的，给完底盘之后，我们需要move(n-1, B, A, C),由此依次循环
*/

class Solution01 {
public:
    void hanota(vector<int>& A, vector<int>& B, vector<int>& C) {
        int n = A.size();
        move(n, A, B, C);
    }

private:
    inline void move(int n, vector<int>& A, vector<int>& B, vector<int>& C) {
        if (n == 1) {C.push_back(A.back()); A.pop_back(); return;}
        move(n-1, A, C, B); C.push_back(A.back()); A.pop_back(); move(n-1, B, A, C);
    }
};
