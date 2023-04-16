/*
 * @lc app=leetcode.cn id=494 lang=cpp
 *
 * [494] 目标和
 */

// @lc code=start
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for(auto &a : nums)
            sum += a;
        if(sum + target < 0)
            return 0;
        if((sum + target) % 2)
            return 0;
        int limit = (sum + target) / 2;
        int n = nums.size();
        vector<int> f(limit + 1, 0);
        f[0] = 1;
        for(int i = 1; i <= n; i ++){
            //for(int j = 0; j <= limit; j ++){
            for(int j = limit; j >= nums[i - 1]; j --)
                f[j] =  f[j] + f[j - nums[i -1]];
                //printf("f[%d][%d] = %d\n", i, j, f[i][j]);
            }
        return f[limit];
    }
};
// @lc code=end

