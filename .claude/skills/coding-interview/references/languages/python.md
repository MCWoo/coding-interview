# Starter bundle — Python

`PROBLEM.md`: the problem statement you wrote, saved verbatim (plain Markdown,
no template needed — just the description, constraints, and examples you
already composed).

`solution.py`:
```python
def solution(nums, target):
    # nums: List[int] -- 2 <= len(nums) <= 10^4, -10^9 <= nums[i] <= 10^9
    # target: int -- -10^9 <= target <= 10^9
    # Returns: List[int] -- the two indices i, j (i != j) such that nums[i] + nums[j] == target
    # TODO: implement your solution here
    pass
```
(The parameter/bounds comment is illustrative — replace it with the actual
signature and constraints for whatever problem you wrote. The point is
sparing the candidate a lookup, not padding the file.)

`interviewer_only/reference_solution.py`:
```python
def solution(nums, target):
    seen = {}
    for i, n in enumerate(nums):
        if target - n in seen:
            return [seen[target - n], i]
        seen[n] = i
    return []
```

`run_tests.py`:
```python
import os
import sys

sys.path.insert(0, os.path.dirname(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "interviewer_only"))

from solution import solution as candidate_solution
from reference_solution import solution as reference_solution

test_cases = [
    {"nums": [2, 7, 11, 15], "target": 9},
    {"nums": [3, 2, 4], "target": 6},
    # Add your own test cases here, e.g. edge cases:
    # {"nums": [], "target": 0},
]

passed = 0
for i, case in enumerate(test_cases, 1):
    expected = reference_solution(**case)
    actual = candidate_solution(**case)
    ok = actual == expected  # adjust the comparison if order/tolerance doesn't matter for this problem
    passed += ok
    print(f"Test case {i}: {'PASS' if ok else 'FAIL'} | input={case} | "
          f"your_output={actual} | expected={expected}")

print(f"\n{passed}/{len(test_cases)} passed")
```

Run with `python3 run_tests.py`. Verified end-to-end (both a wrong and a
correct `solution.py`) when this bundle shape was first built — this is the
reference pattern the other languages' templates were adapted from.
