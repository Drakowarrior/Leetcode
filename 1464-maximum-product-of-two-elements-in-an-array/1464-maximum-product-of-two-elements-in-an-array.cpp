class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        int curMax = nums[0];

        for (int i = 1; i < n; i++) {
            ans = max(ans, (curMax - 1) * (nums[i] - 1));
            curMax = max(curMax, nums[i]);
        }

        return ans;
    }
};