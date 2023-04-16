/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        /*
        int min_price = INT_MAX;
        int res = INT_MIN;
        for(auto price : prices){
            min_price = min(min_price, price);
            res = max(res, price - min_price);
        }
        return res;
        */
        if(prices.size() == 1)
            return 0;
        vector<int> p = {0, -1 * prices[0]}, res(2, 0);
        for(int i = 1; i < prices.size(); i ++){
            res[0] = max(0, max(p[0], p[1] + prices[i]));
            res[1] = max(p[1], -1 * prices[i]);
            p = res;
        }
        return res[0];
    }
};
// @lc code=end

