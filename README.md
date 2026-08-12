<!--no-pdf-->
# CMSC 124 Problem Set 1 Starter

Ten data types from Unit 5, built by hand in C17. The manual is the assignment.
This file is the repository's own notes.

## Layout

```
include/dt.h              the fixed public interface. Do not edit.
src/main.c                given, complete
src/driver.c              given, complete: the case-file front end
src/print.c               given, complete: the canonical printed forms
src/dt_*.c                yours, ten files
cases/                    the entire grading corpus
build.sh  run  check.sh   the course run contract
```

## What to Run

```bash
./build.sh          # one clean build into build/
./run <case-file>   # execute one case file
./check.sh          # build, then the whole published corpus, then sanitizers
```

`check.sh` is the whole grade. There is no second script.

## Exit Codes

The course contract, the same one the laboratory interpreter uses.

| Code | Meaning |
|---|---|
| 0 | every command parsed and ran, and no reference was left unreleased |
| 65 | the case file was rejected before anything ran |
| 70 | a command ran and faulted |

## Reading a First Run

A fresh clone builds without warnings and then fails 30 of the 60 checks.

Look at the 30 that pass before you take any encouragement from them. Most are
cases that expect a refusal, which a stub that refuses everything satisfies by
accident. `boundary/array_index_above_upper` wants exit 70, and `dt_array_get`
returning `DT_ERR_RANGE` unconditionally is exit 70. Nothing has been built. So
do not read 30/60 as halfway. Every one of the ten `normal/` cases fails. Those
are the ones that need working code.

The Actions badge on this repository is red for the same reason. It stays red
until somebody implements the ten modules, which is the correct state for a
starter. Yours goes green when you finish.

## Tested Toolchains

Every row below is a run that happened.

| Environment | Versions | Result |
|---|---|---|
| MSYS2 UCRT64 (Windows 11) | GCC 16.2.0, CMake 4.4.2, Ninja 1.13.2, Python 3.14.7 | builds warning-free; 60/60 with a complete implementation; sanitizers skipped, see below |
| Ubuntu 24.04 under WSL 2 | GCC 13.3.0, Python 3.12.3 | 60/60 with a complete implementation, including under AddressSanitizer and UndefinedBehaviorSanitizer |
| GitHub Actions, `ubuntu-latest` | the workflow in `.github/workflows/test.yml` | builds, fetches the harness, runs the corpus, and runs it again sanitized; 30/60 on the stubs, matching both machines above |

The Ubuntu figure comes from compiling `src/*.c` directly with `gcc`, because
that machine had no CMake installed. The CMake path runs on Windows and in
Actions. macOS was never run here. Its setup steps come from the Laboratory
Activity 0 manual, where they are the same commands.

## The Sanitizer Leg

`check.sh` probes once for whether your compiler can link
`-fsanitize=address,undefined`, and runs the corpus a second time under those
sanitizers when it can.

MinGW GCC ships neither `libasan` nor `libubsan`, so on MSYS2 the link fails
with `cannot find -lasan` and the leg is skipped by name. This is a property of
the toolchain, confirmed on UCRT64 GCC 16.2.0 and on mingw32 GCC 16.1.0, and
not something your code can change. It does run in the GitHub Actions workflow,
confirmed on `ubuntu-latest`. That workflow is where the graded verdict comes
from, so push your work and read the Actions tab if you want the sanitized
answer on Windows.

The leg earns its place. Writing this starter, AddressSanitizer caught a leak
in `driver.c` that all 60 correctness checks passed straight through: a
malformed quoted string made `scan_line` abandon the tokens it had already
allocated for that line. Nothing about the output was wrong. The bug was
invisible to a comparison of stdout, which is the category of mistake the
sanitizer exists for.
