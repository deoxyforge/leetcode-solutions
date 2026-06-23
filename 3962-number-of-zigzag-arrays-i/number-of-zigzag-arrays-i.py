class Solution:
    def zigZagArrays(self, n: int, l: int, r: int) -> int:
        MOD = 10**9 + 7
        m = r - l + 1

        # Length = 2
        up = [0] * (m + 1)
        down = [0] * (m + 1)

        for x in range(1, m + 1):
            up[x] = x - 1
            down[x] = m - x

        for _ in range(3, n + 1):
            pref = [0] * (m + 1)
            suff = [0] * (m + 2)

            for i in range(1, m + 1):
                pref[i] = (pref[i - 1] + down[i]) % MOD

            for i in range(m, 0, -1):
                suff[i] = (suff[i + 1] + up[i]) % MOD

            new_up = [0] * (m + 1)
            new_down = [0] * (m + 1)

            for x in range(1, m + 1):
                new_up[x] = pref[x - 1]
                new_down[x] = suff[x + 1]

            up = new_up
            down = new_down

        ans = 0
        for x in range(1, m + 1):
            ans = (ans + up[x] + down[x]) % MOD

        return ans