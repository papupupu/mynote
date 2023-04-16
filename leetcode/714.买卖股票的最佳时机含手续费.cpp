/*
 * @lc app=leetcode.cn id=714 lang=cpp
 *
 * [714] 买卖股票的最佳时机含手续费
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        if(prices.size() == 1)
            return 0;
        vector<int> res{0, -1 * prices[0]};
        auto p = res;
        for(int i = 1; i < prices.size(); i ++){
            res[0] = max(p[0], p[1] + prices[i] - fee);
            res[1] = max(p[1], p[0] - prices[i]);
            p = res;
        }
        return res[0];
    }

};
// @lc code=end

