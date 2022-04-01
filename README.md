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

#### LRU缓存
使用双端队列和哈希表
```cpp
class LRUCache {
public:
struct DoubleList{
    DoubleList *left;
    DoubleList *right;
    int key;
    int val;
    DoubleList():left(nullptr),right(nullptr),key(0),val(0){}
    DoubleList(int k,int v):left(nullptr),right(nullptr),key(k),val(v){}
};
    LRUCache(int capacity) {
        this->capacity=capacity;
        size=0;
        head=new DoubleList();
        tail=new DoubleList();
        head->right=tail;
        tail->left=head;
    }
    
    int get(int key) {
        if(mp.count(key)){
            DoubleList* node=mp[key];
            int val=node->val;
            pop(node);
            push_front(node);
            return val;
        }
        else{
            return -1;
        }
    }
    
    void put(int key, int value) {
        if(mp.count(key)){
            DoubleList* node=mp[key];
            pop(node);
            push_front(node);
            node->val=value;
        }
        else{
            if(size==capacity){
                pop_back();
                DoubleList* node=new DoubleList(key,value);
                mp[key]=node;
                push_front(node);
            }
            else{
                size++;
                DoubleList* node=new DoubleList(key,value);
                mp[key]=node;
                push_front(node);
            }
        }
    }

    void pop(DoubleList* node){
        node->left->right=node->right;
        node->right->left=node->left;
    }
    void push_front(DoubleList* node){
        head->right->left=node;
        node->right=head->right;
        node->left=head;
        head->right=node;
    }
    void pop_back(){
        DoubleList* last_node=tail->left;
        pop(last_node);
        mp.erase(last_node->key);
        delete last_node;
    }
    unordered_map<int,DoubleList*>mp;
    DoubleList *head;
    DoubleList *tail;
    int capacity;
    int size;
    
};
```