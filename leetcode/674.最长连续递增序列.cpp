/*
 * @lc app=leetcode.cn id=674 lang=cpp
 *
 * [674] 最长连续递增序列
 */

// @lc code=start
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int n = nums.size();
        int ans = 1, p = 1;
        for(int i = 1; i < n; i ++){
            if(nums[i] > nums[i - 1]){
                ans = max(p + 1, ans);
                p = p + 1;
            }
            else {
                p = 1;
            }
        }
        return ans;
    }
};
// @lc code=end

