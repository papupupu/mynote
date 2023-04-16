/*
 * @lc app=leetcode.cn id=188 lang=cpp
 *
 * [188] 买卖股票的最佳时机 IV
 */

// @lc code=start
class Solution {
public:
  int maxProfit(int k, vector<int> &prices) {
    if (prices.size() < 2 || k == 0)
      return 0;
    vector<vector<int>> profit(k + 1, {0, -1 * prices[0]});
    int res = 0;
    for (int p : prices) {
    profit[0][1] = max(profit[0][1], -1 * p);
      for (int i = 1; i <= k; i++) {
        profit[i][0] = max(profit[i][0], profit[i - 1][1] + p);
        profit[i][1] = max(profit[i][1], profit[i][0] - p);
        res = max(res, profit[i][0]);
      }
    }
    return res;
  }
};
// @lc code=end

