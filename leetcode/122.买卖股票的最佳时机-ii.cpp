/*
 * @lc app=leetcode.cn id=122 lang=cpp
 *
 * [122] 买卖股票的最佳时机 II
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
    vector<int> p{0, -1 * prices[0]}, res(2, 0);
    if(prices.size() ==  1) 
            return p[0];

        for(int i = 1; i < prices.size(); i ++){
            res[1] = max(p[1], p[0] - prices[i]);
            res[0] = max(p[0], p[1] + prices[i]);
            p = res;
            //printf("i = %d, res[0] = %d\n", i, res[0]);
        }
        return res[0];
    }
};
// @lc code=end

