/*
 * @lc app=leetcode.cn id=213 lang=cpp
 *
 * [213] 打家劫舍 II
 */

// @lc code=start
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> pp(2, 0), p(2, 0), res(2, 0);
        int n = nums.size();
        int ans = INT_MIN;
        if(n < 4){
            for(int& a : nums)
                ans = max(ans, a);
            return ans; 
        }
        //不偷第一家
        p[1] = nums[2], p[0] = nums[1];
        pp[1] = nums[1], pp[0] = 0;
        for(int i = 4; i <= n; i ++){
            res[0] = max(p[1], p[0]);
            res[1] = max(pp[0], pp[1])+ nums[i - 1];
            pp[0] = p[0];
            pp[1] = p[1];
            p[1] = res[1];
            p[0] = res[0];
        }
        ans = max(res[0], res[1]); 
        
       //偷第一家 
        p[1] = nums[2] + nums[0], p[0] = nums[0];
        pp[1] = INT_MIN, pp[0] = nums[0];
        for(int i = 4; i <= n; i ++){
            res[0] = max(p[1], p[0]);
            res[1] = max(pp[0], pp[1])+ nums[i - 1];
            pp[0] = p[0];
            pp[1] = p[1];
            p[1] = res[1];
            p[0] = res[0];
        }
        ans = max(ans, res[0]);
        return ans;
    }
};
// @lc code=end

