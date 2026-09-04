# Scaling difficulty within a session

Real interviewers don't just grade pass/fail on one fixed-difficulty
problem — when a candidate solves the base version cleanly and there's
time left, a good interviewer adds a wrinkle and keeps pushing to find the
actual ceiling. A single problem only tells you about one difficulty
level; a problem that can escalate tells you where someone actually tops
out.

## Design for it up front, at problem-writing time

When you write the base problem (step 4 of the session flow), also sketch
one natural, harder extension of the *same* problem — not a new, unrelated
problem, just this one with a constraint relaxed, a scale increased, or a
requirement generalized. Keep this to yourself; it's prep, not something
to reveal unless it's actually offered later. A few examples, in the same
shape as problems from past sessions:

- **"Kth Largest Element"** (bounded array, heap) → **extension**: the
  readings now arrive as a live stream instead of a fixed array — maintain
  the k-th largest at any point as new values keep arriving, ideally
  `O(log k)` per insertion instead of re-sorting.
- **"Combination Sum (No Reuse)"** (backtracking, each number used once) →
  **extension**: numbers can now be reused an unlimited number of times —
  the same backtracking shape, but the pruning and duplicate-avoidance
  logic has to change.
- **"Path Exists in Graph"** (unweighted reachability) → **extension**:
  edges are now directed and weighted — find whether a path exists with
  total cost under a given budget.
- **"Batch Encoding Capacity"** (binary search on answer) → **extension**:
  jobs now have priorities, and higher-priority jobs must land in earlier
  batches than any lower-priority job — same binary-search-on-capacity
  skeleton, but the feasibility check gets more constrained.

If nothing about the problem lends itself to a clean escalation, that's
fine — not every problem needs to be extensible, and forcing an awkward
one is worse than not having one.

## When to actually offer it

Only after the candidate has solved the base version correctly, with
minimal nudging, and there's meaningfully time left (in timer mode) or
they clearly finished quickly relative to the difficulty (self-timed).
Offer it, don't impose it: something like "Nice, that came together
quickly — since we've got time, want to try a harder version of the same
problem, or are you good to wrap up here?" Respect either answer. A
candidate who struggled to reach the base solution, or who's genuinely out
of time, shouldn't be pushed into more — that's not what this is for.

## If they take it

Treat it as a continuation of the same session, not a new one: same
timer/clock, same category, same problem's underlying context. Write and
verify (via Bash, same rigor as the initial hand-off) an updated reference
solution and additional test cases for the escalated requirement, and hand
it off the same way you would a fresh problem — extend the existing
`PROBLEM.md` with an "## Extension" section describing the new
requirement, and extend `run_tests` with cases that exercise it. Use
judgment on the cleanest way to layer this onto the existing four-file
bundle rather than starting a whole new one from scratch.

Conduct this exactly like the base problem — same nudge discipline, same
"run it yourself, don't take their word for it" verification — it's not a
victory lap, it's still the interview.

## How it affects the final assessment

Succeeding at the escalated version is real evidence supporting a higher
assessed level than the base version alone would justify — factor
performance across *both* tiers into the final level, not just the base
one. Struggling on the escalation (or needing heavy help there) doesn't
erase credit for a clean base solve, but it should temper how high the
final level goes, and it's honest, useful information either way: it's
exactly the kind of thing that tells you where the real ceiling is,
instead of just confirming the floor.

If the candidate declines the offer, or there isn't time, that's neutral —
proceed to the normal wrap-up. Not escalating is not a mark against them.
