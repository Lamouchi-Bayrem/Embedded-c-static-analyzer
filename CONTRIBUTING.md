# Contributing

## Development workflow

1. Open an issue describing the problem or feature.
2. Create a focused branch.
3. Keep GUI, controller, parser, and report changes separated where practical.
4. Add tests for parser or analysis behavior.
5. Format and build before opening a pull request.

## Branch naming

```text
feature/compile-database
feature/sarif-export
fix/cppcheck-parser
refactor/job-runner
```

## Commit examples

```text
Add compile database loader
Fix multiline Clang diagnostic parsing
Add analyzer timeout and cancellation test
```

## Local checks

```bash
clang-format -i src/*.cpp include/*.h

cppcheck \
    --std=c++17 \
    --enable=warning,style,performance,portability \
    --suppress=missingIncludeSystem \
    -Iinclude \
    src include

rm -rf build
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel "$(nproc)"
```

## Pull-request expectations

A pull request should include:

- Problem statement
- Technical approach
- User-visible behavior
- Tests performed
- Screenshots for GUI changes
- Limitations or follow-up work

## Coding guidance

- Prefer explicit ownership and lifetimes.
- Keep analyzer execution out of the GUI thread.
- Do not parse source code with regular expressions when semantic compiler information is required.
- Preserve raw analyzer output for debugging.
- Treat paths and analyzer text as untrusted data.
- Do not automatically rewrite analyzed safety-related code.
- Do not copy proprietary coding-standard text into the repository.
