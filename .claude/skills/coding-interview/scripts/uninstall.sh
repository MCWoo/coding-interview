#!/usr/bin/env bash
# Remove the ~/.claude/skills symlink created by install.sh.
# This does NOT delete your candidate_profile.json (your saved skill-level
# history) — that lives in ~/.claude/coding-interview/ and survives even if
# you uninstall or reinstall the skill itself. Pass --purge-history to also
# delete it, if you really want to start over from scratch.
set -euo pipefail

SKILL_SRC="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SKILL_NAME="$(basename "$SKILL_SRC")"
TARGET="${HOME}/.claude/skills/${SKILL_NAME}"
PROFILE_DIR="${HOME}/.claude/coding-interview"

if [ -L "$TARGET" ]; then
  rm "$TARGET"
  echo "Removed symlink: $TARGET"
elif [ -e "$TARGET" ]; then
  echo "$TARGET exists but isn't a symlink to this skill; leaving it alone."
else
  echo "Nothing installed at $TARGET; nothing to do."
fi

if [ "${1:-}" = "--purge-history" ]; then
  rm -rf "$PROFILE_DIR"
  echo "Purged saved candidate history at $PROFILE_DIR"
else
  echo "Your candidate history (if any) is untouched at $PROFILE_DIR"
fi
