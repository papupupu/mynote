/*
 * @lc app=leetcode.cn id=1143 lang=cpp
 *
 * [1143] 最长公共子序列
 */

// @lc code=start
#include <vector>
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int res = 0;
        int n = text1.size(), m = text2.size();
        std::vector<std::vector<int>> f(n , std::vector<int>(m, 0));
        for(int i = 0; i < m; i ++){
            if(text1[0] == text2[i])
                f[0][i] = 1;
        }

        for(int i = 0; i < n; i ++){
            if(text2[0] == text1[i])
                f[i][0] = 1;
        }
        
        for(int i = 1; i < n; i ++){
            int max_t = 0;
            for(int j = 1; j < m; j ++){
                if(text1[i] == text2[j]){
                    f[i][j] = max_t + 1;
                    max_t = f[i][j];
                }
                f[i][j] = max_t;
            }
        }
        
        return f[n - 1][m - 1];
    }
};
// @lc code=end

