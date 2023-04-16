/*
 * @lc app=leetcode.cn id=392 lang=cpp
 *
 * [392] 判断子序列
 */

// @lc code=start
#include <vector>
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int m = s.size(), n = t.size();
        std::vector<std::vector<int>> res(m + 1, std::vector<int>(n + 1, 0));
        for(int i = 1; i <= m; i ++){
            for(int j = 1; j <= n; j ++){
                if(s[i - 1] == t[j - 1]){
                    res[i][j] = res[i - 1][j - 1] + 1;
                }
                else{
                    res[i][j] = max(res[i - 1][j], res[i][j - 1]);
                }
            }
        }
        return res[m][n] == s.size();
    }
};
// @lc code=end

