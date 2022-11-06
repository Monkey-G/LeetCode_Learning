class Solution01 {//自己写的垃圾代码
public:
    string interpret(string command) {
        int n = command.size();
        string ans_str;

        //G对应ASCII码71,(对应ASCII码40,)对应ASCII码41
        for(int i = 0; i < n;){
            char ch = command[i];
            if (ch == 71){
                ans_str += "G";
                ++i;
            }
            
            else {
                if (ch == 40){//
                    if (command[i+1] == 41){
                        ans_str += "o";
                        i += 2;
                    }
                    else{
                        ans_str += "al";
                        i += 4;
                    }
                }
            }
        }

        return ans_str;
    }
};
