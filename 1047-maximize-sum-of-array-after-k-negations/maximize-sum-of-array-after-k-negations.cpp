class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() && k > 0; i++) {
            if (nums[i] < 0) {
                nums[i] = -nums[i];
                k--;
            }
        }

        int sum = 0;
        int mn = INT_MAX;

        for (int num : nums) {
            sum += num;
            mn = min(mn, num);
        }

        if (k % 2 == 1) {
            sum -= 2 * mn;
        }

        return sum;
    }
};