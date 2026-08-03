struct Solution {
    auto stoneGameIII(vector<int>& a) {
        int dp[3]{}, x[2]{};
        for (int v : a | views::reverse) {
            int r = max(max(v - dp[0], v + x[0] - dp[1]), v + x[0] + x[1] - dp[2]);
            x[1] = exchange(x[0], v);
            dp[2] = exchange(dp[1], exchange(dp[0], r));
        }

        constexpr string_view kAns[]{"Bob", "Tie", "Alice"};
        return string(kAns[clamp(dp[0], -1, 1) + 1]);
    }
};