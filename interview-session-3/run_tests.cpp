#include <iostream>
#include <vector>
#include "solution.cpp"
#include "interviewer_only/reference_solution.hpp"
using namespace std;

int main() {
    struct TestCase { int n; vector<vector<int>> edges; int source; int destination; };
    vector<TestCase> testCases = {
        {3, {{0, 1}, {1, 2}, {2, 0}}, 0, 2},  // verifies undirected
        {6, {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}}, 0, 5},
        {1, {}, 0, 0},  // Self
        {2, {}, 0, 1},

        // Add your own test cases here
        {6, {{0, 1}, {0, 2}, {1, 2}, {3, 5}, {5, 4}, {4, 3}, {2, 4}}, 0, 5}, // Loop
        {6, {{0, 1}, {0, 2}, {1, 2}, {3, 5}, {5, 4}, {4, 3}, {2, 4}}, 5, 5}, // Self
        {15, {{0, 1}, {0, 2}, 
                {1, 3}, {1, 4}, {2, 5}, {2, 6}, 
                {3, 7}, {3, 8}, {4, 9}, {4, 10}, {5, 11}, {5, 12}, {6, 13}, {6, 14},
            }, 0, 14},
        {1000, {{0, 100}}, 0, 100},
    };

    int passed = 0;
    for (size_t i = 0; i < testCases.size(); i++) {
        auto edgesCopy = testCases[i].edges;
        bool expected = referenceSolution(testCases[i].n, testCases[i].edges, testCases[i].source, testCases[i].destination);
        bool actual = solution(testCases[i].n, edgesCopy, testCases[i].source, testCases[i].destination);
        bool ok = (actual == expected);
        passed += ok;
        cout << "Test case " << i + 1 << ": " << (ok ? "PASS" : "FAIL")
             << " | your_output=" << boolalpha << actual << " | expected=" << expected << endl;
    }
    cout << "\n" << passed << "/" << testCases.size() << " passed" << endl;
}
