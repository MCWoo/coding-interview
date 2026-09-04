#include <iostream>
#include <vector>
#include "solution.cpp"
#include "interviewer_only/reference_solution.hpp"
using namespace std;

int main() {
    struct TestCase { vector<int> jobTimes; int maxBatches; };
    vector<TestCase> testCases = {
        {{3, 2, 2, 4, 1, 4}, 3},
        {{3, 2, 2, 4, 1, 4}, 6},
        {{3, 2, 2, 4, 1, 4}, 1},
        {{5}, 1},

        // Add your own test cases here
        {{3, 2, 2, 4, 1, 4}, 8},
        {{3, 20, 2, 4, 1, 4}, 4},
        {{3, 3, 3, 3, 3, 3, 3}, 4},
    };

    int passed = 0;
    for (size_t i = 0; i < testCases.size(); i++) {
        auto copy1 = testCases[i].jobTimes;
        auto copy2 = testCases[i].jobTimes;
        int expected = referenceSolution(copy1, testCases[i].maxBatches);
        int actual = solution(copy2, testCases[i].maxBatches);
        bool ok = (actual == expected);
        passed += ok;
        cout << "Test case " << i + 1 << ": " << (ok ? "PASS" : "FAIL")
             << " | your_output=" << actual << " | expected=" << expected << endl;
    }
    cout << "\n" << passed << "/" << testCases.size() << " passed" << endl;
}
