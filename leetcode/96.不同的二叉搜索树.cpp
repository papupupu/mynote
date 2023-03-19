/*
 * @lc app=leetcode.cn id=96 lang=cpp
 *
 * [96] 不同的二叉搜索树
 */

// @lc code=start
class Solution {
public:
    int numTrees(int n) {
        vector<int> res(n + 1, 1);
        int sum;
        for(int i = 1; i <= n; i ++){
            sum = 0;
            //j是选中的根节点，res[j - 1]是左子树的可能性,res[i - j]是右子树的可能性
            for(int j = 1; j <= i; j ++){
               sum += res[j -1] * res[i - j];
            }
            res[i] = sum;
        }
        return res[n];
    }
};
// @lc code=end

