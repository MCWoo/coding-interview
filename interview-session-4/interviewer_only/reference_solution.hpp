#pragma once
#include <vector>
using namespace std;

inline int referenceSolution(vector<int>& readings, int threshold) {
    int lo = 0, hi = (int)readings.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (readings[mid] < threshold) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}
