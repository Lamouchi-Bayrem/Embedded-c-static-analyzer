# Dependencies

## Required to build the GUI

- Linux development environment
- CMake 3.16 or newer
- C++17 compiler
- Qt 6 Widgets
- Qt 6 Concurrent
- Make or Ninja

Ubuntu installation:

```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    ninja-build \
    qt6-base-dev \
    qt6-base-dev-tools
```

## Analysis engines

At least one C compiler is needed for compiler diagnostics:

```bash
sudo apt install -y gcc clang
```

Recommended static-analysis tools:

```bash
sudo apt install -y cppcheck clang-tidy
```

Recommended development tool:

```bash
sudo apt install -y clang-format
```

## Runtime behavior when tools are missing

- If Clang is available, the application prefers it for compiler diagnostics.
- If Clang is unavailable but GCC exists, GCC is used.
- If neither compiler is available, compiler analysis is skipped and reported.
- Cppcheck is optional and is skipped when unavailable.
- Clang-Tidy is optional and is skipped when unavailable.

Missing optional tools must not crash the GUI.

## Verify installation

```bash
cmake --version
ninja --version
clang --version
gcc --version
cppcheck --version
clang-tidy --version
```

## Build

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel "$(nproc)"
```

## Notes

This is a C++/Qt project. It does not require Python and therefore does not use `requirements.txt`.

Future native Clang LibTooling work will require LLVM and Clang development packages. Those dependencies should be added only when the native engine is introduced, to keep v1 installation lightweight.
