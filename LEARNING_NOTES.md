# Learning Notes

Concepts and tools explicitly asked about while working on this project.

## Claude Code skills: is `--flag` invocation syntax "officially supported"?

Asked while designing the `--new-category` / `--status` / `--list-categories`
/ `--notes` shortcuts on `/coding-interview`.

Slash-command invocations in Claude Code pass everything after the command
name to the model as plain text — there's no built-in argument parser that
recognizes `--flag` syntax as special. So `--status` isn't "officially
supported" flag syntax in the way a CLI framework's `argparse` would treat
it; it's just text the skill's instructions are written to recognize and
act on, the same way they'd recognize any other natural-language request
("show me my status"). This means flag-style shortcuts are a documentation
convention inside `SKILL.md` (pattern-match on the args text), not a
code-level parsing feature — which is also why they can coexist with
natural language ("how am I doing?") triggering the same behavior.

## JavaScript: does `Array.prototype.reduce` add by default?

Asked while writing a candidate solution during a mock interview session.

No — `reduce` has no default operation. It takes a callback
`(accumulator, currentValue) => ...` plus an optional initial value, and
just applies whatever the callback does across the array, threading the
return value forward as the accumulator each step. "Summing" is the most
common use, but that's a property of writing `(a, b) => a + b` as the
callback, not something `reduce` does on its own — pass any lambda (max,
string concatenation, building up an object) and it does that instead. If
no initial value is given, the first array element is used as the starting
accumulator and reduction starts from index 1.

## C++: what does `auto` mean in a lambda's parameter list?

Asked while discussing a `binarySearch(hi, auto predicate)` helper lambda
written outside a formal interview session (general binary-search
discussion, LeetCode #74).

It makes the lambda a **generic lambda** (C++14+): the closure's
`operator()` becomes a template, with the parameter's type deduced per
call site — the same deduction rules as an ordinary template parameter
(pass-by-value, decays arrays/top-level cv-qualifiers; write `const
auto&` to bind by reference instead). Passing two differently-typed
lambdas to the same `auto`-parameter function generates two separate
compile-time instantiations of `operator()`, with no virtual dispatch or
`std::function`-style type erasure involved — this is what makes the
pattern zero-cost.

This is distinct from bare `auto` as a parameter type in an *ordinary*
(non-lambda) function, e.g. `void foo(auto x)` — that's a separate,
C++20-only feature ("abbreviated function templates"); the lambda version
works back to C++14. It's also a different job for the same keyword than
`auto` used for variable-type deduction (e.g. `auto binarySearch = [...]`
deduces the *variable's* type from its initializer — unrelated to
parameter-type templating, despite reusing the same keyword).

## Algorithms: what is "sweep line"?

Asked after a mock interview session (`greedy_intervals`, "Deployment
Freeze Windows") where the candidate independently arrived at the pattern
(tracking start/end timepoints on a timeline rather than the intervals
themselves) without knowing its name.

Sweep line is the general pattern of reducing "reason about every point
on a number line/plane" down to "reason only about the finite set of
points where something could change." Concretely: turn every
object/interval into one or more **events** at specific positions (e.g. a
"start" and an "end" event per interval), **sort the events by
position**, then **walk through them in order**, updating some running
state at each one and emitting output whenever that state crosses a
condition of interest. Complexity is almost always O(n log n) (the sort)
+ O(n) (the single linear walk).

Common applications: interval merging, "max overlapping meetings" style
problems, the skyline problem, calendar conflict detection, and (in 2D)
computational geometry — segment intersection, closest pair of points,
rectangle union area, sweeping a line across the plane while maintaining
an active set of shapes the line currently crosses.

The classic failure mode, and the one that actually surfaced a real bug
in the candidate's solution this session: when multiple events land at
the *exact same position*, their relative processing order matters (e.g.
whether one interval's "end" event or a different interval's "start"
event, at the same coordinate, is treated as happening first), and
sorting by position alone doesn't specify it. The fix is always to give
the comparator an explicit secondary key (an event-type rank) so ties
resolve the way the problem's semantics need, rather than leaving it to
however the sort implementation happens to break ties.

## How are system design interviews actually assessed?

Asked after a live system design session (`session-08`, a self-service
cloud platform problem) where the candidate asked whether the interview
had even been addressed properly, since there's no test suite the way
there is for a DS&A problem.

System design loops don't have a ground-truth answer to check against, so
assessment rests on *how* a candidate reasons, scored across roughly six
recurring axes: requirements gathering, high-level architecture, deep-dive
technical depth, trade-off reasoning (consistently reported as the single
most differentiating axis — a choice only earns credit once the tension
behind it is actually named out loud), scalability/operational awareness
(expect numbers and a specific bottleneck at senior level, not just "we'd
add a cache"), and communication (thinking out loud, not reconstructed
after the fact when asked).

The bar on each axis rises with seniority rather than new axes appearing —
a senior+ candidate is expected to drive requirements-gathering themselves
and surface a requirement the prompt never stated, where a mid-level
candidate answering clarifying questions when prompted is already fine. A
common real failure mode is spending too long on requirements/high-level
sketching and never reaching the deep dive, which is where the strongest
signal actually lives.

Full writeup, including how this maps onto this project's five-level skill
ladder, lives in
`.claude/skills/coding-interview/references/system_design_assessment.md`.
