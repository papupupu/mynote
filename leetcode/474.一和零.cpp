/*
 * @lc app=leetcode.cn id=474 lang=cpp
 *
 * [474] 一和零
 */

// @lc code=start
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));
        for(auto& s : strs)
        {
            int a = 0, b = 0;
            for(auto c : s){
                if(c == '0') a ++;
                else b++;
            }
            for(int i = m; i >= a; i --){
                for (int j = n; j >= b; j --) {
                    f[i][j] = max(f[i - a][j - b] + 1, f[i][j]); 
                }
            }
        }
        return f[m][n];
    }
};
// @lc code=end

