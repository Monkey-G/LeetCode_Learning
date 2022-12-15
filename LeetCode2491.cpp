/*思路：
（1）显然应该先对skill进行排序，由于是2人团而且每个团队技能和相等，那一定是最头配最尾，次头配次尾这样的依次匹配，
如果有一队技能和出现不等，那返回-1就可以了
*/
using LL = long long;

class Solution01 {
public:
    long long dividePlayers(vector<int>& skill) {
        LL ans = 0;
        sort(skill.begin(), skill.end());
        int l = 0, r = skill.size()-1;
        int sum = skill[l]+skill[r];
        while (l < r) {
            if (skill[l]+skill[r] != sum) {ans = -1; break;}
            else ans += skill[l++]*skill[r--];
        }
        return ans;
    }
};



class Solution02 {//网友好解，快一些
public:
    long long dividePlayers(vector<int>& skill) {
        int n=skill.size();
        int sum=0;
        for(int i=0;i<n;i++) sum+=skill[i];
        if(sum%(n/2)!=0) return -1;
        int points=sum/(n/2);
        int count[1001],maxskill=0;
        memset(count,0,sizeof(count));
        for(int i=0;i<n;i++){
            count[skill[i]]++;
            maxskill=max(maxskill,skill[i]);
        }
        long long ans=0;
        for(int i=1;i<=maxskill;i++){
            while(count[i]!=0){
                if(count[points-i]) count[points-i]--;
                else return -1;
                if(count[i]) count[i]--;
                else return -1;
                ans+=i*(points-i);
            }
        }
        return ans;
    }
};
