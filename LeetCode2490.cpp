class Solution01 {
public:
    bool isCircularSentence(string sentence) {
        vector<string> vstr;
        int index = 0;
        while (sentence.find(" ", index) != string::npos){
            vstr.push_back(sentence.substr(index, sentence.find(" ", index)-index));
            index = sentence.find(" ", index)+1;
        }
        vstr.push_back(sentence.substr(index, sentence.size()-index));

        if (sentence.front() != sentence.back()) return false;
        bool ans = true;
        for (int i = 1; i < vstr.size(); ++i) if (vstr[i].front() != vstr[i-1].back()) {ans = false; break;}
        return ans;
    }
};
