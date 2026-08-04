class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        unordered_set<int> seen(nums.begin(), nums.end());

        int mn = *min_element(nums.begin(), nums.end());
        int mx = *max_element(nums.begin(), nums.end());

        vector<int> ans;

        for (int x = mn; x <= mx; x++) {
            if (!seen.count(x)) {
                ans.push_back(x);
            }
        }

        return ans;
    }
};