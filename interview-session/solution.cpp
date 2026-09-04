#include <algorithm>
#include <vector>
using namespace std;

void recurse(const vector<int>& nums, int index, int remaining, vector<int> combo, vector<vector<int>>& result) {
    if (remaining == 0) {
        result.emplace_back(combo);
        return;
    }

    for (int i = index; i < nums.size(); ++i) {
        if (i > index && nums[i] > remaining) break;

        combo.emplace_back(nums[i]);

        recurse(nums, i + 1, remaining - nums[i], combo, result);

        combo.pop_back();
    }
}

vector<vector<int>> solution(vector<int>& nums, int target) {
    vector<vector<int>> result;

    if (nums.empty()) return result;

    std::sort(nums.begin(), nums.end());

    vector<int> combo;
    combo.reserve(std::min(static_cast<int>(nums.size()), target / nums[0]));

    recurse(nums, 0, target, combo, result);

    return result;
}