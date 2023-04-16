/*
 * @lc app=leetcode.cn id=377 lang=cpp
 *
 * [377] 组合总和 Ⅳ
 */

// @lc code=start
//显然我写错了，我的是完全背包，只考虑每个nums[i]的个数，不考虑顺序的,这个是考虑顺序的，所以下面的做法错了
/*
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> f(target + 1, 0);
        f[0] = 1;
        for(int i = 0; i < n; i ++){
            for (int j = nums[i]; j <= target; j ++) {
                f[j] += f[j - nums[i]];
            }
        }
        return f[target];
    }
}
*/
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int n = nums.size();
        vector<unsigned> f(target + 1, 0);
        f[0] = 1;
        for(int i = 1; i <= target; i ++){
            for(int j = 0; j < n; j ++){
                if(nums[j] <= i)
                    f[i] += f[i - nums[j]];
            }
        }
        return f[target];
       
    }
};
// @lc code=end

