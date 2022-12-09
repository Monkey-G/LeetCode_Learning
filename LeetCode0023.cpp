/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/*思路：
（1）我估计是用单调栈来解决
*/

#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution01 {//自己做的单调栈解法
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* ans = new ListNode;
        ListNode* p = ans;
        int n = lists.size();
        deque<int> dq;
        unordered_set<int> visited;
        while (visited.size() != n) {//直到全部链表都找完
            FOR (i, 0, n) {
                if (visited.count(n)) continue;//该链表已经找完了
                if (!lists[i]) {visited.emplace(i);continue;}//该链表已经找完了
                if (dq.empty()) {dq.emplace_back(lists[i]->val); lists[i] = lists[i]->next;}//dq此时是空的，直接插值就行
                else {
                    //lists[i]->val大于等于所有dq的值，把它插在最后
                    if (lists[i]->val > dq.back()) {dq.emplace_back(lists[i]->val); lists[i] = lists[i]->next;}
                    //lists[i]->val小于所有dq的值，把它插在最前
                    else if (lists[i]->val <= dq.front()) {dq.emplace_front(lists[i]->val); lists[i] = lists[i]->next;}
                }
            }//一轮找完了，一定能找到该轮的最小值
            /*FOR (i, 0, dq.size()) cout << dq[i] << " ";
            cout << endl;*/
            if (!dq.empty()) {
                int value = dq.front();
                while (!dq.empty()) {
                    if (dq.front() == value){
                        ListNode* s = new ListNode;
                        s->val = dq.front(); dq.pop_front(); 
                        p->next = s; p = p->next;
                    }
                    else break;
                }
            }
        }
        while (!dq.empty()) {
            ListNode* s = new ListNode;
            s->val = dq.front(); dq.pop_front(); 
            p->next = s; p = p->next;
        }
        return ans->next;
    }
};





#define FOR(i, m, n) for (int i = m; i < n; ++i)

class Solution02 {// 自己做的哈希表解法最优化版本
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* ans = new ListNode;
        ListNode* p = ans;
        unordered_map<int, int> num_cnt;
        unordered_set<int> num_set;
        for (auto list : lists) while (list) {
            if (!num_set.count(list->val)) num_set.emplace(list->val);
            ++num_cnt[list->val]; list = list->next;
        }
        FOR (i, -10000, 10001) {
            if (!num_set.count(i)) continue;
            FOR (j, 0, num_cnt[i]) {
                ListNode* s = new ListNode;
                s->val = i; p->next = s; p = p->next;
            }
        }
        return ans->next;
    }
};


class Solution03 {//网友神解，用了有序容器
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<int, vector<int>, greater<int>> que;
        for (auto node:lists) {
            while (node != nullptr) {
                que.push(node->val);
                node = node->next;
            }
        }
        ListNode* dummy = new ListNode(-1);
        ListNode* p  = dummy;

        while (!que.empty()) {
            ListNode* tmp = new ListNode(que.top());
            que.pop();
            p->next = tmp;
            p = tmp;
        }
        p->next = nullptr;

        return dummy->next;

    }
};



