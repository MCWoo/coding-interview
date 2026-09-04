#!/usr/bin/env python3
"""
Manage the candidate skill-tracking profile for the coding-interview skill.

Why this exists as a script instead of Claude editing JSON by hand: the profile
is read and rewritten every session, and a hand-edited JSON file eventually gets
a trailing comma or a mis-typed level and silently corrupts. This script is the
single writer, validates level names, and always leaves the file in a valid
state (atomic write). It also centralizes the "which category/difficulty is
next" logic so the ramp-up behavior is consistent across sessions instead of
being re-derived from scratch (and possibly inconsistently) every interview.

Default profile location: ~/.claude/coding-interview/candidate_profile.json
This is deliberately OUTSIDE the skill's own directory. The skill directory
may be reinstalled/updated/symlinked; the candidate's history shouldn't live
inside something that gets replaced.

Usage:
  manage_state.py init
  manage_state.py show [--category NAME]
  manage_state.py list
  manage_state.py notes [--category NAME]
  manage_state.py add-category --name NAME [--display-name TEXT]
                   [--level LEVEL] [--source TEXT] [--description TEXT]
  manage_state.py describe-category --category NAME --description TEXT
  manage_state.py suggest [--category NAME] [--exclude-category NAME ...]
  manage_state.py update-level --category NAME --level LEVEL --note TEXT
  manage_state.py log-session --category NAME --difficulty D --language L
                   --duration MIN --outcome TEXT --level-before X --level-after Y
                   [--problem-title TEXT]

All commands accept --profile PATH to override the default location.
"""
import argparse
import json
import os
import random
import re
import sys
import tempfile
from datetime import datetime, timezone

DEFAULT_PROFILE = os.path.expanduser("~/.claude/coding-interview/candidate_profile.json")

LEVELS = ["unknown", "weak", "developing", "proficient", "strong"]
LEVEL_RANK = {lvl: i for i, lvl in enumerate(LEVELS)}

CATEGORIES = [
    "arrays_hashing",
    "two_pointers_sliding_window",
    "stacks_queues",
    "linked_lists",
    "trees_graphs_traversal",
    "graph_algorithms",
    "binary_search",
    "recursion_backtracking",
    "dynamic_programming",
    "greedy_intervals",
    "heaps_priority_queues",
    "system_design",
    "object_oriented_design",
    "senior_scenarios",
]

DIFFICULTY_BY_RANK = {
    0: "easy",        # unknown
    1: "easy",        # weak
    2: "medium",      # developing
    3: "medium",      # proficient (occasional hard, handled by suggest())
    4: "hard",        # strong
}


def now_iso():
    return datetime.now(timezone.utc).isoformat(timespec="seconds")


def normalize_category_name(raw):
    """Turn free-text like 'Game Physics' or 'network-engineering' into a key
    consistent with the built-in categories (arrays_hashing, etc.): lowercase,
    underscore-separated, alphanumerics only."""
    key = re.sub(r"[^a-z0-9]+", "_", raw.strip().lower()).strip("_")
    return key


def load_profile(path):
    if not os.path.exists(path):
        raise SystemExit(f"No profile found at {path}. Run `init` first.")
    with open(path) as f:
        return json.load(f)


def save_profile(path, profile):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    dir_ = os.path.dirname(path)
    fd, tmp_path = tempfile.mkstemp(dir=dir_, prefix=".profile-", suffix=".tmp")
    with os.fdopen(fd, "w") as f:
        json.dump(profile, f, indent=2, sort_keys=False)
        f.write("\n")
    os.replace(tmp_path, path)


def cmd_init(args):
    if os.path.exists(args.profile) and not args.force:
        print(f"Profile already exists at {args.profile} (use --force to reset). Nothing to do.")
        return
    profile = {
        "created_at": now_iso(),
        "categories": {
            cat: {
                "level": "unknown",
                "attempts": 0,
                "last_difficulty": None,
                "last_date": None,
                "history": [],
            }
            for cat in CATEGORIES
        },
        "sessions": [],
    }
    save_profile(args.profile, profile)
    print(f"Initialized profile at {args.profile}")


def cmd_show(args):
    profile = load_profile(args.profile)
    if args.category:
        if args.category not in profile["categories"]:
            raise SystemExit(f"Unknown category: {args.category}")
        print(json.dumps(profile["categories"][args.category], indent=2))
    else:
        print(json.dumps(profile, indent=2))


def cmd_list(args):
    profile = load_profile(args.profile)
    for name, entry in profile["categories"].items():
        display = entry.get("display_name", name)
        tag = " [custom]" if entry.get("custom") else ""
        line = f"{name}{tag}: {entry['level']} ({entry['attempts']} attempt(s)) -- {display}"
        if entry.get("description"):
            line += f" | {entry['description']}"
        print(line)


