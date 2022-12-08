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
