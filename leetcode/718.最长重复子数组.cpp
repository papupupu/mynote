/*
 * @lc app=leetcode.cn id=718 lang=cpp
 *
 * [718] 最长重复子数组
 */

// @lc code=start
#include <algorithm>
#include <vector>
class Solution {
public:
  int findLength(vector<int> &nums1, vector<int> &nums2) {
    /*
    int res = 0;
    int n = nums1.size(), m = nums2.size();
    vector<vector<int>> f(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(nums1[i] == nums2[j]){
                if((i -1) != 0 && (j - 1) != 0)
                    res[i][j] = res[i -1][j - 1] + 1;
                else
                    res[i][j] = 1;
            }
        }
        res = max(res, f[i][j]);
      }
    }
    return res;
    */
    int n = nums1.size(), m = nums2.size();
    std::vector<vector<int>> res(n, std::vector<int>(m, 0));
    int ans = INT_MIN;
    for(int i = 0; i < n; i ++){
      for(int j = 0; j < m; j ++){
        if(!j || !i){
          if(nums1[i] == nums2[j])
            res[i][j] = 1;
        }
        else{
          if(nums1[i] == nums2[j])
            res[i][j] = res[i - 1][j - 1] + 1;
        }
        ans = std::max(ans, res[i][j]);
      }
    }
    return ans;
  }
};
// @lc code=end

