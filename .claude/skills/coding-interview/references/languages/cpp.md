# Starter bundle — C++

`PROBLEM.md`: the problem statement you wrote, saved verbatim (description,
constraints, examples) — plain Markdown, not part of the build.

`solution.cpp`:
```cpp
#include <vector>
using namespace std;

// nums: vector<int> -- 2 <= nums.size() <= 10^4, -10^9 <= nums[i] <= 10^9
// target: int -- -10^9 <= target <= 10^9
// Returns: vector<int> -- the two indices i, j (i != j) such that nums[i] + nums[j] == target
vector<int> solution(vector<int>& nums, int target) {
    // TODO: implement your solution here
    return {};
}
```
(The parameter/bounds comment is illustrative — replace it with the actual
signature and constraints for whatever problem you wrote.)

`interviewer_only/reference_solution.hpp`:
```cpp
#pragma once
#include <vector>
#include <unordered_map>
using namespace std;

inline vector<int> referenceSolution(vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < (int)nums.size(); i++) {
        auto it = seen.find(target - nums[i]);
        if (it != seen.end()) return {it->second, i};
        seen[nums[i]] = i;
    }
    return {};
}
```

`run_tests.cpp`:
```cpp
#include <iostream>
#include <vector>
#include "solution.cpp"
#include "interviewer_only/reference_solution.hpp"
using namespace std;

int main() {
    vector<pair<vector<int>, int>> testCases = {
        {{2, 7, 11, 15}, 9},
        {{3, 2, 4}, 6},
    };

    int passed = 0;
    for (size_t i = 0; i < testCases.size(); i++) {
        auto nums = testCases[i].first;
        auto expected = referenceSolution(nums, testCases[i].second);
        auto actual = solution(nums, testCases[i].second);
        bool ok = (actual == expected); // adjust if order doesn't matter
        passed += ok;
        cout << "Test case " << i + 1 << ": " << (ok ? "PASS" : "FAIL") << endl;
    }
    cout << "\n" << passed << "/" << testCases.size() << " passed" << endl;
}
```

Compile with `g++ -std=c++17 run_tests.cpp -o run_tests && ./run_tests`.
