# Starter code bundle — shared rules

Purpose: give the candidate something they can paste straight into their own
IDE/terminal, with a way to actually verify their solution against correct
expected outputs — not just see raw output and have to eyeball it. That
needs a real reference solution to compute "expected" from, which means
*you* (the interviewer) have to write and trust your own correct solution.

This file has the rules that apply no matter what language the candidate
picked. Once you know the language, go straight to its file in
`references/languages/` — you only need that one:

| Language | File |
|---|---|
| Python | `references/languages/python.md` |
| JavaScript / TypeScript | `references/languages/javascript.md` |
| Java | `references/languages/java.md` |
| Go | `references/languages/go.md` |
| C++ | `references/languages/cpp.md` |

For a language not listed there, follow the same three-file shape (below)
using that language's normal module/import mechanism to separate the
reference implementation from the candidate's file.

## The four-file bundle

For every DSA problem, write four files, structured so the trust boundary
is obvious from the file layout itself:

```
PROBLEM.md                     <- the problem statement, saved for reference
solution.py                    <- candidate edits this
run_tests.py                   <- candidate runs this
interviewer_only/
    reference_solution.py      <- do not open. correct answer, used by run_tests.py
```

(Substitute the right extension/module layout per language — see the file
for the candidate's chosen language.)

That's the whole bundle — don't also generate editor/IDE config (a
`tasks.json`, a `launch.json`, a Makefile, etc.) unless the candidate
specifically asks for help with their build setup. Compiling and running is
their own tooling to manage, the same way it would be in a real interview or
on the job; the plain compile/run command given in each language's file
under `references/languages/` is all that's needed. If a candidate does hit
real friction with their editor's build tooling, it's fine to help debug it
in the moment — just don't do it preemptively for every session.

- **`PROBLEM.md`**: the exact problem statement you just presented in the
  chat — description, constraints, worked examples, edge cases — saved to
  disk as-is. The candidate is about to spend 20-60 minutes with their
  attention in an editor, not the conversation; without this file they'd
  have to keep alt-tabbing back to reread a constraint, which is friction
  a real interview whiteboard doesn't have. Write it right after you finalize
  the problem text, so the file and what you said in chat always match.
- **`solution.*`**: the only file the candidate should write in. Empty
  function body (`pass` / `TODO` / equivalent) — never pre-fill so much as an
  edge-case check or a loop skeleton, that's a nudge given away for free.
  The one thing it *should* carry is a short comment above the signature
  documenting each parameter's type/bounds and the return shape, copied
  straight from the constraints in `PROBLEM.md` — that's not a hint about
  the algorithm, it's just sparing the candidate a lookup for information
  they already have. See the per-language file for the exact shape.
- **`interviewer_only/reference_solution.*`**: your actual correct
  implementation of the problem, in a subfolder whose name signals "not for
  you." This is what makes real verification possible — `run_tests` calls
  it to compute expected output and diffs it against the candidate's output.
- **`run_tests.*`**: imports both, runs every test case through both
  implementations, and prints a clear PASS/FAIL per case with input, the
  candidate's actual output, and the expected output. **The default test
  cases should be exactly the worked examples from the problem statement —
  no more.** Don't proactively seed extra edge cases (an empty input, a
  single-element array, whatever) into this file yourself, even ones that
  seem obviously worth covering. Thinking of which edge cases matter is
  part of what's being assessed here, and quietly pre-supplying them is a
  hint just as much as naming an algorithm would be — the candidate should
  have to notice "what if this is empty?" on their own, not find it already
  sitting in the file you handed them. See "Checking edge cases the
  candidate didn't think of" below for where your own edge-case thinking
  actually belongs.

**This relies on the honor system, and that's fine** — say so once when you
hand the files over ("there's a reference solution in `interviewer_only/`
that the test runner uses to check your work — please don't open it, same
as not flipping to the answer key early"). Never paste the reference
solution's code into the chat itself; the whole point of putting it in a
separate file is that it stays out of the conversation the candidate is
reading.

**Verify the reference solution before handing anything over.** You wrote
it, which means it can have the same bugs the candidate might make. Before
presenting the files, actually run `run_tests` yourself with a throwaway
correct-looking `solution.*` (or temporarily point it at the reference
implementation) to confirm the reference solution's outputs match the
worked examples in your problem statement. A wrong reference solution
produces false FAILs against a correct candidate answer — a fast way to
destroy the candidate's trust in the exercise. This takes one Bash call and
is worth it every time.

**Comparisons need to match what the problem actually promises.** Plenty of
problems have multiple valid outputs (e.g. "return the indices in any
order", "any valid subset works") or need tolerance (floating point). A
naive equality check will produce false FAILs on a correct-but-differently-
shaped answer. Write the comparison in `run_tests` to match the problem:
sort before comparing when order doesn't matter, use a tolerance for
floats, compare sets, etc. Get this right in the same pass where you verify
the reference solution.

## Checking edge cases the candidate didn't think of

Your own edge-case thinking still matters — it just belongs at the *end*,
not the start. Once the candidate says they're done (see "Wrapping up" in
`SKILL.md`), and after you've run their existing test suite, come up with a
handful of edge cases based on the stated constraints that their own added
tests *didn't* cover (empty/minimal input if the constraints allow it,
duplicate values, the largest and smallest allowed values, degenerate
shapes specific to the problem) and run those against their final solution
using your reference solution to compute the expected output — the same
verification mechanics as before, just aimed at their code instead of
yours.

Do this in a throwaway/scratch harness rather than editing the candidate's
`run_tests.*` file — appending your own hidden-edge-case tests into their
visible file would leave a permanent record of exactly which edge cases you
thought to check, which quietly telegraphs the answer to whoever looks at
this problem again later (including, in principle, the same candidate on a
similar problem down the line).

The results are real signal for the "edge case handling" part of your
end-of-session feedback: if their solution fails something they never
thought to test, that's worth naming directly, the same way you'd cite a
bug you found reading the code. If it holds up, that's worth crediting too
— don't run this check and then say nothing about it either way.

## Non-coding problem types

For `system_design` and `object_oriented_design` problems, and for
`senior_scenarios` items that are discussion/whiteboard-shaped (e.g. "review
this PR", "debug this incident"), a runnable starter/test bundle usually
isn't the right artifact — there's no single "expected output" to check
against. Instead:

- **System design**: give the prompt as a short brief (like a real design
  interview kickoff) and let the candidate drive with questions, diagrams
  (ASCII is fine), and API sketches. No starter file needed.
- **OOP design**: a minimal class/interface skeleton in their chosen language
  is reasonable (empty class shells with no methods filled in), since the
  "code" here mostly is the design.
- **Debugging/code-review scenarios**: provide the buggy snippet or PR diff
  as the artifact itself, not a template to fill in.
