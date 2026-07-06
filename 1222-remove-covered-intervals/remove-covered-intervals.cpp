class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });

        int ans = 0;
        int maxEnd = -1;

        for (auto &in : intervals) {
            if (in[1] > maxEnd) {
                ans++;
                maxEnd = in[1];
            }
        }

        return ans;
    }
};