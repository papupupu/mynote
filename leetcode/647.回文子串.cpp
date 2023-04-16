/*
 * @lc app=leetcode.cn id=647 lang=cpp
 *
 * [647] 回文子串
 */

// @lc code=start
class Solution {
public:
    // f[i][j] = f[i + 1][j - 1] && (s[i] == s[j])
    int countSubstrings(string s) {
        /*
        int n = s.size();
        vector<vector<bool>> f(n + 1, vector<bool>(n + 1, false));
        int res = 0;
        for(int i = n; i >= 1; i --) 
            for (int j = i; j <= n; j ++) {
                if(i == j){
                    f[i][j] = true;
                }
                else if(j - i == 1){
                    f[i][j] = (s[i] == s[j]);
                }
                else{
                    f[i][j] = ((s[i] == s[j]) && f[i + 1][j - 1]);
                }
                if(f[i][j]){
                    res ++;
                }
            }
        return res;
        */
        
        int n = s.size();
        
        vector<bool> f(n, false);
        int res = 0;
        for(int i = n - 1; i >= 0; i --){
            for(int j = n - 1; j >= 0; j --){
                if(i == j){
                    f[j] = true;
                }
                else if(i - j == 1){
                    if(s[i] == s[j])
                        f[j] == true;
                    // f[j] = (s[i] == s[j]);
                }
                else{
                    f[j] = f[j - 1] && (s[i] == s[j]);
                }
                if(f[j]){
                    res ++;
                }
            }
        }
        return res;
    }
};
// @lc code=end

