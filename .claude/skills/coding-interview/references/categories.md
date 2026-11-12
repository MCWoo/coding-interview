# Category taxonomy and difficulty ladder

## Categories

These are the built-in categories every profile starts with — general DS&A
plus system design/OOP/senior scenarios. They cover the common case, but
they're not the whole space: a candidate can add their own categories for
whatever they're actually specializing in (game physics, network
engineering, graphics, distributed systems, anything pulled from a job
description) via `manage_state.py add-category`. See
`references/custom_categories.md` for that workflow. Once
added, a custom category is tracked exactly like these built-in ones — same
five-level ladder, same weighted selection, nothing here treats them
differently.

**Data structures & algorithms**
- `arrays_hashing` — arrays, hash maps/sets, prefix sums, string manipulation
- `two_pointers_sliding_window` — two pointers, sliding window, fast/slow pointers
- `stacks_queues` — stacks, queues, monotonic stack/queue problems
- `linked_lists` — singly/doubly linked lists, cycle detection, reversal
- `trees_graphs_traversal` — binary trees/BSTs, tree DFS/BFS, tries
- `graph_algorithms` — general graphs, union-find, topological sort, shortest paths (Dijkstra/BFS-weighted)
- `binary_search` — binary search on arrays and on answer spaces
- `recursion_backtracking` — combinatorial search, permutations/subsets, backtracking with pruning
- `dynamic_programming` — 1D/2D DP, memoization vs tabulation, knapsack-family
- `greedy_intervals` — greedy proofs, interval scheduling/merging
- `heaps_priority_queues` — heaps, top-k, merge-k problems

**Beyond LeetCode — senior/principal territory**
- `system_design` — design a system at scale (e.g. "design a URL shortener", "design a rate limiter"): requirements gathering, high-level architecture, data model, scaling bottlenecks, tradeoffs. See `references/system_design_assessment.md` for how to actually assess a session in this category — the generic level ladder below still applies, but there's no test suite to anchor on, so that file breaks down what "proficient" vs. "strong" trade-off reasoning or scalability reasoning actually looks like.
- `object_oriented_design` — design classes/interfaces for a bounded problem (e.g. "design a parking garage", "design an elevator system"): OOP modeling, extensibility, edge cases
- `senior_scenarios` — grab-bag for other senior/principal-shaped problems: debugging a gnarly incident from a code snippet + logs, reviewing a PR for correctness/scale issues, API design (REST/gRPC contract for a described feature), concurrency bugs (race conditions, deadlocks), tradeoff discussions ("how would you migrate X with zero downtime")

## Level ladder

Five levels, used consistently for every category: `unknown`, `weak`,
`developing`, `proficient`, `strong`. A new candidate profile starts every
category at `unknown` — treat `unknown` exactly like `weak` for problem
selection (easy difficulty), the distinction just exists so you can tell
"never tested" apart from "tested and struggled" when explaining progress to
the candidate.

Rough behavioral anchors for setting a level after a session (see SKILL.md's
"Assessing performance" section for the full rubric) — these are guidelines
for judgment, not a checklist to grade mechanically:

| Level | What it looks like |
|---|---|
| `unknown` | Not yet attempted in this category |
| `weak` | Needed significant hints to find an approach, or didn't reach a working solution, or the working solution was well below the expected complexity |
| `developing` | Reached a correct approach but needed a nudge on a key insight, or the implementation had bugs that took a while to find, or timing/complexity analysis was shaky |
| `proficient` | Solved it independently in reasonable time with a sound approach and correct-ish complexity, minor rough edges |
| `strong` | Solved it cleanly and fast, identified the optimal approach with little/no guidance, articulated tradeoffs and complexity clearly, handled follow-ups well |

**Never move more than one level per session, in either direction, with one
named exception: a first-ever session in a category can jump `unknown`
straight to `developing`, but no further than that even for an outstanding
showing.** `unknown` isn't really a skill level — it just means "never
assessed" — so treating a strong-but-first-time performance the same as an
established `weak` rating being asked to prove itself again is the wrong
comparison. Landing on `developing` after one clean, independent solve is a
fair read of "no evidence of a problem, plus a correct approach"; jumping
past it to `proficient` or `strong` on a single data point still isn't,
since those levels are meant to reflect handling real friction or difficulty
well, which one easy-to-medium first problem doesn't establish either way.

Every other transition keeps the strict one-step cap, no exceptions: an
excellent session in a category already at `weak` moves it to `developing`,
not straight to `proficient`; a single bad session in a category previously
rated `strong` drops it to `proficient`, not all the way back to `unknown`.
If a performance feels like it deserves a bigger jump than the cap allows,
that's what the next session is for — a second consecutive strong showing
moves it another step, same as the first one did. This keeps the tracked
level anchored to a real trend across sessions rather than a single data
point, and it's simpler to apply consistently than judging exceptions case
by case. Dropping a level after a rough session in a previously
strong/proficient category is equally normal — skills rust, and the ramp
should follow current performance, not just historical best — but that drop
is also capped at one step per session.

## Difficulty selection

`manage_state.py suggest` implements the actual weighted-random selection
(weaker + longer-untouched categories are picked more often, and difficulty
is derived from the chosen category's current level). You don't need to
reimplement this logic — just run the script and use its output. The mapping
it uses:

- `unknown` / `weak` → easy
- `developing` → medium
- `proficient` → medium, occasionally (~30%) hard
- `strong` → hard, occasionally (~40%) `open_ended` (a stretch/system-design-shaped problem regardless of category)

If the candidate asks to focus on a specific category or explicitly wants a
harder/easier problem than the ladder would suggest, honor that — the
algorithm is a sensible default starting point, not a constraint on the
candidate's agency. Pass `--category NAME` to `suggest` to force a category
while still getting a sensible difficulty for their current level in it.

**Staleness prevention.** The weighting above is deliberately skewed toward
weak/unknown categories, which means a category that reaches `proficient`
or `strong` can become almost impossible to ever get picked again once a
candidate has accumulated several still-unknown categories — the weighting
alone would just let it fall out of rotation permanently. To prevent that,
roughly 1 in 4 calls to `suggest` instead forces a revisit of whichever
`proficient`/`strong` category has gone longest without being practiced
(when one exists), overriding the normal weighted pick for that call. This
is deterministic-by-recency rather than random within that branch — the
point is a guaranteed periodic check-in on already-strong areas, not
another dice roll. `suggest`'s JSON output includes a `staleness_revisit`
boolean so you can tell which mode produced a given pick, though you don't
need to explain that mechanism to the candidate — just treat the resulting
category/difficulty the same way regardless of which path picked it.
