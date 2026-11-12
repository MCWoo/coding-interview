# Whiteboard support (system design / OOP design)

## Why this exists

Real system design and OOP design interviews are rarely typed prose —
candidates sketch boxes, arrows, and data flows on a literal or virtual
whiteboard, and a lot of the signal (does the architecture hang together
visually, does a data-flow arrow go the wrong way, does a component get
drawn and then silently disappear from later revisions) lives in that
diagram, not just in what the candidate says about it. Letting a candidate
use whatever online whiteboard tool they'd normally reach for (Miro,
Excalidraw, FigJam, tldraw, Google Jamboard, or anything else) makes the
session closer to the real thing, and gives you material for the debrief
that a transcript of spoken descriptions alone wouldn't.

This is optional and tool-agnostic. The candidate picks whatever
whiteboard tool they already like — you're not picking one for them, and a
candidate with no browser-accessible tool handy should default to ASCII
diagrams in chat instead, which works fine and isn't a lesser interview,
just a different medium (plenty of real remote interviews are conducted
that way too).

## When to offer it

Ask about this once the category is settled, for `system_design`,
`object_oriented_design`, or a design-shaped `senior_scenarios` problem —
not for DSA categories, where there's nothing to diagram. This is why it
can't be folded into the step 2 setup questions (language/timing/IDE) the
way those are: category usually isn't known until step 3's `suggest` call
runs, one step later. Fold the question in naturally right before you
write the problem statement: "Want to use a whiteboard tool for this one —
Miro, Excalidraw, FigJam, whatever you've got — or keep it to ASCII/text
here in chat?"

## Setup: how you'll actually view it

**Check for a configured whiteboard MCP first.** Run `ToolSearch` with a
query like `"miro board whiteboard diagram"` before assuming you need the
browser. A board-reading MCP (if the candidate has one configured) gives
you exact, structured content — shapes, text, connectors — instead of a
screenshot you have to visually interpret, so it's strictly better when
available.

