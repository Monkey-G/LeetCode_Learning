class Solution {
public:
    vector<string> ambiguousCoordinates(string s) {
        int n = s.size();
        vector<string> ans;

            //分为左子串、右子串；对于每一个子串，它自己的头尾部不能同时为0
            //对于每一个子串，当其头部为0，则其只能有0.xxx的形式；同理，当其尾部为0，则其只能有xxx0的形式
            int index = 1;
            if (s[1] - '0' != 0 && s[n-2] - '0' != 0){
                while (index < n-2){
                    string l_str = s.substr(1, index), r_str = s.substr(index+1, n-2-index);
                    if (l_str[index-1] - '0' == 0){//这种情况l_str不作处理
                        if (r_str[0] - '0' == 0) {
                            r_str.insert(1, ".");
                            string result = "()";
                            result.insert(1, l_str + ", " + r_str);
                            ans.push_back(result);
                        }
                        else{
                            for (int index_r = 1; index_r < r_str.size(); index_r++){
                                string r_str_copy = r_str;
                                r_str_copy.insert(index_r, ".");
                                string result = "()";
                                result.insert(1, l_str + ", " + r_str_copy);
                                ans.push_back(result);
                            }
                            string result = "()";
                            result.insert(1, l_str + ", " + r_str);
                            ans.push_back(result);
                        }
                    }
                    else{
                        if (r_str[0] - '0' == 0) {
                            r_str.insert(1, ".");
                            for (int index_l = 1; index_l < l_str.size(); index_l++){
                                string l_str_copy = l_str;
                                l_str_copy.insert(index_l, ".");
                                string result = "()";
                                result.insert(1, l_str_copy + ", " + r_str);
                                ans.push_back(result);
                            }
                            string result = "()";
                            result.insert(1, l_str + ", " + r_str);
                            ans.push_back(result);  
                        }
                        else{
                            for (int index_r = 1; index_r < r_str.size(); index_r++){
                                string r_str_copy = r_str;
                                r_str_copy.insert(index_r, ".");
                                for (int index_l = 1; index_l < l_str.size(); index_l++){
                                    string l_str_copy = l_str;
                                    l_str_copy.insert(index_l, ".");
                                    string result = "()";
                                    result.insert(1, l_str_copy + ", " + r_str_copy);
                                    ans.push_back(result);
                                }
                                string result = "()";
                                result.insert(1, l_str + ", " + r_str_copy);
                                ans.push_back(result);
                            }
                            for (int index_l = 1; index_l < l_str.size(); index_l++){
                                string l_str_copy = l_str;
                                l_str_copy.insert(index_l, ".");
                                string result = "()";
                                result.insert(1, l_str_copy + ", " + r_str);
                                ans.push_back(result);
                            }
                            string result = "()";
                            result.insert(1, l_str + ", " + r_str);
                            ans.push_back(result);
                        }
                    }
                }
            }
            if (s[1] - '0' == 0 && s[n-2] - '0' != 0){
                while (index < n-2){
                    if (index > 1 && s[index] - '0' == 0) {++index; continue;}
                    string l_str = s.substr(1, index), r_str = s.substr(index+1, n-2-index);
                    if (index > 1) l_str.insert(1, ".");//如果index > 1就将其转换为0.xxx的形式
                    if (r_str[0] - '0' == 0) {
                        r_str.insert(1, ".");
                        string result = "()";
                        result.insert(1, l_str + ", " + r_str);
                        ans.push_back(result);
                    }
                    else{
                        for (int index_r = 1; index_r < r_str.size(); index_r++){
                            string r_str_copy = r_str;
                            r_str_copy.insert(index_r, ".");
                            string result = "()";
                            result.insert(1, l_str + ", " + r_str_copy);
                            ans.push_back(result);
                        }
                        string result = "()";
                        result.insert(1, l_str + ", " + r_str);
                        ans.push_back(result);
                    }
                }
            }
            if (s[1] - '0' != 0 && s[n-2] - '0' == 0){
                while (index < n-2){
                    if (index < n-3 && s[index+1] - '0' == 0) {++index; continue;}
                    string l_str = s.substr(1, index), r_str = s.substr(index+1, n-2-index);
                    //这类情况右字串无小数，不需要处理
                    if (l_str[index-1] - '0' == 0) {
                        string result = "()";
                        result.insert(1, l_str + ", " + r_str);
                        ans.push_back(result);
                    }
                    else{
                        for (int index_l = 1; index_l < l_str.size(); index_l++){
                            string l_str_copy = l_str;
                            l_str_copy.insert(index_l, ".");
                            string result = "()";
                            result.insert(1, l_str_copy + ", " + r_str);
                            ans.push_back(result);
                        }
                        string result = "()";
                        result.insert(1, l_str + ", " + r_str);
                        ans.push_back(result);
                    }
                }
            }
            if (s[1] - '0' == 0 && s[n-2] - '0' == 0){
                while (index < n-2){
                    if (index > 1 && index < n-3 && (s[index] - '0' == 0 || s[index+1] - '0' == 0)) {++index; continue;}
                    string l_str = s.substr(1, index), r_str = s.substr(index+1, n-2-index);
                    if (index > 1) l_str.insert(1, ".");
                    string result = "()";
                    result.insert(1, l_str + ", " + r_str);
                    ans.push_back(result);
                }
            }

        return ans;
    }
};
