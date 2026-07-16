class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        vector<int> prefixGcd;
        int mx = 0;

        for (int x : nums) {
            mx = max(mx, x);
            prefixGcd.push_back(std::gcd(x, mx));
        }

        sort(prefixGcd.begin(), prefixGcd.end());

        long long ans = 0;
        int l = 0, r = prefixGcd.size() - 1;

        while (l < r) {
            ans += std::gcd(prefixGcd[l], prefixGcd[r]);
            l++;
            r--;
        }

        return ans;
    }
};