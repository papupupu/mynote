/*
 * @lc app=leetcode.cn id=516 lang=cpp
 *
 * [516] 最长回文子序列
 */

// @lc code=start
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> res(n, vector<int>(n, 0));
        // res[i][j]  = res[i + 1][j - 1]
        for(int i = n - 1; i >= 0; i --){
            for (int j = i; j >= i; j --) {
                if(i == j)
                    res[i][j] = 1;
                else if(i - j == 1)
                    res[i][j] = (s[i] == s[j] ? 2 : 0);
                else
                    res[i][j] = res[i + 1][j - 1] + (s[i] == s[j] ? 2 : 0);
                printf("res[%d][%d] = %d\n", i, j, res[i][j]);
            }
        }
        return res[0][n - 1];
    }
};
// @lc code=end

