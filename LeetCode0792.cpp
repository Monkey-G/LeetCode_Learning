int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {//自己写的解
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int ans = 0;
        for (string &word : words) {
            if (s.size() == 1) {if (word == s) ++ans;}
            else{
                int index = 0;
                int cnt = 0;
                for (char &ch : word) {
                    index = s.find(ch,index);
                    if (index == string::npos) break;//没找出来
                    else {++cnt; ++index;}
                }  
                if (cnt == word.size()) ++ans;
            }   
        }
        return ans;
    }
};


#define FOR(i, n) for(int i=0; i < n; ++i)

char*cursor[26][50001];
int len[26];
class Solution02 {//网友的神仙解
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        memset(len,0,sizeof(len));//把len中的初值全部初始化为0
        FOR(i, words.size()){//统计所有word，把它们的指针存进cursor的相应位置
            int c=words[i][0]-'a';
            cursor[c][len[c]++]=&words[i][0];
        }
        int ans=0;
        for(char c:S){
            c-='a';
            int k=len[c];
            len[c]=0;
            for(int i=0;i<k;i++){
                char*next=cursor[c][i]+1;
                if(!*next)ans++;
                else{
                    int d=*next-'a';
                    cursor[d][len[d]++]=next;
                }
            }
        }
        return ans;
    }
};
//IO
int _IO=[](){
	ios::sync_with_stdio(0);
	cin.tie(0); //cout.tie(0);
	return 0;
}();
