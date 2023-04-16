/*
 * @lc app=leetcode.cn id=123 lang=cpp
 *
 * [123] 买卖股票的最佳时机 III
 */

// @lc code=start
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        /*
        if(prices.size() == 1)
            return 0;
        vector<int> p{0, -1 * prices[0], 0, - 1 * prices[0], 0};
        auto res = p;
        for(int i = 1; i < prices.size(); i ++){
            res[0] = 0;
            res[1] = max(p[1], p[0] - prices[i]);
            res[2] = max(p[2], p[1] + prices[i]);
            res[3] = max(p[3], p[2] - prices[i]);
            res[4] = max(p[4], p[3] + prices[i]);
            p = res;
        }
        return max(res[0], max(res[2], res[4]));
        */
        //0 1 2 3 4偶数不持有股票
        if(prices.size() == 1)
            return 0;
        vector<int> res{0, - 1 * prices[0], 0, -1 * prices[0], 0};
        for(int p : prices){
            res[0] = 0;
            res[1] = max(res[1], res[0] - p);
            res[2] = max(res[2], res[1] + p);
            res[3] = max(res[3], res[2] - p);
            res[4] = max(res[4], res[3] + p);
        }
        return max(res[0], max(res[2], res[4]));
        
    }
};
// @lc code=end

