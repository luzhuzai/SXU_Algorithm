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