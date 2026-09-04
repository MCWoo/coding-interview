#include <vector>
using namespace std;

/*
[1, 2] -> 1
[0, 1) -> mid: 0 -> 1->2 return 1;

[1, 2] -> 2
[0, 1) -> mid: 0 -> recurse right
[1, 1) -> mid: 1 -> 

[1] -> 1 return 0
[0, 0) -> 0, return 0
[1] -> 0

[1, 2, 3] -> 0
[0, 2) -> mid: 1 = 2 -> recurse left
[0, 1) -> mid: 0 = 1 -> recurse left
[0, 0) -> mid: 0

[1, 2, 3] -> 3
[0, 2) -> mid: 1 = 2 -> return 2
*/
int recurse(const vector<int>& readings, int min, int max, int threshold) {
    if (min == max) return max;

    int mid = min + (max - min) / 2;

    if (readings[mid] < threshold) {
        // Check if this is the solution
        if (readings[mid+1] >= threshold) return mid+1;

        // recurse right
        return recurse(readings, mid + 1, max, threshold);
    } else {
        // recurse left
        return recurse(readings, min, mid, threshold);
    }
}

// readings: vector<int> -- 1 <= readings.size() <= 10^5, -10^4 <= readings[i] <= 10^4, sorted non-decreasing
// threshold: int -- -10^4 <= threshold <= 10^4
// Returns: int -- index of first reading >= threshold, or readings.size() if none reach it
int solution(const vector<int>& readings, int threshold) {
    if (readings.back() < threshold) return readings.size();

    return recurse(readings, 0, readings.size()-1, threshold);
}

