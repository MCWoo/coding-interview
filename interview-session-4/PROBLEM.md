# Ramp-Up Threshold Detection

You're building diagnostics tooling for a hardware test rig. During a
heating-element ramp-up test, a sensor logs a temperature reading once per
minute, and because the element is monotonically heating up (never cooling
during the test window), the readings come out in **non-decreasing** order
(consecutive readings can repeat if the sensor logs faster than the element
actually changes temperature).

Given the array of `readings` and a `threshold` temperature, find the index
of the **first** reading that is `>= threshold` — that's the minute the rig
crossed into the target range. If the element never reaches `threshold`
during the test, return `readings.size()` (i.e., where it *would* land if
one more reading came in).

**Signature:** `int solution(vector<int>& readings, int threshold)`

**Constraints:**
- `1 <= readings.size() <= 10^5`
- `-10^4 <= readings[i] <= 10^4`
- `readings` is sorted in non-decreasing order (duplicates allowed)
- `-10^4 <= threshold <= 10^4`

**Examples:**
- `readings = [10, 12, 12, 15, 20], threshold = 13` → `3` (`readings[3] = 15` is the first value `>= 13`)
- `readings = [10, 12, 12, 15, 20], threshold = 12` → `1` (the first `12` is at index `1`, and `12 >= 12`)
- `readings = [10, 12, 12, 15, 20], threshold = 25` → `5` (never reached — return the array length)
- `readings = [10, 12, 12, 15, 20], threshold = 5` → `0` (already at/above threshold from the first reading)
