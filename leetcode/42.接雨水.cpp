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