/*
 * @lc app=leetcode.cn id=139 lang=cpp
 *
 * [139] 单词拆分
 */

// @lc code=start
/*
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> hash;
        for(string& word : wordDict){
            hash.insert(word);
        }
        int n = s.size();
        vector<bool> f(n, false);
        for(int i = 0; i < n; i ++){
            for(int j = i; j >= 0; j --){
                if(!j || f[j - 1]){
                    if(hash.count(s.substr(j, i - j + 1)))
                        f[i] = true;
                }
            }
        }
        return f[n - 1];
    }
};
*/
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<unsigned long long> hash;
        const int p = 131;
        for(string& word : wordDict){
            unsigned long long h = 0;
            for(char c : word){
                h = h * p + c;
            }
            hash.insert(h);
        }
        int n = s.size();
        vector<bool> f(n + 1, false);
        f[0] = true;
        for(int i = 0; i < n; i ++){
            if(f[i]){
                unsigned long long h = 0;
                for(int j = i + 1; j <= n; j ++){
                    h = h * p + s[j];
                    if(hash.count(h)){
                        f[j] = true;
                    }
                }
 
            }
       }
        return f[n];
    }
};
// @lc code=end

