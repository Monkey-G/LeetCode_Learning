class Solution01 {//这类问题要好好考虑两段相交的情况
public:
    int maxRepeating(string sequence, string word) {
        int max_cnt = 0;
        string word_cut = word;
        word_cut.erase(0, 1);

        while(sequence.find(word) != string::npos){
            int cnt = 0;
            sequence.erase(0, sequence.find(word));
            while (sequence.find(word) == 0){sequence.erase(0, word.size());++cnt;} 
            sequence.insert(0, word_cut);
            max_cnt = max(max_cnt, cnt);
        }

        return max_cnt;
    }
};
