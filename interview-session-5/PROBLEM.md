# Batch Encoding Capacity

You're building a batch video-encoding pipeline. Jobs must be encoded
strictly in the order they're queued (no reordering), and they're grouped
into consecutive batches: each batch greedily takes as many jobs as it can
without its total encoding time exceeding the batch's time capacity (a
single job is never split across two batches).

Given the encoding time required for each job in `jobTimes` and a fixed
number of batches `maxBatches` available before a deadline, find the
**minimum per-batch time capacity** that still allows all jobs to be
processed within `maxBatches` batches or fewer.

**Signature:** `int solution(vector<int>& jobTimes, int maxBatches)`

**Constraints:**
- `1 <= jobTimes.size() <= 10^4`
- `1 <= jobTimes[i] <= 10^4`
- `1 <= maxBatches <= jobTimes.size()`

**Examples:**
- `jobTimes = [3, 2, 2, 4, 1, 4], maxBatches = 3` → `6`
  (capacity 6 splits into `[3,2]`, `[2,4]`, `[1,4]` — 3 batches; capacity 5 would need 4 batches, so 6 is the minimum that fits in 3)
- `jobTimes = [3, 2, 2, 4, 1, 4], maxBatches = 6` → `4`
  (one job per batch is always allowed when `maxBatches` equals the job count, so capacity only needs to cover the single largest job)
- `jobTimes = [3, 2, 2, 4, 1, 4], maxBatches = 1` → `16`
  (everything has to fit in one batch, so capacity must cover the full sum)
