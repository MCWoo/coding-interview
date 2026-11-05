# coding-interview

A persistent [Claude Code](https://claude.com/claude-code) skill that runs
realistic mock technical interviews — DS&A, system design, OOP design, and
senior/principal-level scenarios (debugging, API design, concurrency,
tradeoff discussions) — and tracks your skill level per category across
sessions so difficulty ramps appropriately over time.

## What it does

- Picks a problem (or lets you pick a category) using a per-category skill
  profile, weighted toward categories you're weak in or haven't practiced
  recently.
- Presents an original problem, wrapped in a short real-world scenario, with
  a runnable four-file starter bundle (problem statement, empty solution
  stub with parameter-bounds comments, a hidden reference solution, and a
  test harness) in your language of choice (Python, JavaScript, Java, Go, or
  C++).
- Acts as an interviewer while you work: answers clarifying questions,
  nudges rather than answers when you're stuck, tracks wall-clock time,
  and actually compiles/runs your solution itself rather than trusting
  pasted output.
- If you solve the base problem cleanly with time to spare, may offer a
  harder extension of the same problem to keep assessing you in the same
  session.
- At wrap-up: verifies your final solution (including edge cases you didn't
  think to test, checked in a scratch harness — never edited into your
  files), asks about time/space complexity, gives direct feedback on your
  approach and code quality, and updates your tracked skill level for that
  category.
- For system design (no test suite to fall back on), assesses against the
  six axes real system design loops actually score — requirements
  gathering, architecture, deep-dive depth, trade-off reasoning,
  scalability, communication — detailed in
  `.claude/skills/coding-interview/references/system_design_assessment.md`.
- Supports adding your own specialized categories (e.g. "game physics",
  "network engineering") by hand or derived from a pasted/linked job
  description.

## Layout

```
.claude/skills/coding-interview/   # the skill itself — SKILL.md + references/ + scripts/
session-01/, session-02/, ...      # local practice session bundles (gitignored — see below)
```

Each `session-NN/` directory (sequential, zero-padded — never named after
the category, so old sessions don't give away the answer before you reopen
them) holds:

- `PROBLEM.md` — the problem statement
- `solution.<ext>` — your starter stub
- `interviewer_only/reference_solution.<ext>` — the hidden answer key
  (honor system — don't open it)
- `run_tests.<ext>` — compiles/runs your solution against the worked
  examples from the problem statement

`session-NN/` directories are gitignored: they're personal practice
history (including hidden answer keys), not part of the skill.

## Installing

This skill is meant to work the same way across every project, with
progress persisted regardless of which project you're in:

```bash
.claude/skills/coding-interview/scripts/install.sh      # macOS/Linux
.claude/skills/coding-interview/scripts/install.ps1     # Windows (PowerShell)
```

This symlinks the skill directory into `~/.claude/skills/`
(`%USERPROFILE%\.claude\skills\` on Windows). Re-running is safe
(idempotent).

To remove it: the matching `uninstall.sh` / `uninstall.ps1` (pass
`--purge-history` / `-PurgeHistory` to also delete your saved profile).

## Using it

Invoke with `/coding-interview` in any project. A few shortcuts on the same
invocation:

- `/coding-interview --status` — see your current level per category
- `/coding-interview --list-categories` — list every category, built-in and
  custom
- `/coding-interview --notes [category]` — review past feedback, not just
  levels
- `/coding-interview --new-category "NAME"` — add a custom category without
  starting a session

Otherwise, just invoke it and answer the setup questions (language, timing,
IDE/editor, optionally a category) to start a session. If you're using VS
Code, the skill writes a matching `.vscode/tasks.json` (and `launch.json`
for compiled languages) into the session directory so the build task uses
the right compiler from the first keystroke, rather than relying on the
C/C++ extension's auto-generated default.

## Learning workspace

`learning/` is a separate teaching workspace (built with the `teach` skill)
for following up on gaps a mock interview surfaces — e.g. after session-08
flagged weak Argo CD/Ansible/observability understanding, `learning/`
holds the mission, curated resources, and self-contained HTML lessons for
closing those gaps. Not gitignored — unlike `session-NN/`, this is written
material meant to persist and be revisited, not a hidden answer key.

## State

Your candidate profile (per-category skill levels, session history, and
feedback notes) lives at `~/.claude/coding-interview/candidate_profile.json`
— outside this repo, so it survives reinstalling or updating the skill.
