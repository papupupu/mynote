/*
 * @lc app=leetcode.cn id=309 lang=cpp
 *
 * [309] 最佳买卖股票时机含冷冻期
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> profit(prices.size() + 1, {0, - 1 * prices[0], 0});
        for(int i = 1; i < prices.size(); i ++){
            profit[i][0] = max(profit[i - 1][0], profit[i -1][2]);
            profit[i][1] = max(profit[i - 1][1], profit[i -1][0] - p);
            profit[i][2] = max(profit[i - 1][1] + p);
        }
        return max(profit[n - 1][0], profit[n -1][2]);
    }
};
// @lc code=end

