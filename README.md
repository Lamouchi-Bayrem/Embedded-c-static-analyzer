# Embedded C Static Analyzer v1

Responsive Qt 6 workbench for selecting C files, running compiler diagnostics, Cppcheck and Clang-Tidy asynchronously, reviewing normalized findings beside source code, and exporting JSON/HTML reports.

## Build

```bash
sudo apt install build-essential cmake ninja-build qt6-base-dev qt6-base-dev-tools clang gcc cppcheck clang-tidy
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/EmbeddedCStaticAnalyzer
```

## Current v1 scope

- Recursive `.c`/`.h` project scan with per-file selection
- Responsive asynchronous analyzer queue
- Cancellation and partial-result retention
- GCC/Clang strict diagnostics
- Cppcheck
- Clang-Tidy
- Finding deduplication and filtering
- Source navigation
- JSON and standalone HTML reports
- Missing-tool handling

## Important

This is a MISRA-oriented analysis workbench. It does not bundle proprietary MISRA rule text and does not claim formal compliance. Use rules and text supplied through your licensed analyzer, and maintain documented enforcement, review, and deviation processes.
