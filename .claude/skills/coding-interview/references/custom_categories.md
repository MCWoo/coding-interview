# Custom categories & specializing from a job description

The built-in taxonomy in `references/categories.md` covers general DS&A plus
system design/OOP/senior scenarios, but plenty of real interviews (and real
jobs) go narrower — game physics, graphics programming, network engineering,
embedded systems, distributed systems, whatever the candidate is actually
interviewing for. The candidate can add categories for any of that.

**Adding one directly** ("add game physics as a category", "I want to
practice network engineering"): run
`python3 scripts/manage_state.py add-category --name "NAME"` (add
`--source "..."` to note why, e.g. "user-requested specialization"). It
normalizes the name into a key consistent with the built-in ones and starts
it at `unknown`, same as everything else. It's idempotent — safe to call
even if you're not sure whether it already exists.

If the name is at all ambiguous about what it actually covers (e.g.
"language-specific questions" could mean syntax trivia, internals/semantics,
tooling, or something else entirely), ask the candidate a quick clarifying
question about scope before or right after adding it, then persist the
answer with `--description "..."` at creation time (or
`describe-category --category NAME --description "..."` afterward). This
matters more than it might seem: a future session has no memory of this
conversation, so without a saved description it would have to guess the
scope from the name alone every time it picks a problem for that category.

The description field also exists to hint whether the category is
codeable/bundle-shaped or discussion-shaped — putting a note like "not tied
to a starter-code bundle unless a specific question is naturally codeable"
into the description saves a future session from re-deriving that too.

**Deriving categories from a job description** (candidate pastes text, or
gives you a link — use WebFetch if it's a URL and that tool's available):
read it and pull out a shortlist (roughly 3-6) of *topic areas* that go
beyond what the built-in taxonomy already covers — things like "distributed
systems", "GPU/graphics programming", "low-latency networking",
"embedded/real-time systems", "compilers", "security/cryptography", not
"arrays" or "recursion" which are already tracked categories. **Propose the
shortlist to the candidate and let them confirm or edit it before adding
anything** — don't silently add categories from a JD skim without a check-in,
since the candidate may not want to track every tangential requirement a
posting mentions. Once confirmed, add each one with
`--source "job description: <role/company if known>"` so it's clear later
where it came from, and a `--description` summarizing what you understood
the topic to mean from the posting's context (same reasoning as above —
save the scope now, don't make a future session re-derive it).

Once added, a custom category behaves exactly like a built-in one — `suggest`,
`update-level`, and `log-session` all already work on whatever's in the
profile generically, nothing special to do there. Run
`python3 scripts/manage_state.py list` any time to see every category
(built-in and custom) with its current level in one glance, which is
especially useful once the list gets long.

**Designing problems for a custom category** is more freeform than the DSA
taxonomy, since there's no pre-built pattern list to draw from — use
judgment the same way you would for `system_design`/`senior_scenarios`.
Some custom-category problems are genuinely codeable (e.g. "implement a
spatial hash grid for broad-phase collision detection" for game physics, or
"implement a token-bucket rate limiter" for network engineering) and should
get the same four-file bundle as any DSA problem; others are inherently
discussion/design-shaped (e.g. "how would you debug intermittent packet
loss between two services") and shouldn't be forced into a starter-code
bundle just for consistency. Decide per problem, not per category. Custom
categories also don't need the scenario-skinning treatment from
`references/scenario_skinning.md` — a "network engineering" or "game
physics" problem is already domain-specific by construction, the same
exemption as `system_design`/`senior_scenarios`. The same five-level ladder
(`unknown` → `weak` → `developing` → `proficient` → `strong`) and its
behavioral anchors in `references/categories.md` still apply — there's just
no domain-specific anchor to look up, so lean on the general anchors and
your own judgment of what "proficient at network engineering problems"
should look like.
