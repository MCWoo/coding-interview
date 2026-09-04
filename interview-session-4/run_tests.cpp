#include <iostream>
#include <vector>
#include "solution.cpp"
#include "interviewer_only/reference_solution.hpp"
using namespace std;

int main() {
    struct TestCase { vector<int> readings; int threshold; };
    vector<TestCase> testCases = {
        {{10, 12, 12, 15, 20}, 13},
        {{10, 12, 12, 15, 20}, 12},
        {{10, 12, 12, 15, 20}, 25},
        {{10, 12, 12, 15, 20}, 5},
        {{10}, 10},

        // Add your own test cases here
        {{10, 12, 12, 12, 12, 15, 20}, 11},
        {{10, 12, 12, 12, 12, 15, 20}, 20},
        {{10, 12, 12, 12, 12, 15, 20}, 19},
        {{10, 12, 12, 12, 12, 15, 20}, 10},
        {{10, 10, 10, 10, 10, 10, 10}, 10},
    };

    int passed = 0;
    for (size_t i = 0; i < testCases.size(); i++) {
        auto readingsCopy = testCases[i].readings;
        int expected = referenceSolution(testCases[i].readings, testCases[i].threshold);
        int actual = solution(readingsCopy, testCases[i].threshold);
        bool ok = (actual == expected);
        passed += ok;
        cout << "Test case " << i + 1 << ": " << (ok ? "PASS" : "FAIL")
             << " | your_output=" << actual << " | expected=" << expected << endl;
    }
    cout << "\n" << passed << "/" << testCases.size() << " passed" << endl;
}
