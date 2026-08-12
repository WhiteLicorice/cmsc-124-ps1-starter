#!/usr/bin/env bash
# check.sh -- the whole grade, run the same way by you, by CI, and by me.
#
# There is no second script with extra tests in it. What this runs is what
# cases/ contains, and cases/ is in the repository you were handed.
set -u

HARNESS_TAG="v1.1"
HARNESS_URL="https://raw.githubusercontent.com/WhiteLicorice/cmsc-124-harness/${HARNESS_TAG}/run_tests.py"

failures=0

banner() {
  printf '\n== %s ==\n' "$1"
}

banner "build"
if ! ./build.sh; then
  echo "check.sh: the build failed, so nothing else can run." >&2
  exit 1
fi

if command -v python3 >/dev/null 2>&1; then
  PYTHON=python3
else
  PYTHON=python
fi

if [[ ! -f run_tests.py ]]; then
  banner "fetching harness ${HARNESS_TAG}"
  if ! curl -sSL "$HARNESS_URL" -o run_tests.py; then
    echo "check.sh: could not fetch the harness. Check your network." >&2
    exit 1
  fi
fi

banner "correctness"
if ! "$PYTHON" run_tests.py cases; then
  failures=1
fi

banner "sanitizers"
# AddressSanitizer and UndefinedBehaviorSanitizer catch the memory faults the
# correctness run cannot see: a read past the end of an array that happens to
# land inside the allocation, a use of freed memory that happens to still hold
# the old bytes. Both are real failures that pass a stdout comparison.
#
# MinGW GCC does not ship libasan or libubsan, so on MSYS2 this leg cannot run
# at all. That is a property of the toolchain, not of your code. It runs on
# Linux, on macOS, and in the GitHub Actions workflow, which is where the
# graded verdict comes from.
probe_cc="${CC:-cc}"
if ! command -v "$probe_cc" >/dev/null 2>&1; then
  probe_cc="gcc"
fi

probe_dir="$(mktemp -d)"
printf 'int main(void){return 0;}\n' > "$probe_dir/probe.c"

if command -v "$probe_cc" >/dev/null 2>&1 &&
   "$probe_cc" -fsanitize=address,undefined -o "$probe_dir/probe" "$probe_dir/probe.c" >/dev/null 2>&1; then
  rm -rf "$probe_dir"

  if ! cmake -S . -B build-san -G Ninja -DCMAKE_BUILD_TYPE=Debug -DDT_SANITIZE=ON >/dev/null; then
    echo "check.sh: sanitized configure failed." >&2
    failures=1
  elif ! cmake --build build-san >/dev/null; then
    echo "check.sh: sanitized build failed." >&2
    failures=1
  else
    # A sanitizer abort is a non-zero exit the harness reports as a failed
    # test, so a leak or an overflow shows up by name rather than as a note
    # nobody reads.
    export ASAN_OPTIONS="detect_leaks=1:abort_on_error=0"
    export UBSAN_OPTIONS="print_stacktrace=1:halt_on_error=1"
    if ! DT_BUILD_DIR=./build-san "$PYTHON" run_tests.py cases; then
      failures=1
    fi
  fi
else
  rm -rf "$probe_dir"
  echo "SKIP: $probe_cc cannot link -fsanitize=address,undefined here."
  echo "SKIP: this is expected on MSYS2 and MinGW, which ship no libasan."
  echo "SKIP: the sanitized run happens on Linux, on macOS, and in CI."
fi

banner "result"
if [[ "$failures" -eq 0 ]]; then
  echo "All published checks passed."
else
  echo "Some published checks failed. Scroll up for the first one." >&2
fi
exit "$failures"
