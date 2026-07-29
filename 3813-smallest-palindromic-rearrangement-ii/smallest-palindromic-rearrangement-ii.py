from math import comb

class Solution:
    def smallestPalindrome(self, s: str, k: int) -> str:
        LIMIT = 10 ** 6 + 1

        freq = [0] * 26
        for ch in s:
            freq[ord(ch) - ord('a')] += 1

        half = [f // 2 for f in freq]
        mid = ""
        for i in range(26):
            if freq[i] & 1:
                mid = chr(i + ord('a'))
                break

        def combLimited(n: int, r: int) -> int:
            if r < 0 or r > n:
                return 0
            r = min(r, n - r)

            res = 1
            for i in range(1, r + 1):
                res = res * (n - r + i) // i
                if res >= LIMIT:
                    return LIMIT
            return res

        def countWays(cnt):
            rem = sum(cnt)
            ways = 1

            for c in cnt:
                if c == 0:
                    continue
                ways *= combLimited(rem, c)
                if ways >= LIMIT:
                    return LIMIT
                rem -= c

            return ways

        if countWays(half) < k:
            return ""

        left = []
        m = len(s) // 2

        for _ in range(m):
            for c in range(26):
                if half[c] == 0:
                    continue

                half[c] -= 1
                ways = countWays(half)

                if ways >= k:
                    left.append(chr(c + ord('a')))
                    break

                k -= ways
                half[c] += 1

        left = "".join(left)
        return left + mid + left[::-1]