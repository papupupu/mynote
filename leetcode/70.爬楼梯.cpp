/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 */

// @lc code=start
class Solution {
public:
    int climbStairs(int n) {
        vector<int> f(n + 1, 0);
        f[0] = f[1] = 1;
        for(int i = 2; i <= n; i ++){
            f[i] = f[i - 2] + f[i - 1];
        }
        return f[n];

    }
};
// @lc code=end

