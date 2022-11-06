class Solution01 {//自己写的垃圾代码，本质上就是暴力解，严重超时
public:
    int magicalString(int n) {
        vector<int> amazing_string = {1};//储存神奇字符串的vector，amazing_string的第一个数为1
        int cnt = 0;//记录新加数据的始端索引

        vector<int> string_operator = {1};
        auto it = string_operator.begin();//amazing_string追踪指针
        
        int ans = 1;//结果

        while (amazing_string.size() < n){
            cnt = amazing_string.size();

            for (; it != string_operator.end(); ++it){
                //根据string_operator来补充数
                if (*it == 1){
                    if(amazing_string.back() == 1)
                    amazing_string.push_back(2);
                    else
                    amazing_string.push_back(1);
                }

                else{
                    if (amazing_string.back() == amazing_string[amazing_string.size()-2]){
                        if(amazing_string.back() == 1){
                           amazing_string.push_back(2);
                           if (amazing_string.size() < n)
                           amazing_string.push_back(2); 
                        }

                        else{
                            amazing_string.push_back(1);
                            if (amazing_string.size() < n)
                            amazing_string.push_back(1);
                        }
                    }

                    else {
                        if(amazing_string.back() == 1)
                        amazing_string.push_back(1);
                        else
                        amazing_string.push_back(2);
                    }
                }

                if (amazing_string.size() == n)
                break;
            }

            if (amazing_string.size() == n)
            break;
            
            for (; cnt < amazing_string.size(); cnt++)
            string_operator.push_back(amazing_string[cnt]);

            it = string_operator.end();
        }

        ans = count(amazing_string.begin() , amazing_string.end() , 1);

        return ans;
    }
};

class Solution02 {//其实他的思路也是从某值开始一步一步遍历推出后边的数来扩充数列直至到达判断条件，以后写代码要先好好想好合理性
public:
    int magicalString(int n) {
        if (n < 4) {
            return 1;
        }
        string s(n, '0');
        s[0] = '1', s[1] = '2', s[2] = '2';
        int res = 1;
        int i = 2;
        int j = 3;
        while (j < n) {
            int size = s[i] - '0';
            int num = 3 - (s[j - 1] - '0');
            while (size > 0 && j < n) {
                s[j] = '0' + num;
                if (num == 1) {
                    ++res;
                }
                ++j;
                --size;
            }
            ++i;
        }
        return res;
    }
};
