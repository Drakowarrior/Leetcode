class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        int left = ranges::count_if(nums, [&](int x) { return x < target; });  // bisect_left: the values that come before the targets
        int right = ranges::count_if(nums, [&](int x) { return x <= target; });  // bisect_right: the values up to the last target
        vector<int> indices(right - left);
        iota(indices.begin(), indices.end(), left);
        return indices;       
    }
};