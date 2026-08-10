constexpr int N=1e5+1;
uint8_t dp[N];
class Solution {
public:
    static bool winnerSquareGame(int n) {
        memset(dp, 0, n+1);
        for (int i=1; i<=n; i++) {
            for (int k=1; k*k<=i; k++) {
                if (dp[i-k*k]==0) {
                    dp[i]=1;
                    break;
                }
            }
        }
        return dp[n];
    }
};



auto init = []()
{ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();