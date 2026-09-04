# Starter bundle — JavaScript / TypeScript (Node)

`PROBLEM.md`: the problem statement you wrote, saved verbatim (plain
Markdown — description, constraints, examples, no extra template needed).

`solution.js`:
```javascript
// nums: number[] -- 2 <= nums.length <= 10^4, -10^9 <= nums[i] <= 10^9
// target: number -- -10^9 <= target <= 10^9
// Returns: number[] -- the two indices i, j (i !== j) such that nums[i] + nums[j] === target
function solution(nums, target) {
  // TODO: implement your solution here
}

module.exports = { solution };
```
(The parameter/bounds comment is illustrative — replace it with the actual
signature and constraints for whatever problem you wrote.)

`interviewer_only/reference_solution.js`:
```javascript
function solution(nums, target) {
  const seen = new Map();
  for (let i = 0; i < nums.length; i++) {
    const complement = target - nums[i];
    if (seen.has(complement)) return [seen.get(complement), i];
    seen.set(nums[i], i);
  }
  return [];
}

module.exports = { solution };
```

`run_tests.js`:
```javascript
const { solution: candidateSolution } = require("./solution");
const { solution: referenceSolution } = require("./interviewer_only/reference_solution");

const testCases = [
  { nums: [2, 7, 11, 15], target: 9 },
  { nums: [3, 2, 4], target: 6 },
  // Add your own test cases here
];

let passed = 0;
testCases.forEach((tc, i) => {
  const expected = referenceSolution(tc.nums, tc.target);
  const actual = candidateSolution(tc.nums, tc.target);
  // JSON.stringify comparison works for simple value equality; switch to a
  // sorted/set comparison if the problem allows multiple valid answers.
  const ok = JSON.stringify(actual) === JSON.stringify(expected);
  passed += ok ? 1 : 0;
  console.log(`Test case ${i + 1}: ${ok ? "PASS" : "FAIL"} | input=${JSON.stringify(tc)} | `
    + `your_output=${JSON.stringify(actual)} | expected=${JSON.stringify(expected)}`);
});
console.log(`\n${passed}/${testCases.length} passed`);
```

Run with `node run_tests.js`. For TypeScript, use the same shape with
`.ts` files and `ts-node run_tests.ts`, or compile first — either is fine,
just match whatever the candidate already has set up.
