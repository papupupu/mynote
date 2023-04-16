/*
 * @lc app=leetcode.cn id=198 lang=cpp
 *
 * [198] 打家劫舍
 */

// @lc code=start
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> pp(2, 0), p(2, 0), res(2, 0);
        p[1] = nums[0];
        if(n == 1)
            return p[1];
        for(int i = 2; i <= n; i ++){
            res[0] = max(p[0], p[1]);
            res[1] = max(pp[0], pp[1]) + nums[i - 1];
            pp[0] = p[0];
            pp[1] = p[1];
            p[0] = res[0];
            p[1] = res[1];
        }
        return max(res[0], res[1]);
        

        /*
        vector<vector<int>> f(n + 1, vector<int>(2,0));
        f[0].first = false;
        f[0].second = 0;
        for(int i = 1; i <= n; i ++){
            if(!f[i - 1].first){
                f[i].first = true;
                f[i].second = f[i - 1].second + nums[i - 1];
            }
            else{
                f[i].first = false;
                f[i].second = f[i - 1].second;
            }
        }
        f[1][1] = nums[0];
        f[1][0] = 0;
        for(int i = 2; i <= n; i ++){
                f[i][0] = max(f[i - 1][1], f[i - 1][0]);
                //printf("f[%d][0] = %d\n", i,f[i][0]);
                f[i][1] =max(f[i - 2][1], f[i - 2][0]) + nums[i - 1];
                //printf("f[%d][1] = %d\n", i,f[i][1]);
        }
        return max(f[n][1], f[n][0]);
        */

    }
};
// @lc code=end

