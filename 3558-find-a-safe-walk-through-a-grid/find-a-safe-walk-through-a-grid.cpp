#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();

        const int INF = 1e9;
        vector<vector<int>> dist(m, vector<int>(n, INF));

        deque<pair<int,int>> dq;

        dist[0][0] = grid[0][0];
        dq.push_front({0, 0});

        int dirs[5] = {1, 0, -1, 0, 1};

        while (!dq.empty()) {
            auto [r, c] = dq.front();
            dq.pop_front();

            for (int k = 0; k < 4; k++) {
                int nr = r + dirs[k];
                int nc = c + dirs[k + 1];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                int cost = dist[r][c] + grid[nr][nc];

                if (cost < dist[nr][nc]) {
                    dist[nr][nc] = cost;
                    if (grid[nr][nc] == 0)
                        dq.push_front({nr, nc});
                    else
                        dq.push_back({nr, nc});
                }
            }
        }

        return health - dist[m - 1][n - 1] >= 1;
    }
};