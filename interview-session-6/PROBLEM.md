# Rhythm Game Combo Paths

You're building the scoring engine for a rhythm game. On each move, the
player advances their combo counter by either **1** or **2** beats. Given a
target beat count `n`, count the number of distinct move sequences that
land the combo counter on exactly `n` — order matters, so advancing by
`1` then `2` is a different sequence from `2` then `1`.

**Signature:** `int solution(int n)`

**Constraints:**
- `1 <= n <= 45`

**Examples:**
- `n = 1` → `1` (`[1]`)
- `n = 2` → `2` (`[1,1]`, `[2]`)
- `n = 3` → `3` (`[1,1,1]`, `[1,2]`, `[2,1]`)
- `n = 4` → `5` (`[1,1,1,1]`, `[1,1,2]`, `[1,2,1]`, `[2,1,1]`, `[2,2]`)

## Extension: Blocked Beats

Some beat values are now **blocked** — a hazard the combo counter must
never land on at *any* point during the sequence, not just at the end.
Given `n` and a list of blocked beat values, count the distinct move
sequences that reach exactly `n` without ever landing on a blocked beat
along the way.

**Signature:** `int solutionExtended(int n, vector<int>& blockedBeats)`

**Constraints:**
- `1 <= n <= 45`
- `0 <= blockedBeats.size() <= n`, all values distinct and in `[0, n]`

**Examples:**
- `n = 4, blockedBeats = [2]` → `1` (only `[1,2,1]` avoids landing on beat 2 — every other sequence passes through it)
- `n = 5, blockedBeats = [3]` → `2`
- `n = 6, blockedBeats = []` → `13` (no blocks — same as the base problem)
