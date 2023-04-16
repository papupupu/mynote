/*
 * @lc app=leetcode.cn id=1035 lang=cpp
 *
 * [1035] 不相交的线
 */

// @lc code=start
#include <vector>
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        /*
        int n = nums1.size(), m = nums2.size();
        std::vector<std::vector<int>> res(n, std::vector<int>(m, 0));
        for(int i = 0; i < n; i ++){
            for(int j = 0; j < m; j ++){
                if(!i || !j){
                    if(nums1[i] == nums2[j])
                        res[i][j] = 1;
                }
                else{
                    res[i][j] = res[i - 1][j - 1];
                    if(nums1[i] == nums2[j]){
                        res[i][j] = res[i - 1][j - 1] + 1;
                    }
                    else res[i][j] = max(res[i - 1][j], res[i][j - 1]);
                }
            }
        }
        return res[n - 1][m - 1];
        */
        int n = nums1.size(), m = nums2.size();
        std::vector<vector<int>> res(n + 1, std::vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i ++) {
            for(int j = 1; j <= m; j ++){
                res[i][j] = max(res[i - 1][j], res[i][j - 1]);
                if(nums1[i] == nums2[j]){
                    res[i][j] = max(res[i][j], res[i - 1][j - 1] + 1);
                }
            }
        }
        return res[n][m];
    }
};
// @lc code=end

