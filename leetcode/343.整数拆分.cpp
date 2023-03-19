/*
 * @lc app=leetcode.cn id=343 lang=cpp
 *
 * [343] 整数拆分
 */

// @lc code=start
class Solution {
public:
    int integerBreak(int n) {
        vector<int> res(n + 1, 1);
        for(int i = 2; i <= n; i++){
            for(int j = 1; j < i; j ++)
                res[i] = max(res[i], max(res[j], j) * max(res[i - j], i - j));
        }
        return res[n];
    }
};
// @lc code=end

