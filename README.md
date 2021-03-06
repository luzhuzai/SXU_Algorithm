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

#### leetcode42.接雨水
找规律求解
```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int nums = height.size();
        vector<int> left(nums);
        vector<int> right(nums);
        
        left[0] = height[0];
        for(int i=1;i<nums;i++){
            left[i] = max(left[i-1],height[i]);
        }
        right[nums-1] = height[nums-1];
        for(int i=nums-2;i>=0;i--){
            right[i] = max(right[i+1],height[i]);
        }
        int res = 0;
        for(int i=0;i<nums;i++){
            res += min(left[i],right[i]) - height[i];
        }
        return res;
    }
};
```
双指针做法
```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0;
        int left = 0, right = height.size()-1;
        int leftMax = height[0],rightMax = height[height.size()-1];
        while(left<right){
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (height[left] < height[right]) {
                res += leftMax - height[left];
                ++left;
            } else {
                res += rightMax - height[right];
                --right;
            }
        }
        return res;
    }
};
```

#### leetcode39.组合总和
使用深搜递归
```cpp
class Solution {
public:
    void dfs(vector<vector<int>>& res,vector<int>& ans,vector<int>& candidates, int target,int dex){
        if(dex == candidates.size()){
            return ;
        }
        if(target==0){
            res.push_back(ans);
            return;
        }
        dfs(res,ans,candidates,target,dex+1);
        if(target-candidates[dex]>=0){
            ans.push_back(candidates[dex]);
            dfs(res,ans,candidates,target-candidates[dex],dex);
            ans.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> combine;
        dfs(ans, combine, candidates, target, 0);
        return ans;

    }
};
```
#### leetcode142.环形链表
使用哈希表
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> mp;
        while(head){
            if(mp.count(head)){
                return head;
            }
            mp.insert(head);
            head = head -> next;
        }
        return nullptr;
    }
};
```
使用快慢指针
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;

        while(fast!=nullptr){
            slow = slow -> next;
            if(fast->next == nullptr){
                return nullptr;
            }
            fast = fast->next->next;
            if(fast == slow){
                ListNode* ptr=head;
                while (ptr != slow) {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return ptr;
            }
        }
        return nullptr;
    }
};
```