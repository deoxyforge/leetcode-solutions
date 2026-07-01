from collections import deque
from typing import List

class Solution:
    def maximumSafenessFactor(self, grid: List[List[int]]) -> int:
        n = len(grid)

        # Step 1: Multi-source BFS
        dist = [[-1] * n for _ in range(n)]
        q = deque()

        for r in range(n):
            for c in range(n):
                if grid[r][c] == 1:
                    dist[r][c] = 0
                    q.append((r, c))

        dirs = [(1,0),(-1,0),(0,1),(0,-1)]

        while q:
            r, c = q.popleft()
            for dr, dc in dirs:
                nr, nc = r + dr, c + dc
                if 0 <= nr < n and 0 <= nc < n and dist[nr][nc] == -1:
                    dist[nr][nc] = dist[r][c] + 1
                    q.append((nr, nc))

        def can(x):
            if dist[0][0] < x:
                return False

            q = deque([(0, 0)])
            vis = [[False] * n for _ in range(n)]
            vis[0][0] = True

            while q:
                r, c = q.popleft()

                if (r, c) == (n - 1, n - 1):
                    return True

                for dr, dc in dirs:
                    nr, nc = r + dr, c + dc
                    if (0 <= nr < n and 0 <= nc < n and
                        not vis[nr][nc] and dist[nr][nc] >= x):
                        vis[nr][nc] = True
                        q.append((nr, nc))

            return False

        lo, hi = 0, max(max(row) for row in dist)

        while lo <= hi:
            mid = (lo + hi) // 2
            if can(mid):
                lo = mid + 1
            else:
                hi = mid - 1

        return hi