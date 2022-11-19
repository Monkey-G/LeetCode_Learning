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

 int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution01 {//自我引用
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        } else if (l2 == nullptr) {
            return l1;
        } else if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
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
int __FAST_IO__ = []() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    return 0;
}();

class Solution02 {//交叉链
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head = new ListNode;
        ListNode *p = head;

        while (list1 && list2) {
            ListNode* s = new ListNode;
            if (list1->val <= list2->val) {s->val = list1->val; p->next = s; p = p->next; list1 = list1->next;}
            else {s->val = list2->val; p->next = s; p = p->next; list2 = list2->next;}
        }

        while (list1 && !list2) {
            ListNode* s = new ListNode;
            s->val = list1->val; p->next = s; p = p->next; list1 = list1->next;
        }

        while (!list1 && list2) {
            ListNode* s = new ListNode;
            s->val = list2->val; p->next = s; p = p->next; list2 = list2->next;
        }

        return head->next;
    }
};
