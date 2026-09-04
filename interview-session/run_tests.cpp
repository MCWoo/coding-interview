#include <iostream>
#include <vector>
#include <algorithm>
#include "solution.cpp"
#include "interviewer_only/reference_solution.hpp"
using namespace std;

vector<vector<int>> normalize(vector<vector<int>> combos) {
    for (auto& c : combos) sort(c.begin(), c.end());
    sort(combos.begin(), combos.end());
    return combos;
}

void printCombos(const vector<vector<int>>& combos) {
    cout << "[";
    for (size_t i = 0; i < combos.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < combos[i].size(); j++) cout << combos[i][j] << (j + 1 < combos[i].size() ? "," : "");
        cout << "]" << (i + 1 < combos.size() ? "," : "");
    }
    cout << "]";
}

int main() {
    struct TestCase { vector<int> nums; int target; };
    vector<TestCase> testCases = {
        {{2, 3, 5, 7}, 7},
        {{1, 2, 3}, 4},
        {{4, 1, 8, 3}, 100},
        {{30,25,14,3,2,1}, 30},
        {{}, 10},
        {{30}, 5},
    };

    int passed = 0;
    for (size_t i = 0; i < testCases.size(); i++) {
        auto numsCopy1 = testCases[i].nums;
        auto numsCopy2 = testCases[i].nums;
        auto expected = normalize(referenceSolution(numsCopy1, testCases[i].target));
        auto actual = normalize(solution(numsCopy2, testCases[i].target));
        bool ok = (actual == expected);
        passed += ok;
        cout << "Test case " << i + 1 << ": " << (ok ? "PASS" : "FAIL") << " | your_output=";
        printCombos(actual);
        cout << " | expected=";
        printCombos(expected);
        cout << endl;
    }
    cout << "\n" << passed << "/" << testCases.size() << " passed" << endl;
}
