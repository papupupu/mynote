/*
 * @lc app=leetcode.cn id=496 lang=cpp
 *
 * [496] 下一个更大元素 I
 */

// @lc code=start
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> m;
        for(int i = 0; i < nums2.size(); i ++){
            m.insert({nums2[i], i});
        }
        stack<int> s;
        vector<int> res = nums2;
        for(int i = nums2.size() - 1; i >= 0; i --){
            while(!s.empty() && nums2[i] >= s.top())
                s.pop();
            if(s.empty())
                res[i] = -1;
            else
                res[i] = s.top();
            s.push(nums2[i]);
        }
        vector<int> ans(nums1.size(), -1);
        for(int i = 0; i < nums1.size(); i ++){
            ans[i] = res[m[nums1[i]]];
        }
        return ans;
    }
};
// @lc code=end

