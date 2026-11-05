# IDE project setup

## Why this exists

A candidate once ended up compiling C++ with plain `gcc` instead of `g++`
— the fix was to run `g++` manually (see `references/languages/cpp.md`), but
the root cause was upstream of that: in VS Code specifically, hitting
"Run"/F5 on a `.cpp` file with no `tasks.json` present triggers the C/C++
extension's auto-generated default build task, which is commonly labeled
something like "C/C++: gcc build active file" and does exactly what it says
— invokes `gcc`, which can't link the C++ standard library and produces
linker errors on anything using `iostream`/`std::`. Writing a correct
`tasks.json` up front, as part of handing over the problem bundle, means the
candidate never encounters that auto-generated default in the first place.

## Ask every session

As part of setup (alongside language and timing), ask what IDE/editor the
candidate is using. Don't skip this just because a prior session already
asked — unlike the specialization/custom-category mention, candidates
reasonably switch machines or editors between sessions, so there's no safe
default to fall back on here the way there is elsewhere.

- **VS Code** → write the project files below into the session directory,
  alongside the four bundle files, before handing the problem over.
- **CLion, Visual Studio, Eclipse/IntelliJ, Vim/Emacs + terminal, or
  anything else** → no scaffolding to write (no template exists yet for
  these) — just make sure the candidate has the compile/run command from
  the relevant `references/languages/*.md` file, same as today. If the
  candidate offers to share their own sample config for one of these, it's
  reasonable to save it under this directory for next time (ask first
  rather than assuming the one sample generalizes to every candidate/IDE
  combination).

## VS Code project files, per language

Write these into `<session-dir>/.vscode/` using the Write tool, right after
the four bundle files. The compile/run command embedded in each one is
pulled from that language's reference doc — if you ever change the command
in `references/languages/<lang>.md`, update the matching template here too
so they don't drift apart.

### C++

`'.vscode/tasks.json`:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++ build active file",
            "command": "/usr/bin/g++",
            "args": [
                "-std=c++17",
                "-fdiagnostics-color=always",
                "-g",
                "${workspaceFolder}/run_tests.cpp",
                "-o",
                "${workspaceFolder}/run_tests"
            ],
            "options": { "cwd": "${workspaceFolder}" },
            "problemMatcher": ["$gcc"],
            "group": { "kind": "build", "isDefault": true },
            "detail": "Builds run_tests with g++ (not gcc) so the C++ standard library links correctly."
        }
    ]
}
```

`.vscode/launch.json` (lets the candidate hit F5 to build-and-debug):
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug run_tests",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/run_tests",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "MIMode": "gdb",
            "preLaunchTask": "C/C++: g++ build active file"
        }
    ]
}
```

### Java

`.vscode/tasks.json`:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "javac: build and run tests",
            "type": "shell",
            "command": "javac Solution.java interviewer_only/ReferenceSolution.java RunTests.java && java RunTests",
            "options": { "cwd": "${workspaceFolder}" },
            "group": { "kind": "build", "isDefault": true },
            "problemMatcher": ["$javac"]
        }
    ]
}
```

### Go

`.vscode/tasks.json`:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "go run",
            "type": "shell",
            "command": "go run .",
            "options": { "cwd": "${workspaceFolder}" },
            "group": { "kind": "build", "isDefault": true },
            "problemMatcher": ["$go"]
        }
    ]
}
```
Sanity-check this still matches whatever module layout you actually used
for the Go bundle (see the caveat in `references/languages/go.md`) before
handing it over.

### Python / JavaScript / TypeScript

These don't need a build step, so there's no gcc/g++-style footgun to guard
against — a `tasks.json` is a nice-to-have for a one-key "run tests" binding
rather than something to insist on. If you write one, use a plain `shell`
task with the run command from the matching language doc
(`python3 run_tests.py`, `node run_tests.js`, or `ts-node run_tests.ts`) and
skip `launch.json` unless the candidate specifically wants to set
breakpoints.
