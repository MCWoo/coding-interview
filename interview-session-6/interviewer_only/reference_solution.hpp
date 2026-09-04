#pragma once
#include <vector>

inline int referenceSolution(int n) {
    if (n <= 2) return n;
    int prev2 = 1, prev1 = 2;
    for (int i = 3; i <= n; i++) {
        int cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

inline int referenceSolutionExtended(int n, std::vector<int>& blockedBeats) {
    std::vector<bool> blocked(n + 1, false);
    for (int b : blockedBeats) if (b >= 0 && b <= n) blocked[b] = true;
    std::vector<long long> dp(n + 1, 0);
    dp[0] = blocked[0] ? 0 : 1;
    for (int i = 1; i <= n; i++) {
        if (blocked[i]) { dp[i] = 0; continue; }
        long long fromOne = dp[i - 1];
        long long fromTwo = (i >= 2) ? dp[i - 2] : 0;
        dp[i] = fromOne + fromTwo;
    }
    return (int)dp[n];
}
