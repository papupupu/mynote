/*
 * @lc app=leetcode.cn id=300 lang=cpp
 *
 * [300] 最长递增子序列
 */

// @lc code=start
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);
        for(int i = 1; i < nums.size(); i ++){
            for(int j = 0; j < i; j ++){
                if(nums[i] > nums[j])
                    nums[i] = max(nums[i], nums[j] + 1);
            }
        }
        return res[n -1];


    }
};
// @lc code=end