def cmd_notes(args):
    profile = load_profile(args.profile)
    cats = profile["categories"]
    if args.category:
        if args.category not in cats:
            raise SystemExit(f"Unknown category: {args.category}")
        cats = {args.category: cats[args.category]}

    printed_any = False
    for name, entry in cats.items():
        if not entry["history"]:
            continue
        printed_any = True
        print(f"\n=== {name} ({entry['level']}) ===")
        for h in entry["history"]:
            print(f"[{h['date']}] {h['from_level']} -> {h['to_level']}")
            print(f"  {h['note']}")
    if not printed_any:
        print("No notes yet for" + (f" '{args.category}'" if args.category else " any category") + ".")


def cmd_add_category(args):
    profile = load_profile(args.profile)
    key = normalize_category_name(args.name)
    if not key:
        raise SystemExit("Category name must contain at least one alphanumeric character.")
    if args.level not in LEVELS:
        raise SystemExit(f"--level must be one of {LEVELS}")

    if key in profile["categories"]:
        existing = profile["categories"][key]
        print(f"Category '{key}' already exists (level: {existing['level']}). Nothing to do.")
        return

    profile["categories"][key] = {
        "level": args.level,
        "attempts": 0,
        "last_difficulty": None,
        "last_date": None,
        "history": [],
        "display_name": args.display_name or args.name,
        "custom": True,
        "source": args.source,
        "description": args.description,
    }
    save_profile(args.profile, profile)
    print(f"Added category '{key}' (display: {profile['categories'][key]['display_name']}, "
          f"starting level: {args.level})")


def cmd_describe_category(args):
    profile = load_profile(args.profile)
    if args.category not in profile["categories"]:
        raise SystemExit(f"Unknown category: {args.category}")
    profile["categories"][args.category]["description"] = args.description
    save_profile(args.profile, profile)
    print(f"Set description for '{args.category}': {args.description}")


def cmd_suggest(args):
    profile = load_profile(args.profile)
    cats = profile["categories"]
    forced_revisit = False

    if args.category:
        if args.category not in cats:
            raise SystemExit(f"Unknown category: {args.category}")
        candidates = {args.category: cats[args.category]}
    else:
        excluded = set(args.exclude_category or [])
        candidates = {c: v for c, v in cats.items() if c not in excluded}
        if not candidates:
            candidates = cats  # exclusion list covered everything; ignore it

        # Staleness prevention: the weighting below deliberately favors weak/
        # unknown categories so heavily that once a candidate accumulates a
        # few proficient/strong ones alongside several still-unknown ones,
        # the strong ones become vanishingly unlikely to ever get picked
        # again by the weighting alone. Roughly 1 in 4 sessions, force a
        # revisit of an already-strong category instead -- skills atrophy,
        # and a category that never gets revisited never gets a chance to
        # prove it's still solid.
        strong_pool = {c: v for c, v in candidates.items() if v["level"] in ("proficient", "strong")}
        if strong_pool and random.random() < 0.25:
            candidates = strong_pool
            forced_revisit = True

    # Weight = weaker categories and longer-untouched categories are more
    # likely to be picked. This is what drives the "ramp up from weak areas"
    # behavior described in the skill: a candidate at "unknown" in dynamic
    # programming should keep seeing DP problems (at easy difficulty) far
    # more often than a category they're already "strong" in.
    def weight(entry):
        rank = LEVEL_RANK[entry["level"]]
        base = (len(LEVELS) - rank) ** 2  # unknown=25, weak=16, developing=9, proficient=4, strong=1
        staleness = 1.0
        if entry["last_date"] is None:
            staleness = 1.5  # never practiced: nudge it up further
        return base * staleness

    if forced_revisit:
        # Deterministic-ish, not weighted-random: the point of the forced
        # revisit is a guaranteed check-in on the longest-overdue category
        # (None sorts first, i.e. "never practiced" counts as most overdue).
        # Shuffle first so a genuine tie (e.g. two categories both never
        # practiced since leveling up) doesn't always resolve to whichever
        # was inserted first.
        items = list(candidates.items())
        random.shuffle(items)
        chosen = min(items, key=lambda kv: kv[1]["last_date"] or "")[0]
    else:
        names = list(candidates.keys())
        weights = [weight(candidates[n]) for n in names]
        chosen = random.choices(names, weights=weights, k=1)[0]

    entry = cats[chosen]
    rank = LEVEL_RANK[entry["level"]]

    difficulty = DIFFICULTY_BY_RANK[rank]
    # At "proficient" or "strong", mix in a harder problem sometimes instead
    # of always giving the ceiling difficulty, so the ramp still feels earned.
    if rank == 3 and random.random() < 0.3:
        difficulty = "hard"
    if rank == 4 and random.random() < 0.4:
        difficulty = "open_ended"  # system-design-style stretch problem

    print(json.dumps({
        "category": chosen,
        "level": entry["level"],
        "difficulty": difficulty,
        "attempts_so_far": entry["attempts"],
        "last_date": entry["last_date"],
        "staleness_revisit": forced_revisit,
    }, indent=2))


