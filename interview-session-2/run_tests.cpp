#include <iostream>
#include <vector>
#include "solution.cpp"
#include "interviewer_only/reference_solution.hpp"
using namespace std;

int main() {
    struct TestCase { vector<int> nums; int k; };
    vector<TestCase> testCases = {
        {{3, 2, 1, 5, 6, 4}, 2},
        {{3, 2, 3, 1, 2, 4, 5, 5, 6}, 4},
        {{1}, 1},
        {{7, 7, 7, 7}, 2},

        // Add your own test cases here
        {{1, 2, 3, 4, 5}, 1},
        {{1, 2, 3, 4, 5}, 5},
        {{-30, 1, 2, 3, 4}, 1},
        {{-30, 0, 2, 3, 4}, 2},
        {{4, 3, 2, 0, -30}, 2},
    };

    int passed = 0;
    for (size_t i = 0; i < testCases.size(); i++) {
        auto numsCopy = testCases[i].nums;
        int expected = referenceSolution(testCases[i].nums, testCases[i].k);
        int actual = solution(numsCopy, testCases[i].k);
        bool ok = (actual == expected);
        passed += ok;
        cout << "Test case " << i + 1 << ": " << (ok ? "PASS" : "FAIL")
             << " | your_output=" << actual << " | expected=" << expected << endl;
    }
    cout << "\n" << passed << "/" << testCases.size() << " passed" << endl;
}
