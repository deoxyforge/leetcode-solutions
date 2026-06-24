class Solution {
public:
    static constexpr long long MOD = 1e9 + 7;

    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix& A, const Matrix& B) {
        int n = A.size();

        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (A[i][k] == 0) continue;

                for (int j = 0; j < n; j++) {
                    if (B[k][j] == 0) continue;

                    C[i][j] =
                        (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }

        return C;
    }

    Matrix power(Matrix base, long long exp) {
        int n = base.size();

        Matrix result(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            result[i][i] = 1;
        }

        while (exp) {
            if (exp & 1) {
                result = multiply(result, base);
            }

            base = multiply(base, base);
            exp >>= 1;
        }

        return result;
    }

    vector<long long> multiplyVec(
        const Matrix& M,
        const vector<long long>& v
    ) {
        int n = M.size();

        vector<long long> res(n, 0);

        for (int i = 0; i < n; i++) {
            long long cur = 0;

            for (int j = 0; j < n; j++) {
                cur = (cur + M[i][j] * v[j]) % MOD;
            }

            res[i] = cur;
        }

        return res;
    }

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        if (n == 1) return m;

        int S = 2 * m;

        Matrix T(S, vector<long long>(S, 0));

        for (int x = 0; x < m; x++) {

            // DOWN(x) -> UP(y), y < x
            for (int y = 0; y < x; y++) {
                T[m + y][x] = 1;
            }

            // UP(x) -> DOWN(y), y > x
            for (int y = x + 1; y < m; y++) {
                T[y][m + x] = 1;
            }
        }

        vector<long long> init(S, 0);

        // Length = 2 states
        for (int b = 0; b < m; b++) {

            init[b] = b;              // a < b
            init[m + b] = m - 1 - b; // a > b
        }

        Matrix P = power(T, n - 2);

        vector<long long> finalState =
            multiplyVec(P, init);

        long long ans = 0;

        for (long long x : finalState) {
            ans = (ans + x) % MOD;
        }

        return (int)ans;
    }
};