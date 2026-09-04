#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

bool isValidBatchTime(const vector<int>& jobTimes, int maxBatches, int batchTime) {
    int currBatch = 0;
    int numBatches = 1;
    for (int i = 0; i < jobTimes.size(); ++i) {
        currBatch += jobTimes[i];
        if (currBatch > batchTime) {
            currBatch = jobTimes[i];
            numBatches++;

            if (numBatches > maxBatches) return false;
        }
    }

    return true;
}

// jobTimes: vector<int> -- 1 <= jobTimes.size() <= 10^4, 1 <= jobTimes[i] <= 10^4
// maxBatches: int -- 1 <= maxBatches <= jobTimes.size()
// Returns: int -- minimum per-batch capacity so all jobs fit within maxBatches batches (in order, no splitting a job)
int solution(const vector<int>& jobTimes, int maxBatches) {
    // Get the sum and max time
    int sum = std::reduce(jobTimes.begin(), jobTimes.end(), 0);
    int longestJob = *std::max_element(jobTimes.begin(), jobTimes.end());

    int lo = longestJob;
    int hi = sum;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (isValidBatchTime(jobTimes, maxBatches, mid)) {
            // Recurse left
            hi = mid;
        } else {
            // Recurse right
            lo = mid + 1;
        }
    }

    return lo;
}
