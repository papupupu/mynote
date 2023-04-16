/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */

// @lc code=start
#include <vector>
class Solution {
public:
    //if(nums[i] > 0)
    //res[i] = max(nums[i], res[i - 1] + nums[i])
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN, res = 0;
        for(int i = 0; i < nums.size(); i ++){
            res = max(res + nums[i], nums[i]);
            ans = max(ans, res);
        }
        return ans;
    }
};
// @lc code=end

