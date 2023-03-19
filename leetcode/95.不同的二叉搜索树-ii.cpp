/*
 * @lc app=leetcode.cn id=95 lang=cpp
 *
 * [95] 不同的二叉搜索树 II
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        return dfs(1, n);
    }
    vector<TreeNode*> dfs(int l, int r){
        vector<TreeNode*> res; 
        if(l > r){
            res.push_back(NULL);
            return res;
        }   
        
        for(int i = l; i <= r; i ++){
            //如果放在这里，你存好的结果里,相同的i实际上每次都是被改变
            //TreeNode* root = new TreeNode(i);
            auto ltrees = dfs(l, i - 1);
            auto rtrees = dfs(i + 1, r); 
            for(auto &ltree: ltrees){
                for(auto &rtree: rtrees){
                    //注意你的root节点必须放进循环中，因为这样你的root才是每次新建的
                    TreeNode* root = new TreeNode(i);
                    root -> left = ltree;
                    root -> right = rtree;
                    res.push_back(root); 
                }
            }
        }
        return res;
    }
};
// @lc code=end

