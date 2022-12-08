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
class Solution01 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* tail = head;
        vector<int> nums;
        while (tail->next) {nums.push_back(tail->val); tail = tail->next;}
        nums.push_back(tail->val);
        int m = nums.size(), delete_index = m-n, index = 0;
        ListNode* ans = new ListNode;
        ListNode* p = ans;
        while (index < m) {
            if (index == delete_index) {++index; continue;}
            ListNode* s = new ListNode;
            s->val = nums[index];
            p->next = s;
            p = p->next;
            ++index;
        }
        return ans->next;
    }
};

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
class Solution02 {//网友解，简洁一些
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode* fast = head;
	ListNode* slow = head;
	for (int i = 0; i < n; i++) {
		fast = fast->next;
	}
	if (!fast) return head->next;
	while (fast->next) {
		slow = slow->next;
		fast = fast->next;
	}
	if (slow->next) 
		slow->next = slow->next->next;
	return head;
    }
};



class Solution03 {//官方1解
public:
    int getLength(ListNode* head) {
        int length = 0;
        while (head) {
            ++length;
            head = head->next;
        }
        return length;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        int length = getLength(head);
        ListNode* cur = dummy;
        for (int i = 1; i < length - n + 1; ++i) {
            cur = cur->next;
        }
        cur->next = cur->next->next;
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};

class Solution04 {//官方2解
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        stack<ListNode*> stk;
        ListNode* cur = dummy;
        while (cur) {
            stk.push(cur);
            cur = cur->next;
        }
        for (int i = 0; i < n; ++i) {
            stk.pop();
        }
        ListNode* prev = stk.top();
        prev->next = prev->next->next;
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};


class Solution05 {//官方3解，最优，空间复杂度最低
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* first = head;
        ListNode* second = dummy;
        for (int i = 0; i < n; ++i) {
            first = first->next;
        }
        while (first) {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};
