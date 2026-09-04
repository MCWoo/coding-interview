#!/usr/bin/env bash
# Symlink this skill into ~/.claude/skills so it's available in every project.
# Safe to re-run: if the symlink already points here, it's a no-op; if a
# different skill occupies the name, it asks before touching it.
set -euo pipefail

SKILL_SRC="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SKILL_NAME="$(basename "$SKILL_SRC")"
TARGET_DIR="${HOME}/.claude/skills"
TARGET="${TARGET_DIR}/${SKILL_NAME}"

mkdir -p "$TARGET_DIR"

if [ -L "$TARGET" ] && [ "$(readlink "$TARGET")" = "$SKILL_SRC" ]; then
  echo "Already installed: $TARGET -> $SKILL_SRC"
  exit 0
fi

if [ -e "$TARGET" ]; then
  echo "Something already exists at $TARGET (and it's not a symlink to this skill)."
  echo "Remove or rename it, then re-run this script."
  exit 1
fi

ln -s "$SKILL_SRC" "$TARGET"
echo "Installed: $TARGET -> $SKILL_SRC"
echo "The skill is now available in every project. Candidate progress is stored"
echo "separately at ~/.claude/coding-interview/candidate_profile.json, so"
echo "reinstalling or updating this skill later won't touch your saved history."
