class Solution01 {//参考ck写的代码，其实思路是对的，但是在具体敲代码还是没有合理使用函数，导致过于复杂而且大概率出错，还不好debug
public:
    vector<string> ambiguousCoordinates(string s) {
        s = s.substr(1, s.size() - 2);
        int n = s.size();
        vector<string> ans;

        for (int index = 1; index < n; index++){//index指向r_str的头部
            string l_str = s.substr(0, index), r_str = s.substr(index, n-index);
            if (!check_identity(l_str) || !check_identity(r_str)) continue;
            vector<string> l_str_addpoint_vector = addpoint(l_str), r_str_addpoint_vector = addpoint(r_str);
            for (auto l_str_addpoint : l_str_addpoint_vector)
            for (auto r_str_addpoint : r_str_addpoint_vector)
            ans.push_back("(" + l_str_addpoint + ", " + r_str_addpoint + ")");
        }
        return ans;
    }
private:
    //长度大于1的左右子串的头尾部不能同时为零
    inline bool check_identity(const string &str) {return (str.size() == 1 || str[0] != '0' || str[str.size()-1] != '0');}
    inline vector<string> addpoint(const string &str){
        int m = str.size();
        vector<string> str_addpoint_vector;
        //当输入子串的长度等于1或者其尾部为0时str不可以加小数点（其尾部为0时头部不可能为0）
        if (str.size() == 1 || str[m-1] == '0') str_addpoint_vector.push_back(str);
        else{
            //此时str的长度一定大于1且头部为0时，其只能是0.xxx的形式
            if (str[0] == '0') str_addpoint_vector.push_back(str.substr(0, 1) + "." + str.substr(1, m-1));
            else{//此时str的长度大于1而且首尾均不为0
                //point_index为插入"."的位置，这步是加入了所有加小数点的情况
                for (int point_index = 1; point_index < m; point_index++) {
                    str_addpoint_vector.push_back(str.substr(0, point_index) + "." + str.substr(point_index, m-point_index));
                }
                //补上不用加小数点的情况
                str_addpoint_vector.push_back(str);
            }
        }
        return str_addpoint_vector;
    }
};

class Solution02 {//官方解，更简洁
public:
    vector<string> getPos(string s) {
        vector<string> pos;
        if (s[0] != '0' || s == "0") pos.push_back(s);
        for (int p = 1; p < s.size(); ++p) {
            if ((p != 1 && s[0] == '0') || s.back() == '0') continue;
            pos.push_back(s.substr(0, p) + "." + s.substr(p));
        }
        return pos;
    }
    vector<string> ambiguousCoordinates(string s) {
        int n = s.size() - 2;
        vector<string> res;
        s = s.substr(1, s.size() - 2);
        for (int l = 1; l < n; ++l) {
            vector<string> lt = getPos(s.substr(0, l));
            if (lt.empty()) continue;
            vector<string> rt = getPos(s.substr(l));
            if (rt.empty()) continue;
            for (auto& i : lt) {
                for (auto& j : rt) {
                    res.push_back("(" + i + ", " + j + ")");
                }
            }
        }
        return res;
    }
};
