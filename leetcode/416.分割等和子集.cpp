/*
 * @lc app=leetcode.cn id=416 lang=cpp
 *
 * [416] 分割等和子集
 */

// @lc code=start
/*
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if(n < 2)
            return false;
        int sum = 0;
        for(int &a : nums)
            sum += a;
        if(sum % 2)
            return false;
        sum /= 2;
        vector<vector<int>> f(n + 1, vector<int>(sum + 1, 0));
        f[0][0] = 1;
        
        for(int i = 1; i < n; i ++){
            for(int j = 0; j <= sum; j ++){
                if(!j) f[i][j] = 1;
                else{
                    f[i][j] |= f[i - 1][j];
                    if(j >= nums[i - 1])
                        f[i][j] |= f[i - 1][j - nums[i - 1]];
                }
            }
        }
        return f[n - 1][sum];
    }
};
*/
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if(n < 2)
            return false;
        int sum = 0;
        for(int &a : nums)
            sum += a;
        if(sum % 2)
            return false;
        sum /= 2;
        //vector<vector<int>> f(n + 1, vector<int>(sum + 1, 0));
        vector<int> f(sum + 1, 0);
        //f[0][0] = 1;
        f[0] = 1;
        
        for(int i = 1; i < n; i ++){
            for(int j = sum; j >= 1; j --){
                    if(j >= nums[i - 1])
                        f[j] |= f[j - nums[i - 1]];
            }
        }
        return f[sum];
    }
};
// @lc code=end

