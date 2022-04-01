// 方法一：模拟
// 模拟整个翻转的流程

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    pair<ListNode*,ListNode*> Myreverse(ListNode* head,ListNode* tail){
        ListNode* pre = tail->next;
        ListNode* p = head;
        pair<ListNode*,ListNode*> res;
        while(pre != tail){
            ListNode* next = p->next;
            p->next = pre;
            pre = p;
            p = next;
        }
        res.first = tail;
        res.second = head;

        return res;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* hair = new ListNode(0);
        hair->next = head;
        ListNode* pre = hair;

        while (head) {
            ListNode* tail = pre;
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (!tail) {
                    return hair->next;
                }
            }
            ListNode* nex = tail->next;
            pair<ListNode*, ListNode*> result = Myreverse(head, tail);
            head = result.first;
            tail = result.second;
            pre->next = head;
            tail->next = nex;
            pre = tail;
            head = tail->next;
        }

        return hair->next;
    }
};
// 方法二：递归
// 将多个反转变为一个反转
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        int num=0;
        ListNode* res=head;
        while(head&&num<k){
            head=head->next;
            num++;
        }
        if(num<k){
            return res;
        }
        ListNode* pre=reverseKGroup(head,k);
        while(k>0){
            ListNode* temp=res->next;
            res->next=pre;
            pre=res;
            res=temp;
            k--;
        }
        return pre;
    }
};