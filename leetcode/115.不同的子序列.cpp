/*
 * @lc app=leetcode.cn id=115 lang=cpp
 *
 * [115] 不同的子序列
 */

// @lc code=start
#include <vector>
class Solution {
public:
    int numDistinct(string s, string t) {
        int n = t.size(), m = s.size();
        std::vector<std::vector<int>> res(n + 1, std::vector<int>(m + 1, 0));
        for(int i = 0; i <= m; i ++)
            res[0][i] = 1;
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++){
                res[i][j] = res[i][j - 1];
                if(t[i - 1] == s[j - 1]){
                   res[i][j] += res[i - 1][j - 1];
                }
                // printf("t = %c, s = %c, res[i][j] = %d\n", t[i - 1], s[j - 1], res[i][j]);
            }
        }
        return res[n][m];
    }
};
// @lc code=end

