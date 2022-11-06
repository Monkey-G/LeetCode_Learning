class Solution01 {
public:
    int reachNumber(int target) {
        //先找出满足n*(n+1)/2 <= |target| < (n+1)*(n+2)/2的n值，
        //即单向n次移动就可以到达或者接近target，而多一次单向移动就会超过target
        //而改变任何一个前n次移动的值都可以实现对绝对值偶数方式（-2，-4...-2n）的减法
        //由于和target的距离是小于（n+1）的，设为distance，
        //那就可以第（n+1）原方向继续移动;然后，即绝对值增加了（n+1-2k）
        //（1）如果n是奇数，那绝对值只能增加偶数：2（k=（n-1）/2）；（n-1）（k=1），
        //对于distance为奇数(distance != 1)的情况，必须要再多一步并再次调整前n次移动，
        //从而实现绝对值增加3至(2n+1)的任意奇数,distance = 1的情况直接多两步即可,
        //------即，n是奇数时，distance为0，需n步；distance不为0且与n奇偶性相反，则需（n+1）步；
        //------distance不为0且与n奇偶性相同，则需（n+2）步；
        //（2）如果如果n是偶数，那绝对值只能增加奇数：1（k=n/2）；（n-1）（k=1），
        //对于distance为偶数的情况，必须要再多两步去+1或者-1，从而实现绝对值增加1至n的任意整数
        //------即，n是偶数时，distance为0，需n步；distance不为0且与n奇偶性相反，则需（n+1）步；
        //------distance不为0且与n奇偶性相同，则需（n+3）步；

        int target_abs = (target > 0) ? target : -target;
        int cnt = sqrt(2) * sqrt(target_abs) - 1;//(cnt-1) < n <= cnt+1，即n = cnt+1或者n = cnt
        int distance = target_abs - cnt * (cnt+1) / 2;
        if (distance >= cnt+1){
            ++cnt;
            distance -= cnt;
        }//确定好了n和distance

        if (distance != 0){
            if ((cnt + distance) % 2) ++cnt;
            else cnt += (cnt % 2 ? 2 : 3);
        }

        return cnt;
    }
};