If the Miro MCP server turns up (`mcp__miro__*` tools), ask the candidate
for their board's URL and use only the **read** tools — `canvas_search`
(an overview pass to find what's on the board, or to narrow down an area)
and `canvas_read_as_svg` (the actual content, as structured data you can
reason about directly: shape labels, text, connector endpoints). Never
touch a `*_create`, `*_update`, `*_move`, or other write tool — see the
read-only guardrail below, which this is a specific case of. You do not
need `canvas_get_canvas_composer_skill` for this; that skill is about the
authoring/DSL workflow for *creating or editing* board content, which
you're never doing here.

**Despite the name, what `canvas_read_as_svg` returns is not renderable
SVG** — it's Miro's own "Canvas Composer" authoring/diffing format (the
same shape `canvas_create_from_svg`/`canvas_update_from_svg` consume to
write content back), using non-standard tags like `<textArea>` and
coordinates that don't map into a sensible viewBox. It's genuinely useful
for *you* to read and reason about during the session — that part holds
up fine — but writing it straight to a `.svg` file produces a blank or
broken image for the candidate. Don't save it as a final artifact; see
"Saving the final diagram" below for the actual mechanism.

A different whiteboard MCP (not Miro) may expose a different tool
surface — apply the same principle (read-only tools, structured content
over a screenshot) rather than looking for these exact names.

**Otherwise, use Claude in Chrome** (the common case today — don't block
the session waiting for an MCP that probably isn't configured). Load the
tools you'll need in one `ToolSearch` call rather than one at a time (see
the `claude-in-chrome` skill for the exact set and why batching matters).
Ask the candidate to open their board in a Chrome tab and tell you once
it's up; use the tab-listing tool to find it rather than guessing which
tab is theirs, and confirm the tab with them once before relying on it for
the rest of the session. From there, a screenshot of that tab is how you
"read" the diagram — you have vision, so look at it directly and reason
about what's actually drawn, the same way you'd read code.

**If neither is available** (no MCP, no browser extension, or the
candidate just doesn't want to grant tab access), don't push — fall back
to ASCII/text diagrams in chat, same as if they'd never been asked.

**Guardrail: read-only, always.** Never click, type, draw, or otherwise
modify anything on the candidate's board — it's their diagram the same way
their code is their code. Stay in the single tab they shared; don't
navigate elsewhere in their browser. Avoid anything that could trigger a
browser dialog (see the `claude-in-chrome` skill's cautions on this) since
it can silently block every later check-in.

## Checking the whiteboard mid-interview

The same trust-but-verify instinct from "Checking the candidate's
solution" in `SKILL.md` applies here: when the candidate says "take a
look" or describes what they've drawn, actually look (`canvas_read_as_svg`
if you're on the Miro MCP, a fresh screenshot otherwise) rather than
taking their verbal description at face value. A candidate's spoken
summary of their own diagram can lag what's actually on the board, the
same way pasted terminal output can be stale.

**Periodic checks fold into the existing recurring check-in**, not a
second parallel cron job — see `references/scheduled_checkins.md` for the
mechanics of that job. When a whiteboard is in use, extend that single
recurring job's prompt to also capture the board's current state
(`canvas_read_as_svg`, or a screenshot) and append what changed to the
same `.interviewer_notes` file, right alongside the code observations — e.g. "a
message queue was added between the API layer and the worker service" is
exactly the same flavor of process signal as "switched from a hash map to
a sorted array," just about the diagram instead of the code.

**Nudge on the diagram the same way you'd nudge on code** — see "Nudges,
not answers" in `SKILL.md`; nothing different applies here except the
subject matter. If the diagram reveals something load-bearing (a missing
component the requirements call for, a data flow drawn backwards, a single
point of failure the candidate hasn't addressed), ask a question about it
rather than naming the fix: "What happens to requests in flight if this
service here goes down?" rather than "You need a load balancer." Keep
using the lightest nudge that could plausibly unstick them, same as
always.

**Also watch for the diagram going quiet on something that matters, not
just for what it does show.** A candidate can talk through an entire flow
in detail — a read path, a failure-handling story, a data-replication
scheme — and never actually put it on the board, especially once a
whiteboard is available and some other part of the design is visually
"done." Don't wait until wrap-up to notice this: if a check-in or a direct
look shows the diagram has stayed still on a component or flow the
conversation has clearly moved past, that's worth a live nudge in the
moment ("Want to sketch that redirect path too, now that you've talked it
through?") — the same way you'd ask a candidate to actually write the code
they just described verbally, rather than letting "I'd write it like
this..." stand in for having written it.

## Saving the final diagram

At wrap-up, as part of "Verify and read the final state" in `SKILL.md`,
capture one last image of the board and save it as
`<problem-dir>/whiteboard_final.png`. **This is always a real screenshot,
regardless of how you were reading the board during the session** — there
is no reliable whole-board export-to-image tool in the Miro MCP surface
(`canvas_read_as_svg`'s output isn't a renderable image; see the note
above), so even a session conducted entirely through the MCP needs a
browser for this one step:

1. Load the Claude-in-Chrome tools if you haven't already (one
   `ToolSearch` call for the usual set).
2. Open the candidate's board URL in a new tab.
3. Give it a moment to load, then press `Shift+1` (Miro's zoom-to-fit
   shortcut) so the whole diagram is in frame — the default view after
   loading is often centered somewhere that doesn't show all the content,
   especially if the candidate panned around while building it.
4. Take a screenshot with `save_to_disk: true` and copy the saved file to
   `<problem-dir>/whiteboard_final.png`.
5. Close the tab you opened for this (see the `claude-in-chrome` skill on
   cleaning up tabs you create).

If you already had the board open in a candidate-shared tab all session
(the browser-screenshot path, not MCP), just reuse that tab for the same
zoom-to-fit-then-screenshot steps instead of opening a new one.

Mention this to the candidate the same way you mention `interviewer_only/`
being theirs to read now: it's a real artifact of the session worth
having, not a hidden answer key, so there's no honor-system framing
needed for it.

This file isn't scratch the way `.interviewer_notes` is — it persists in
the session directory alongside `PROBLEM.md`, not deleted at wrap-up.
