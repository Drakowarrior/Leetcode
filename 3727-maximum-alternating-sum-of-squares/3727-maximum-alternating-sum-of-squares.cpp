class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();

        // Step 1: square every number (long long, so it cannot overflow)
        vector<long long> a(n);
        for (int i = 0; i < n; i++)
            a[i] = 1LL * nums[i] * nums[i];

        // Step 2: sort — smallest on the left, biggest on the right
        sort(a.begin(), a.end());

        long long ans = 0;
        int k = n / 2;   // number of minus places

        // Step 3: subtract the k smallest squares
        for (int i = 0; i < k; i++)
            ans -= a[i];

        // Step 4: add all the bigger squares
        for (int i = k; i < n; i++)
            ans += a[i];

        return ans;
    }
};