# How system design interviews are actually assessed

DSA problems have an obvious ground truth — a test suite either passes or it
doesn't, and complexity is a fact about the algorithm. System design has no
equivalent oracle: there's no single correct architecture for "design a URL
shortener," so the assessment has to rest on *how the candidate reasoned*,
not whether they landed on some canonical diagram. This file exists because
that distinction isn't obvious if you haven't sat on the other side of one
of these before — use it alongside the generic level ladder in
`categories.md` when assessing `system_design`, and for the design-shaped
parts of `senior_scenarios` and `object_oriented_design`.

Caveat on sourcing: companies like Google/Meta/Amazon don't publish their
internal rubrics. What follows is synthesized from how system design
interviews are consistently described across engineering-interview prep
material and reporting on the format — treat it as "how these are commonly
run and scored in practice," not a leaked official document. The pattern is
consistent enough across sources to be a reliable basis for this skill.

## The six axes interviewers actually watch

Real loops vary in exact wording, but they consistently reduce to some
subset of these. Watch for all of them during the interview — the feedback
at wrap-up should be organized along these lines, not just "good job" or
"needs work":

1. **Requirements gathering.** Did the candidate ask what the system
   actually needs to do before designing it — functional requirements
   (what operations, what data), non-functional requirements (read/write
   ratio, latency expectations, consistency needs, scale), and explicit
   non-goals? A candidate who starts drawing boxes before asking a single
   question is optimizing for looking busy, not for building the right
   thing — exactly the failure mode a real interviewer is watching for.

2. **High-level architecture.** Can they decompose the problem into
   sensible components (services, data stores, caches, queues) with clear
   responsibilities and sane boundaries between them? This is the "big
   picture correct" check — not every box has to be optimal, but the
   decomposition has to hang together logically.

3. **Deep dive / technical depth.** Once the high-level shape exists, can
   the candidate go a level deeper on the one or two components that
   actually matter for this problem — the data model, an API contract, how
   a specific component scales or fails? This is where a lot of candidates
   run out of runway (see "Common failure mode" below), and it's also where
   the strongest signal lives, because shallow breadth is easy to fake and
   deep correctness isn't.

4. **Trade-off reasoning.** Across most sources, this is called out as the
   single most differentiating axis. Nearly any design choice has a
   plausible alternative (SQL vs. NoSQL, strong vs. eventual consistency,
   push vs. pull, normalize vs. denormalize) — what interviewers are
   actually grading is whether the candidate *names* the tension, weighs it
   against the stated requirements, and picks a side with a reason, rather
   than asserting one option as simply correct. A choice that's never
   framed as a trade-off doesn't earn credit for the trade-off axis even if
   it happens to be the "right" choice — the reasoning has to be
   externalized, not just arrived at.

5. **Scalability and operational awareness.** Can they reason quantitatively
   about scale when it matters — rough traffic/storage estimates, where the
   bottleneck will actually appear, what happens at 10x — rather than just
   name-dropping "we'd add caching" or "we'd shard the database" without
   connecting it to a number or a specific bottleneck in *this* design.
   Fault tolerance falls under the same axis: what happens when a component
   dies, and does the design degrade gracefully or fall over.

6. **Communication.** Is the reasoning narrated as it happens, not
   reconstructed after the fact when asked? A design that's correct but
   only exists in the candidate's head until you extract it with questions
   reads very differently from one where the candidate is thinking out loud
   and inviting course-correction. This maps directly to this skill's
   existing "Thinking aloud" guidance in the main `SKILL.md` — system design
   is the category where that behavior matters most, because the format has
   no code to fall back on reading afterward.

## How seniority raises the bar on the *same* axes

The axes above don't change with level — what counts as a strong showing on
each one does. This matters a lot for calibrating `developing` vs.
`proficient` vs. `strong`:

- **Requirements gathering:** a mid-level candidate asking good clarifying
  questions when prompted is fine; a senior/staff candidate is expected to
  *drive* this themselves, and even to surface a requirement the prompt
  didn't state outright (e.g. noticing that "design a notification system"
  implicitly needs a dedup/rate-limiting story the prompt never mentioned).
- **Architecture:** junior/mid candidates are expected to reach *a*
  reasonable design. Senior+ candidates are expected to identify which part
  of the problem is actually hard and steer the conversation there
  themselves, rather than treating every component as equally worth time.
- **Scalability:** "we'd add a cache" is an acceptable mid-level answer.
  "At this write volume, here's the rough number of writes/sec, here's
  where that saturates a single Postgres primary, and here's why I'd shard
  on X rather than Y" is the senior-level version of the same idea — the
  presence of actual numbers and a specific bottleneck is the tell.
- **Organizational/operational concerns** (cost, migration path, team
  ownership boundaries, build-vs-buy) show up more at senior/staff/EM-flavored
  scenarios than at a standard mid-level loop — don't expect this from an
  `unknown`/`weak`-level candidate, but it's fair to probe for it once a
  candidate's profile suggests they're operating at that level.

When assessing a session, read the candidate's actual behavior against the
expectation for *their current tracked level*, not some fixed abstract bar —
the same way a `weak`-level candidate solving a problem with heavy nudging
caps at `developing` in the DSA categories, a `developing`-level system
design candidate who reaches a reasonable design with help on the deep dive
is showing exactly what's expected of that level, not falling short of some
universal standard.

## Common failure mode: running out of the clock before the deep dive

This comes up often enough to call out on its own: a candidate who spends
too long on requirements-gathering and the high-level sketch never reaches
the deep-dive portion, where the strongest signal actually lives. If a
session is trending this way, a light time-boxing nudge ("let's lock in the
high-level shape and go deeper on the data model") is fair — same spirit as
this skill's existing nudge guidance for DSA problems, just redirecting
pacing rather than hinting at a technique. Don't let a candidate burn 40 of
60 minutes drawing boxes and then have nothing to assess on axes 3-5.

## Applying this to assessment and feedback

At wrap-up, structure the feedback (SKILL.md's "Give feedback" step) around
whichever 2-4 of the six axes above were actually load-bearing for this
particular problem — not all six always apply with equal weight (a
"design a rate limiter" problem leans hard on architecture + trade-offs,
while "design a notification system" leans on requirements + scalability).
Call out explicitly which requirements or trade-offs never got addressed at
all, the same way an unaddressed requirement in the live session (see the
Viasat-platform session's missed cross-cloud-visibility requirement as a
concrete example of this) is worth naming specifically rather than letting
a generally-good session read as uniformly complete.

For the level ladder itself (`categories.md`), the generic anchors still
apply — map "needed significant hints to find an approach" etc. onto
whichever axis actually needed the hint. A candidate who nailed the
architecture but needed heavy prompting to produce any trade-off reasoning
at all is a different `developing` than one who nailed trade-offs but
produced a disorganized architecture — both land on the same level, but the
feedback and the "what to improve" should name the specific axis, not just
the level number.
