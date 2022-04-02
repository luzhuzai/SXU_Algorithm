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