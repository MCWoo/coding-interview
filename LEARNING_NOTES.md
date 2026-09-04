# Learning Notes

Concepts and tools explicitly asked about while working on this project.

## Claude Code skills: is `--flag` invocation syntax "officially supported"?

Asked while designing the `--new-category` / `--status` / `--list-categories`
/ `--notes` shortcuts on `/coding-interview`.

Slash-command invocations in Claude Code pass everything after the command
name to the model as plain text — there's no built-in argument parser that
recognizes `--flag` syntax as special. So `--status` isn't "officially
supported" flag syntax in the way a CLI framework's `argparse` would treat
it; it's just text the skill's instructions are written to recognize and
act on, the same way they'd recognize any other natural-language request
("show me my status"). This means flag-style shortcuts are a documentation
convention inside `SKILL.md` (pattern-match on the args text), not a
code-level parsing feature — which is also why they can coexist with
natural language ("how am I doing?") triggering the same behavior.

## JavaScript: does `Array.prototype.reduce` add by default?

Asked while writing a candidate solution during a mock interview session.

No — `reduce` has no default operation. It takes a callback
`(accumulator, currentValue) => ...` plus an optional initial value, and
just applies whatever the callback does across the array, threading the
return value forward as the accumulator each step. "Summing" is the most
common use, but that's a property of writing `(a, b) => a + b` as the
callback, not something `reduce` does on its own — pass any lambda (max,
string concatenation, building up an object) and it does that instead. If
no initial value is given, the first array element is used as the starting
accumulator and reduction starts from index 1.
