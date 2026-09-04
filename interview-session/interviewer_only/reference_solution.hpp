#pragma once
#include <vector>
#include <algorithm>
using namespace std;

inline void backtrack(vector<int>& nums, int start, int target, vector<int>& current, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    for (int i = start; i < (int)nums.size(); i++) {
        if (nums[i] > target) continue;
        current.push_back(nums[i]);
        backtrack(nums, i + 1, target - nums[i], current, result);
        current.pop_back();
    }
}

inline vector<vector<int>> referenceSolution(vector<int> nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> current;
    backtrack(nums, 0, target, current, result);
    return result;
}
