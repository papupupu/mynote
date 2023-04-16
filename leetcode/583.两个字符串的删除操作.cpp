/*
 * @lc app=leetcode.cn id=583 lang=cpp
 *
 * [583] 两个字符串的删除操作
 */

// @lc code=start
#include <vector>
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        std::vector<std::vector<int>> res(n + 1, std::vector<int>(m + 1, 0));
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++){
                res[i][j] = max(res[i - 1][j], res[i][j - 1]);
                if(word1[i - 1] == word2[j - 1])
                    res[i][j] = res[i - 1][j - 1] + 1;
            }
        }
        return (m + n - 2 * res[n][m]);
    }
};
// @lc code=end

