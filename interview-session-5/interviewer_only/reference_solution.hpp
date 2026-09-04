#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

inline int referenceBatchesNeeded(vector<int>& jobTimes, int capacity) {
    int batches = 1;
    int current = 0;
    for (int t : jobTimes) {
        if (current + t > capacity) {
            batches++;
            current = t;
        } else {
            current += t;
        }
    }
    return batches;
}

inline int referenceSolution(vector<int>& jobTimes, int maxBatches) {
    int lo = *max_element(jobTimes.begin(), jobTimes.end());
    int hi = accumulate(jobTimes.begin(), jobTimes.end(), 0);
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (referenceBatchesNeeded(jobTimes, mid) > maxBatches) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}
