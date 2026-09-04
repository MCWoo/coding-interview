# Scenario skinning — making problems read like real interviews

## Why this matters

A real interviewer essentially never opens with "given an array `nums` and
an integer `target`, return...". They open with something closer to "we're
building a fraud-detection feature and need to flag pairs of transactions
that net out to exactly a reported refund amount" — and the underlying
algorithm you need turns out to be the exact same array/hash-map pattern
either way. The scenario is what makes it feel like an interview instead of
a flashcard drill, and it's also genuinely realistic: interviewers reuse
well-known patterns constantly, they just dress them in whatever their
company's actual domain is.

Skinning changes the *story* and the *parameter names*, not the substance.
The constraints, the difficulty, the expected complexity, the reference
solution, the test cases — none of that changes. You're translating `nums`
into `transactionAmounts` and writing two sentences of setup, not inventing
a harder problem.

## Keep the skin honest

The flavor text has to survive contact with the actual constraints, or it
reads as sloppy rather than realistic:

- If a value can be negative, the domain framing needs to make sense of
  that (e.g. "temperature readings" or "account balance deltas" — not
  "shopping cart prices" unless refunds/discounts are explicitly part of
  the story).
- If a value can be huge (`10^9`, say), don't frame it as something that's
  obviously small in real life (a person's age, a single day's step count)
  without explaining why — pick a quantity where that range is plausible
  (a timestamp, an account balance in cents, a distance in millimeters).
- The formal spec still needs to be precise. The scenario buys you a
  one-to-two-sentence setup paragraph before the spec, not permission to
  make the actual input/output contract vaguer. Keep the explicit signature,
  types, and constraints block exactly as rigorous as it would be without
  any story at all.

## Which categories need this

Apply it to the DSA categories — `arrays_hashing`, `two_pointers_sliding_window`,
`stacks_queues`, `linked_lists`, `trees_graphs_traversal`, `graph_algorithms`,
`binary_search`, `recursion_backtracking`, `dynamic_programming`,
`greedy_intervals`, `heaps_priority_queues`. These are the ones that, left
unskinned, read as bare algorithmic exercises.

`system_design`, `object_oriented_design`, and `senior_scenarios` don't need
separate treatment here — a system-design brief or a "design a parking
garage" prompt or a "review this PR" scenario is already inherently
real-world by construction. Nothing to add for those.

## A rotating pool of domains

Don't reach for the same one or two domains every time (fintech is an easy
default to overuse) — vary it the way a real slate of interviews across
different companies would. Some options to rotate through:

fintech/payments · e-commerce & order fulfillment · social networks/friend
graphs · ride-sharing & mapping/logistics · DevOps/observability/monitoring
dashboards · gaming (leaderboards, matchmaking, inventory) · IoT/sensor
networks · streaming media & recommendations · calendar/scheduling systems ·
search/autocomplete · access control & permissions systems · course/learning
management · customer support ticketing · version control & build/CI
systems · URL shorteners & click analytics · email/spam filtering ·
warehouse/robotics logistics · chat & messaging systems · ad auction/bidding
systems · restaurant/reservation booking

Pick whichever domain makes the *current* problem's shape feel natural
rather than forcing a favorite domain onto every problem.

## Worked examples

These are drawn from the shape of problems already used in past sessions,
showing the same underlying problem bare vs. skinned.

### Array/hash-map pattern (e.g. `arrays_hashing`)

**Bare:** "Given an array of integers `nums` and an integer `target`,
return the indices of the two numbers that add up to `target`."

**Skinned (fintech):** "You're building a reconciliation tool for a
payments platform. Given a list of transaction amounts (in cents) posted
today and a reported refund total, find the two transactions whose amounts
sum exactly to the refund total, so support can flag them for review."
Signature becomes `vector<int> solution(vector<int>& transactionAmounts, int refundTotal)` —
same two-int-hashmap algorithm underneath, same constraints, same
complexity expectations.

### Heap pattern (e.g. `heaps_priority_queues`)

**Bare:** "Given an array `nums` and an integer `k`, return the k-th
largest element."

**Skinned (observability):** "You're on-call for a service and pulling
response-time samples from the last monitoring window. Given a list of
latency readings (in milliseconds) and an integer `k`, find the k-th
highest latency — you want to know how bad the tail actually gets without
sorting the entire window every time." Same bounded-min-heap approach,
same complexity, just `latenciesMs` instead of `nums`.

### Graph reachability pattern (e.g. `graph_algorithms`)

**Bare:** "Given `n` nodes and a list of `edges`, determine if there's a
path between `source` and `destination`."

**Skinned (infra/dependency graph):** "You're building a tool that checks
whether one microservice can transitively reach another through however
many hops of internal calls, so a platform team can safely decommission
services. Given `n` services (numbered `0` to `n-1`) and a list of
direct-call edges, determine whether `source` can reach `destination`
through some chain of calls." Same BFS/adjacency-list approach — the edges
just represent "service A calls service B" instead of an abstract
undirected connection. (Note this example happens to want a *directed*
graph, which is itself a nice realistic wrinkle a bare "graph" problem
wouldn't have prompted — let the scenario inform small, honest variations
like directed vs. undirected when it naturally would.)

### Dynamic programming pattern (e.g. `dynamic_programming`)

**Bare:** "Given an array of integers, find the maximum sum of a
non-adjacent subsequence."

**Skinned (scheduling):** "You're building a scheduler for a warehouse
robot that can service pickup requests along a single conveyor line, each
worth a point value, but the robot can't service two adjacent stations back
to back (it needs to travel past one in between). Given the point value at
each station in order, find the maximum total value the robot can collect."
Same classic house-robber-shaped recurrence underneath.

The pattern in all four: identify the underlying pattern first (it's fine,
even expected, to still be thinking in terms of "this is a two-sum/heap/BFS
type problem" while designing it) — then find a domain and a one-sentence
premise where that exact shape of data and constraint would plausibly show
up, and write the spec through that lens.
