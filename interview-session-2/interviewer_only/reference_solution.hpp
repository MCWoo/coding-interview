#pragma once
#include <vector>
#include <queue>
using namespace std;

inline int referenceSolution(vector<int> nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int n : nums) {
        minHeap.push(n);
        if ((int)minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}
