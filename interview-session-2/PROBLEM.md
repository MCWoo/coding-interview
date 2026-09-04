# Kth Largest Element in an Array

You're given an integer array `nums` and an integer `k`. Return the `k`th
largest element in the array — **not** the `k`th distinct element, so
duplicate values each count toward the ranking.

**Signature:** `int solution(vector<int>& nums, int k)`

**Constraints:**
- `1 <= k <= nums.length <= 10^4`
- `-10^4 <= nums[i] <= 10^4`

**Examples:**
- `nums = [3, 2, 1, 5, 6, 4], k = 2` → `5` (sorted descending: 6, 5, 4, 3, 2, 1 — the 2nd is 5)
- `nums = [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4` → `4` (sorted descending: 6, 5, 5, 4, 3, 3, 2, 2, 1 — the 4th is 4)
- `nums = [7, 7, 7, 7], k = 2` → `7` (duplicates each count individually)

It's guaranteed `k` is always valid for the given array (i.e. `1 <= k <= nums.length`).
