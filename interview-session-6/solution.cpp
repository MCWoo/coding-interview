#include <vector>

// n: int -- target beat count, 1 <= n <= 45
// Returns: int -- number of distinct move sequences (steps of 1 or 2) that sum to exactly n
int solution(int n) {
    // Base cases
    if (n == 1) return 1;
    if (n == 2) return 2;  // Either 1 + 1 or 2

    std::vector<int> solutions(n);

    solutions[0] = 1;
    solutions[1] = 2;

    for (int i = 2; i < n; ++i) {
        solutions[i] = solutions[i-1] + solutions[i-2];
    }

    return solutions[n-1];
}

// n: int -- target beat count, 1 <= n <= 45
// blockedBeats: vector<int> -- distinct beat values in [0, n] the combo counter must never land on
// Returns: int -- number of distinct move sequences that reach exactly n without landing on a blocked beat
int solutionExtended(int n, std::vector<int>& blockedBeats) {
    const int SENTINEL = -1;
    std::vector<int> solutions(n, SENTINEL);

    for (int blocked : blockedBeats) {
        if (blocked == n) return 0;  // Early out
        solutions[blocked-1] = 0;
    }

    // This time, don't overwrite any blocked values for base case
    if (solutions[0] == SENTINEL) solutions[0] = 1;
    if (n == 1) return solutions[0];

    // And our base case has to take into account if 1 were blocked
    if (solutions[1] == SENTINEL) solutions[1] = solutions[0] + 1;

    for (int i = 2; i < n; ++i) {
        if (solutions[i] != SENTINEL) continue;
        solutions[i] = solutions[i-1] + solutions[i-2];
    }

    return solutions[n-1];
}
