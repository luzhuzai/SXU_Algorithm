# SXU_Algorithm
## luzaizai的刷题记录

#### leetcode 25.K 个一组翻转链表

方法一：模拟
模拟整个翻转的流程



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
方法二：递归
将多个反转变为一个反转



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

#### leetcode 215.数组中的第K个最大元素
使用c++的优先队列去完成
    

    class Solution {
        public:
            int findKthLargest(vector<int>& nums, int k) {
                priority_queue<int,vector<int>, greater<int>> q;
                for(auto &i:nums){
                    if(q.size()<k){
                        q.push(i);
                    }else{
                        if(i>q.top()){
                            q.pop();
                            q.push(i);
                        }
                    }
                }
                return q.top();
            }
        };