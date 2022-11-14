class Solution01 {//自己的解
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        int ans = 0, cnt = 0;
        sort(boxTypes.begin(), boxTypes.end(), [](vector<int> &a, vector<int> &b){ return a[1] > b[1]; });
        for (auto box_itype : boxTypes) {
            if (cnt < truckSize) {
                ans += box_itype[1] * min(box_itype[0], truckSize-cnt); 
                cnt += min(box_itype[0], truckSize-cnt);
            }
            if (cnt == truckSize) break;
        }
        return ans;
    }
};

class Solution02 {//网友解，用了结构体，会快些
typedef struct
{
    int box;
    int unit;
}node;
public:
static bool cmp(node a,node b)
{
    if(a.unit!=b.unit)
        return a.unit>b.unit;
    else  
        return a.box>b.box;
}
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        vector<node> v;
        for(int i=0;i<boxTypes.size();i++)
            v.push_back({boxTypes[i][0],boxTypes[i][1]});
        sort(v.begin(),v.end(),cmp);
        int sum=0;
        for(int i=0;i<v.size();i++)
        {
            if(truckSize!=0)
            {
                if(v[i].box<=truckSize)
                {
                    sum+=v[i].box*v[i].unit;
                    truckSize-=v[i].box;
                }
                else
                {
                    sum+=truckSize*v[i].unit;
                    truckSize=0;
                }
            
            }
            else
                break;
        }
        return sum;
    }
};
