#include <iostream>
#include <vector>
#include "solution.cpp"
#include "interviewer_only/reference_solution.hpp"
using namespace std;

int main() {
    int testCases[] = {1, 2, 3, 4,
         45,
        };


    int passed = 0;
    int total = sizeof(testCases) / sizeof(testCases[0]);
    for (int i = 0; i < total; i++) {
        int expected = referenceSolution(testCases[i]);
        int actual = solution(testCases[i]);
        bool ok = (actual == expected);
        passed += ok;
        cout << "Test case " << i + 1 << ": " << (ok ? "PASS" : "FAIL")
             << " | input=" << testCases[i] << " | your_output=" << actual << " | expected=" << expected << endl;
    }
    cout << "\n" << passed << "/" << total << " passed" << endl;

    cout << "\n-- Extension: Blocked Beats --" << endl;
    struct ExtTestCase { int n; vector<int> blocked; };
    vector<ExtTestCase> extCases = {
        {4, {2}},
        {5, {3}},
        {6, {}},

        // Add your own test cases here
        // Blocked
        {1, {1}},
        {2, {2}},
        {45, {45}},
        {45, {1, 2}},
        {20, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}},

        // Allowable
        {2, {1}},
        {10, {1, 5}},
        {10, {1, 5, 9}},
        {10, {2, 5, 9}},
    };
    int extPassed = 0;
    for (size_t i = 0; i < extCases.size(); i++) {
        int expected = referenceSolutionExtended(extCases[i].n, extCases[i].blocked);
        int actual = solutionExtended(extCases[i].n, extCases[i].blocked);
        bool ok = (actual == expected);
        extPassed += ok;
        cout << "Ext test case " << i + 1 << ": " << (ok ? "PASS" : "FAIL")
             << " | your_output=" << actual << " | expected=" << expected << endl;
    }
    cout << "\n" << extPassed << "/" << extCases.size() << " extension tests passed" << endl;
}
