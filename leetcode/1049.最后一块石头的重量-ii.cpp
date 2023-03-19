/*
 * @lc app=leetcode.cn id=1049 lang=cpp
 *
 * [1049] 最后一块石头的重量 II
 */

// @lc code=start
/*
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        //思路转化有点难;两堆石头差值最小的时候可以推出有可以由抵消实现
        //此时就是最优解;
        //两堆石头和为sum不变
        //差值最小，即被减去的那一堆负石头<正石头
        //得出负石头 < sum/2 且 越接近sum/2越好
        //即01背包，容量为j = sum/2, i = 石头数量
    
        int n = stones.size();
        if(n == 1)
            return stones[0];
        int sum = 0;
        for(int &a: stones)
            sum += a;
        int limit = sum / 2;
        vector<vector<int>> f(n + 1, vector<int>(sum + 1, 0));
        for(int i = 1; i <= n; i ++){
            for(int j = 0; j <= limit; j ++){
                f[i][j] = f[i - 1][j];
                if(stones[i - 1] <= j){
                   f[i][j] = max(f[i][j], f[i - 1][j - stones[i - 1]] + stones[i - 1]); 
                }
            }
        }
        return  sum - 2 * f[n][limit];
    }
};
*/
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        //思路转化有点难;两堆石头差值最小的时候可以推出有可以由抵消实现
        //此时就是最优解;
        //两堆石头和为sum不变
        //差值最小，即被减去的那一堆负石头<正石头
        //得出负石头 < sum/2 且 越接近sum/2越好
        //即01背包，容量为j = sum/2, i = 石头数量
    
        int n = stones.size();
        if(n == 1)
            return stones[0];
        int sum = 0;
        for(int &a: stones)
            sum += a;
        int limit = sum / 2;
        //vector<vector<int>> f(n + 1, vector<int>(sum + 1, 0));
        vector<int> f(limit + 1, 0);
        for(int i = 1; i <= n; i ++){
            for(int j = limit; j >= 0; j --){ 
                if(stones[i - 1] <= j){
                   f[j] = max(f[j], f[j - stones[i - 1]] + stones[i - 1]); 
                }
            }
        }
        return  sum - 2 * f[limit];
    }
};
// @lc code=end

