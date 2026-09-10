# Scheduled check-ins (CronCreate)

Without these, time-awareness and process-awareness both depend on the
candidate happening to send a message at the right moment — a spoken time
update only lands if they message you near the 10-minute mark, and your
sense of "how did they get here" is reconstructed after the fact from
whatever's in the conversation plus one final read of the file. `CronCreate`
lets you do both proactively instead: reminders fire on their own schedule
regardless of what the candidate's doing, and periodic silent reads of the
working file build a real, checkable record of the candidate's actual
process — dead ends, backtracks, the order things happened in — not just
the final diff.

## What to schedule, and when

`CronCreate` and `CronDelete` may be deferred tools in your environment
(listed by name only, schema not yet loaded) — if so, load both with
`ToolSearch` (e.g. `select:CronCreate,CronDelete`) before your first call,
the same as any other deferred tool.

Set these up in session flow step 4, right after you capture `.started_at`
— that's when you have the real start time and end time (if any) in hand.

**Every session, timed or self-timed — a periodic silent read:**
```
CronCreate(cron="*/3 * * * *", recurring=true, prompt="Silently read the
candidate's current solution file(s) in <problem-dir> and append ONE
short, timestamped line to <problem-dir>/.interviewer_notes (create it if
it doesn't exist) describing what you observe -- e.g. an approach they
tried and abandoned, a bug they introduced or fixed, a shift in strategy.
Do not output any chat text, ask any question, or otherwise interact with
the candidate -- this is a background note-taking pass only.")
```
The general cron guidance about avoiding round minute marks (`:00`/`:30`)
exists to prevent many different users' sessions from all hitting the API
in the same instant — that's not really a concern for a single candidate's
private note-taking job, so don't overthink the exact schedule here.

**Timed sessions only (60/90 min) — proactive time nudges**, computed from
the real clock (same `date -d "+N minutes"` arithmetic you already use to
state the end time):
```
CronCreate(cron="<halfway time>", recurring=false, prompt="Give the
candidate a brief, low-key heads-up that about half the time is gone,
then let them keep working.")

CronCreate(cron="<10-min-remaining time>", recurring=false, prompt="Give
the candidate a brief heads-up that about 10 minutes remain, then let
them keep working.")

CronCreate(cron="<2-min-remaining time>", recurring=false, prompt="Give
the candidate a brief heads-up that about 2 minutes remain, then let them
keep working.")

CronCreate(cron="<end time>", recurring=false, prompt="Time is up for
this session. Let the candidate know, ask if they want a couple more
minutes to finish a thought or want to stop where they are, then move to
wrap-up either way (see 'Wrapping up' in SKILL.md) regardless of their
answer.")
```
Self-timed sessions skip all four of these — there's no deadline to count
down to — but still get the periodic silent read above.

**Keep every job ID CronCreate returns** (in your own context for the
session is enough — no need to write them to a file) so you can cancel
them all at wrap-up. A session that ends early (candidate finishes well
before the timer, or stops mid-problem) would otherwise leave jobs
pending that fire *after* the interview is already over — including,
awkwardly, a "time's up" nudge or a silent-read pass landing in the middle
of an unrelated conversation the candidate has with you afterward.

## At wrap-up

Before you give feedback (fold this into "Verify and read the final
state" in the Wrapping up section of `SKILL.md`): if
`<problem-dir>/.interviewer_notes` exists, read it. It's real signal about
process that a single end-of-session read of the final file can't
reconstruct — a note like "10:14 — tried a two-pointer approach, backed
out after ~4 min, switched to a hash map" tells you something the finished
code alone doesn't. Use anything genuinely useful the same way you'd use
your own live observations during the interview; don't feel obligated to
cite every line if most of it was just "still writing the same function."

Once you're done with it:
1. **Cancel every cron job you created for this session** via
   `CronDelete` on each tracked job ID — the periodic read especially must
   not keep firing after the interview's over.
2. **Delete `.interviewer_notes` itself.** It's working scratch for this
   session, not a lasting artifact the way `PROBLEM.md` or the candidate's
   solution file are — once its content has fed into your feedback, it
   shouldn't linger in the problem directory.

## If CronCreate isn't available

Don't block the session on it — if a `CronCreate` call fails or the tool
isn't available for some reason, fall back to the manual wall-clock checks
described in "Tracking time" in `SKILL.md` (checking `date +%H:%M` against
the stated end-time whenever it's natural to do so). The scheduled version
is strictly better when it's available, not a hard requirement for the
skill to function.
