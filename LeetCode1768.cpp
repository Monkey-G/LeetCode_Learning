class Solution01 {
public:
    string mergeAlternately(string word1, string word2) {
    int m = word1.size(),n = word2.size();
    int i =0,j =0;//索引
    string word3; 
	word3.reserve(m+n);
	while(i < m  || j < n)
	{  
        if (i < m){
            word3.push_back(word1[i]);
            ++i;
        }

        if (j < n){
            word3.push_back(word2[j]);
            ++j;
        }
	}
    return word3;
    }
};
