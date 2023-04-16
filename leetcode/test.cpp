/*
 * @lc app=leetcode.cn id=647 lang=cpp
 *
 * [647] 回文子串
 */

// @lc code=start
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main (int argc, char *argv[])
{
        string s = "aaa";
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
}


