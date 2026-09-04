#include <queue>
#include <vector>
using namespace std;

// nums: vector<int> -- 1 <= nums.size() <= 10^4, -10^4 <= nums[i] <= 10^4
// k: int -- 1 <= k <= nums.size() (always valid)
// Returns: int -- the kth largest element (duplicates count individually)
int solution(const vector<int>& nums, int k) {
    std::priority_queue<int, vector<int>, greater<int>> minHeap;

    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) minHeap.pop();
    }

    return minHeap.top();
}
