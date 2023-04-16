/*
 * @lc app=leetcode.cn id=518 lang=cpp
 *
 * [518] 零钱兑换 II
 */

// @lc code=start
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<int> f(amount + 1, 0);
        f[0] = 1;
        for(int i = 1; i <= n; i ++){
            for(int j = coins[i -1]; j <= amount; j ++){
                f[j] += f[j], f[j - coins[i - 1]] ;
            } 
        }
        return f[n];
    }
};
// @lc code=end

