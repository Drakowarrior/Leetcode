class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<int> buydp(k, INT_MAX), selldp(k+1, 0);

        for (auto price : prices) {
            buydp[0] = min(buydp[0], price);
            for (int i = 1; i < k; i++) {
                selldp[i-1] = max(selldp[i-1], price - buydp[i-1]);
                buydp[i] = min(buydp[i], price - selldp[i-1]);
            }
            selldp[k] = max(selldp[k], price - buydp[k-1]);
        }
        return selldp[k];
    }
};