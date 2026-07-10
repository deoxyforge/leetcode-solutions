class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                     vector<vector<int>>& queries) {
        vector<pair<int,int>> ord;
        ord.reserve(n);
        for (int i = 0; i < n; i++)
            ord.push_back({nums[i], i});
        sort(ord.begin(), ord.end());

        // position of each original node in sorted order
        vector<int> pos(n);
        for (int i = 0; i < n; i++)
            pos[ord[i].second] = i;

        // nxt[i] = farthest position reachable in one edge
        vector<int> nxt(n);
        int r = 0;
        for (int i = 0; i < n; i++) {
            while (r + 1 < n &&
                   ord[r + 1].first - ord[i].first <= maxDiff)
                r++;
            nxt[i] = r;
        }

        // component right boundary
        vector<int> compRight(n);
        int i = 0;
        while (i < n) {
            int far = nxt[i];
            int j = i;
            while (j <= far) {
                far = max(far, nxt[j]);
                j++;
            }
            for (int k = i; k < j; k++)
                compRight[k] = far;
            i = j;
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> up(LOG, vector<int>(n));

        for (int i = 0; i < n; i++)
            up[0][i] = nxt[i];

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++)
                up[k][i] = up[k - 1][ up[k - 1][i] ];
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int a = pos[q[0]];
            int b = pos[q[1]];
            if (a > b) swap(a, b);

            if (a == b) {
                ans.push_back(0);
                continue;
            }

            if (compRight[a] < b) {
                ans.push_back(-1);
                continue;
            }

            int cur = a;
            int steps = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < b) {
                    cur = up[k][cur];
                    steps += 1 << k;
                }
            }

            ans.push_back(steps + 1);
        }

        return ans;
    }
}; //github 
