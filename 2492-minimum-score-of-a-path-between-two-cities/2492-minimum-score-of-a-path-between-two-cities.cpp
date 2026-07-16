class Solution {
public:
vector<vector<pair<int,int>>> adj;
    vector<int> vis;
    int ans = INT_MAX;

    void dfs(int node) {
        vis[node] = 1;

        for (auto &it : adj[node]) {
            int nei = it.first;
            int wt = it.second;

            ans = min(ans, wt);

            if (!vis[nei])
                dfs(nei);
        }
    }
    int minScore(int n, vector<vector<int>>& roads) {
        adj.resize(n + 1);
        vis.assign(n + 1, 0);

        for (auto &r : roads) {
            int u = r[0], v = r[1], w = r[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        dfs(1);

        return ans;
    }
};