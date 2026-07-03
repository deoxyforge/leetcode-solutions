class Solution {
public:
    using ll = long long;

    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        vector<vector<pair<int, int>>> g(n);
        vector<int> indeg(n, 0);

        for (auto &e : edges) {
            g[e[0]].push_back({e[1], e[2]});
            indeg[e[1]]++;
        }

        // Topological order
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0) q.push(i);
        }

        vector<int> topo;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (auto &[v, w] : g[u]) {
                if (--indeg[v] == 0) q.push(v);
            }
        }

        auto check = [&](int mn) {
            const ll INF = (1LL << 60);
            vector<ll> dist(n, INF);
            dist[0] = 0;

            for (int u : topo) {
                if (dist[u] == INF) continue;
                if (u != 0 && u != n - 1 && !online[u]) continue;

                for (auto &[v, w] : g[u]) {
                    if (w < mn) continue;
                    if (v != n - 1 && !online[v]) continue;

                    if (dist[u] + (ll)w < dist[v]) {
                        dist[v] = dist[u] + (ll)w;
                    }
                }
            }

            return dist[n - 1] <= k;
        };

        if (!check(0)) return -1;

        int lo = 0, hi = 1000000000;
        while (lo < hi) {
            int mid = lo + (hi - lo + 1) / 2;
            if (check(mid))
                lo = mid;
            else
                hi = mid - 1;
        }

        return lo;
    }
};