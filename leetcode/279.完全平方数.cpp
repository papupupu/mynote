/*
 * @lc app=leetcode.cn id=279 lang=cpp
 *
 * [279] 完全平方数
 */

// @lc code=start
class Solution {
public:
    int numSquares(int n) {
        vector<int> nums((int)sqrt(n) + 1);
        vector<int> f(n + 1, 10000);
        f[0] = 0;
        for(int i = 1; i < nums.size(); i ++){
            nums[i] = i * i;
        }
        for(int i = 1;  i < nums.size(); i ++){
            for(int j = nums[i]; j <= n; j ++){
                f[j] = min(f[j], f[j - nums[i]] + 1);
            }
        }
        return f[n];
    }
};
// @lc code=end

