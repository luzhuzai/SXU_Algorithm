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