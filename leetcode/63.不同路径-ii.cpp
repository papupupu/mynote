/*
 * @lc app=leetcode.cn id=63 lang=cpp
 *
 * [63] 不同路径 II
 */

// @lc code=start
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int x = obstacleGrid.size();
        int y = obstacleGrid[0].size();
        if(obstacleGrid[0][0] == 1){
            return 0;
        }
        vector<vector<int>> res(x, vector<int>(y));
        res[0][0] = 1;
        for(int i = 0; i < x; i ++){
            for (int j = 0; j < y; j ++) {
                if(obstacleGrid[i][j])
                    res[i][j] = 0;
                else{
                    if(!i && !j)
                        res[i][j] = 1;
                    else if(!i && j)
                        res[i][j] = res[i][j - 1];
                    else if(i && !j) 
                        res[i][j] = res[i - 1][j]; 
                    else if(i && j)
                        res[i][j] = res[i - 1][j] + res[i][j - 1];
                }
                //printf("res[%d][%d] = %d\n", i , j, res[i][j]);
            }
        }
        return res[x - 1][y -1];
    }
};
// @lc code=end

