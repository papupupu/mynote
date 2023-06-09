/*
 * @lc app=leetcode.cn id=322 lang=cpp
 *
 * [322] 零钱兑换
 */

// @lc code=start
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<unsigned> f(amount + 1, INT_MAX);
        f[0] = 0;
        for(int i = 0; i < n; i ++){
            for(int j = coins[i]; j <= amount; j ++){
                f[j] = min(f[j], f[j - coins[i]] + 1);
            }
        }
        if(f[amount] == INT_MAX)
            return -1;
        return f[amount];
    }
};
// @lc code=end

