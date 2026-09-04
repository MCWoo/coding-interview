# Starter bundle — Go

Go packages can't have two functions with the same name either, so give the
reference implementation its own package.

`PROBLEM.md`: the problem statement you wrote, saved verbatim (description,
constraints, examples) — plain Markdown, not part of the Go build.

`solution.go` (package `main`):
```go
package main

// nums: []int -- 2 <= len(nums) <= 10^4, -10^9 <= nums[i] <= 10^9
// target: int -- -10^9 <= target <= 10^9
// Returns: []int -- the two indices i, j (i != j) such that nums[i]+nums[j] == target
func solution(nums []int, target int) []int {
	// TODO: implement your solution here
	return nil
}
```
(The parameter/bounds comment is illustrative — replace it with the actual
signature and constraints for whatever problem you wrote.)

`interviewer_only/reference_solution.go` (package `intervieweronly`):
```go
package intervieweronly

func Solution(nums []int, target int) []int {
	seen := map[int]int{}
	for i, n := range nums {
		if j, ok := seen[target-n]; ok {
			return []int{j, i}
		}
		seen[n] = i
	}
	return []int{}
}
```

`run_tests.go` — since `run_tests.go` needs both `main.solution` and the
`intervieweronly` package, keep it as a separate `_test.go`-style entry
point or a small script; the simplest approach is a `runtests/main.go` that
imports the module's `intervieweronly` package and shells out to compare,
OR (simpler for a quick interview exercise) just keep the reference
function in a build-tag-excluded file and copy its logic into the tester at
verification time. For interviews, it's fine to keep Go's version slightly
simpler: put the reference solution inline in `run_tests.go` itself but
still physically separate from `solution.go`, and just ask the candidate
not to scroll down past the `// --- reference below, don't peek ---` marker.

This one hasn't been run end-to-end the way the Python bundle was (see
`python.md`) — if you generate a Go bundle, sanity-check the module wiring
with `go run` yourself before handing it to the candidate, since Go's
package/import rules make it easy to end up with something that doesn't
build.
