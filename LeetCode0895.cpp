class FreqStack {
public:
    FreqStack() {
        max_freq = 0;
    }
    
    void push(int val) {
        ++freq_cnt[val];//val对应的freq增加
        //把push后val对应的频率freq_cnt[val]存进freq_group中相应频率的stack之中
        freq_group[freq_cnt[val]].push(val);
        max_freq = max(max_freq, freq_cnt[val]);//实时更新max_freq
    }
    
    int pop() {
        int val = freq_group[max_freq].top();//返回max_freq对应freq_group中stack的栈顶数
        --freq_cnt[val];//相对应的val的频率要自减，更新频率
        freq_group[max_freq].pop();//删除max_freq对应freq_group中stack的栈顶
        while (freq_group[max_freq].empty() && max_freq >= 0) --max_freq;//如果freq_group[max_freq]空了就更新max_freq
        return val;
    }

private:
    unordered_map<int, int> freq_cnt;
    unordered_map<int, stack<int>> freq_group;
    int max_freq;
};
/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
