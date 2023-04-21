/*
 * @lc app=leetcode.cn id=739 lang=cpp
 *
 * [739] 每日温度
 */

// @lc code=start
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> s;
        int n = temperatures.size();
        vector<int> answer(n, 0);
        for(int i = n - 1; i >= 0; i --){
            while(!s.empty() && temperatures[i] >= temperatures[s.top() - 1]){
                s.pop();
            }
            if(s.empty())
                answer[i] = 0;
            else
                answer[i] = s.top() - i - 1;
            //printf("%d天 res = %d", i + 1, answer[i]);
            s.push(i + 1);
        }
        return answer;
        
    }
};
// @lc code=end

