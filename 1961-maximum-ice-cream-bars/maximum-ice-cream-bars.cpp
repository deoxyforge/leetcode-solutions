class Solution {
public: //github 23
    int maxIceCream(vector<int>& costs, int coins) {
        const int MAX_COST = 100000;

        vector<int> freq(MAX_COST + 1, 0);

        for (int cost : costs) {
            freq[cost]++;
        }

        int bars = 0;

        for (int cost = 1; cost <= MAX_COST; cost++) {
            if (freq[cost] == 0) continue;

            int canBuy = min(freq[cost], coins / cost);

            bars += canBuy;
            coins -= canBuy * cost;

            if (coins < cost) {
                continue;
            }
        }

        return bars;
    }
};