def cmd_update_level(args):
    if args.level not in LEVELS:
        raise SystemExit(f"--level must be one of {LEVELS}")
    profile = load_profile(args.profile)
    if args.category not in profile["categories"]:
        raise SystemExit(f"Unknown category: {args.category}")
    entry = profile["categories"][args.category]
    entry["history"].append({
        "date": now_iso(),
        "from_level": entry["level"],
        "to_level": args.level,
        "note": args.note,
    })
    entry["level"] = args.level
    save_profile(args.profile, profile)
    print(f"{args.category}: {entry['history'][-1]['from_level']} -> {args.level}")


def cmd_log_session(args):
    profile = load_profile(args.profile)
    if args.category not in profile["categories"]:
        raise SystemExit(f"Unknown category: {args.category}")
    entry = profile["categories"][args.category]
    entry["attempts"] += 1
    entry["last_difficulty"] = args.difficulty
    entry["last_date"] = now_iso()

    profile["sessions"].append({
        "date": entry["last_date"],
        "category": args.category,
        "problem_title": args.problem_title,
        "difficulty": args.difficulty,
        "language": args.language,
        "duration_min": args.duration,
        "outcome": args.outcome,
        "level_before": args.level_before,
        "level_after": args.level_after,
    })
    save_profile(args.profile, profile)
    print(f"Logged session for {args.category} ({args.level_before} -> {args.level_after})")


def build_parser():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--profile", default=DEFAULT_PROFILE, help="Path to candidate_profile.json")
    sub = p.add_subparsers(dest="command", required=True)

    sp = sub.add_parser("init", help="Create a fresh profile (all categories start 'unknown')")
    sp.add_argument("--force", action="store_true", help="Overwrite an existing profile")
    sp.set_defaults(func=cmd_init)

    sp = sub.add_parser("show", help="Print the profile, or one category")
    sp.add_argument("--category")
    sp.set_defaults(func=cmd_show)

    sp = sub.add_parser("list", help="List every category (built-in and custom) with its level")
    sp.set_defaults(func=cmd_list)

    sp = sub.add_parser("notes", help="Print the feedback/rationale notes behind every level change")
    sp.add_argument("--category", help="Only show notes for this category")
    sp.set_defaults(func=cmd_notes)

    sp = sub.add_parser("add-category", help="Add a custom category (e.g. a specialization) to track")
    sp.add_argument("--name", required=True, help="Category name, e.g. 'Game Physics' or 'network-engineering'")
    sp.add_argument("--display-name", help="Human-readable label if different from --name")
    sp.add_argument("--level", default="unknown", choices=LEVELS, help="Starting level (default: unknown)")
    sp.add_argument("--source", default=None, help="Where this came from, e.g. 'job description: Senior Graphics Engineer'")
    sp.add_argument("--description", default=None,
                    help="What this category actually covers, esp. if the name is ambiguous "
                         "(e.g. 'language internals/semantics for whatever language is picked "
                         "that session, not syntax trivia') -- future sessions read this instead "
                         "of re-deriving scope from a conversation they don't have access to")
    sp.set_defaults(func=cmd_add_category)

    sp = sub.add_parser("describe-category", help="Set/update a category's description (works on built-in categories too)")
    sp.add_argument("--category", required=True)
    sp.add_argument("--description", required=True)
    sp.set_defaults(func=cmd_describe_category)

    sp = sub.add_parser("suggest", help="Suggest a category + difficulty for the next problem")
    sp.add_argument("--category", help="Force a specific category instead of weighted pick")
    sp.add_argument("--exclude-category", action="append", help="Exclude a category (repeatable)")
    sp.set_defaults(func=cmd_suggest)

    sp = sub.add_parser("update-level", help="Record a change in a category's assessed level")
    sp.add_argument("--category", required=True)
    sp.add_argument("--level", required=True, choices=LEVELS)
    sp.add_argument("--note", required=True, help="Why the level changed (short rationale)")
    sp.set_defaults(func=cmd_update_level)

    sp = sub.add_parser("log-session", help="Append a completed interview session to history")
    sp.add_argument("--category", required=True)
    sp.add_argument("--difficulty", required=True)
    sp.add_argument("--language", required=True)
    sp.add_argument("--duration", required=True, type=int, help="Minutes spent")
    sp.add_argument("--outcome", required=True, help="Short summary of how it went")
    sp.add_argument("--level-before", required=True, choices=LEVELS)
    sp.add_argument("--level-after", required=True, choices=LEVELS)
    sp.add_argument("--problem-title", default=None)
    sp.set_defaults(func=cmd_log_session)

    return p


def main():
    args = build_parser().parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
