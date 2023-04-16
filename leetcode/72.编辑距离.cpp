/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 */

// @lc code=start
#include <vector>
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        std::vector<std::vector<int>> res(n + 1, std::vector<int>(m + 1, 0));
        for(int i = 0; i <= n; i ++)
            res[i][0] = i;
        for(int i = 0; i <= m; i ++)
            res[0][i] = i;


        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++){
                res[i][j] = min(res[i][j - 1] + 1, res[i - 1][j] + 1);
                res[i][j] = min(res[i][j], res[i - 1][j - 1] + (word1[i - 1] != word2[j - 1]));
            }
        }
        return res[n][m];
    }
};
// @lc code=end

