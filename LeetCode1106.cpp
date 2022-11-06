class Solution01 {//自己写的垃圾代码
public:
    bool parseBoolExpr(string expression) {
        bool res;
        int front_index = expression.rfind("(");
        int back_index = (front_index != string::npos) ? expression.find(")", front_index) : string::npos;
        string cnt;

        while (back_index != string::npos) {
            if (expression[front_index - 1] == 33) {//反操作，"!"对应ASCII码33
                cnt = (expression[front_index + 1] == 102) ? "t" : "f";
                //cout << cnt << endl;
                expression.erase(front_index - 1, back_index - front_index + 2);
                //cout << front_index << endl;
                //cout << expression << endl;
                if (expression.empty()) 
                expression += cnt;
                else 
                expression.insert(front_index - 1, cnt);
                //cout << front_index << endl;
                //cout << expression << endl;
            }

            if (expression[front_index - 1] == 38) {//与操作，"&"对应ASCII码38
                cnt = expression.substr(front_index + 1, back_index - 1);
                if (cnt.find("f") != string::npos) cnt = "f";
                else cnt = "t";
                //cout << cnt << endl;
                expression.erase(front_index - 1, back_index - front_index + 2);
                //cout << front_index << endl;
                //cout << expression << endl;
                if (expression.empty()) 
                expression += cnt;
                else 
                expression.insert(front_index - 1, cnt);
                //cout << front_index << endl;
                //cout << expression << endl;
            }

            if (expression[front_index - 1] == 124) {//或操作，"|"对应ASCII码124
                cnt = expression.substr(front_index + 1, back_index - 1);
                if (cnt.find("t") != string::npos) cnt = "t";
                else cnt = "f";
                //cout << cnt << endl;
                expression.erase(front_index - 1, back_index - front_index + 2);
                //cout << front_index << endl;
                //cout << expression << endl;
                if (expression.empty()) 
                expression += cnt;
                else 
                expression.insert(front_index - 1, cnt);
                //cout << front_index << endl;
                //cout << expression << endl;
            }

            front_index = expression.rfind("(");
            back_index = (front_index != string::npos) ? expression.find(")", front_index) : string::npos;
        }

        res = (expression == "t");

        return res;
    }
};

class Solution02 {//官方解，因为使用了stack，运行速度和占用内存都会更好些
public:
    bool parseBoolExpr(string expression) {
        stack<char> stk;
        int n = expression.size();
        for (int i = 0; i < n; i++) {
            char c = expression[i];
            if (c == ',') {
                continue;
            } else if (c != ')') {
                stk.push(c);
            } else {
                int t = 0, f = 0;
                while (stk.top() != '(') {
                    char val = stk.top();
                    stk.pop();
                    if (val == 't') {
                        t++;
                    } else {
                        f++;
                    }
                }
                stk.pop();
                char op = stk.top();
                stk.pop();
                switch (op) {
                case '!':
                    stk.push(f == 1 ? 't' : 'f');
                    break;
                case '&':
                    stk.push(f == 0 ? 't' : 'f');
                    break;
                case '|':
                    stk.push(t > 0 ? 't' : 'f');
                    break;
                default:
                    break;
                }
            }
        }
        return stk.top() == 't';
    }
};
