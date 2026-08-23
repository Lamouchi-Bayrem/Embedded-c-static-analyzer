<div align="center">

# Embedded C Static Analyzer

### Responsive Qt 6 workbench for compiler diagnostics, static analysis, source review, and reproducible embedded-C quality reports

[![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-6-41CD52?logo=qt&logoColor=white)](https://www.qt.io/)
[![C](https://img.shields.io/badge/Analyzed_C-C11%20%7C%20C17-A8B9CC?logo=c)](https://www.iso.org/standard/74528.html)
[![CMake](https://img.shields.io/badge/CMake-3.16%2B-064F8C?logo=cmake)](https://cmake.org/)
[![Status](https://img.shields.io/badge/Status-v1%20MVP-orange)](#roadmap)

</div>

---

## Overview

**Embedded C Static Analyzer** is a desktop analysis workbench for embedded-C projects. It allows developers to select translation units, run multiple analysis engines asynchronously, review normalized findings beside the source code, and export reproducible JSON and HTML reports.

The v1 application combines:

- GCC or Clang compiler diagnostics
- Cppcheck quality checks
- Clang-Tidy and Clang Static Analyzer checks
- Responsive background execution with cancellation
- Finding normalization and deduplication
- Source navigation
- JSON and standalone HTML reports

The long-term goal is a scalable embedded-software quality platform with a native Clang AST engine, project baselines, deviation management, SARIF export, CI integration, and target-specific profiles.

> The application is **MISRA-oriented**. It does not bundle proprietary MISRA guideline text and does not claim automatic or formal MISRA compliance.

## Why this project exists

Embedded-C analysis depends on more than searching source text. Accurate results require the correct language standard, include paths, preprocessor definitions, compiler assumptions, and translation-unit context.

This project provides one interface for:

1. Selecting the code to analyze.
2. Detecting available analysis tools.
3. Executing tools without blocking the GUI.
4. Converting different tool outputs into one finding model.
5. Reviewing issues with source context.
6. Exporting evidence for engineering review.

## Current v1 features

### Project and file handling

- Open a C project directory
- Recursively discover `.c` and `.h` files
- Exclude build-directory contents
- Select individual C translation units
- Detect common include directories
- Display source files in a project tree

### Analysis engines

- GCC or Clang strict compiler diagnostics
- Cppcheck warning, style, performance, and portability checks
- Clang-Tidy checks from:
  - `clang-analyzer-*`
  - `bugprone-*`
  - `cert-*`
  - `performance-*`
  - `portability-*`

### Responsive execution

- Non-blocking analyzer execution through `QProcess`
- Sequential job queue
- Progress reporting
- Cancellation support
- Partial-result retention
- Missing-tool handling
- Analyzer failure isolation

### Results and reports

- Common finding model
- Finding deduplication
- Severity and text filters
- File, line, and column display
- Integrated source viewer
- Jump to the affected line
- Detailed finding view
- JSON report export
- Standalone HTML report export

## Architecture

```text
Qt 6 desktop GUI
├── Project scanner
├── File selection
├── Findings dashboard
├── Source viewer
└── Report exporter
        │
        ▼
AnalysisController
├── Asynchronous QProcess queue
├── Cancellation
├── Progress events
├── Tool failure isolation
└── Output parsing
        │
        ▼
Analysis engines
├── GCC / Clang diagnostics
├── Cppcheck
└── Clang-Tidy
        │
        ▼
Normalized Finding
├── Severity
├── Engine
├── Rule/check ID
├── File, line, and column
├── Message
├── Status
└── Fingerprint
```

## Repository structure

```text
embedded-c-static-analyzer/
├── CMakeLists.txt
├── README.md
├── DEPENDENCIES.md
├── ROADMAP.md
├── CONTRIBUTING.md
├── include/
│   ├── analysiscontroller.h
│   ├── finding.h
│   └── mainwindow.h
├── src/
│   ├── analysiscontroller.cpp
│   ├── main.cpp
│   └── mainwindow.cpp
├── examples/
│   ├── clean/
│   │   └── main.c
│   └── issues/
│       └── issues.c
└── docs/
    ├── ANALYSIS_MODEL.md
    └── DEPLOYMENT.md
```

## Quick start

### 1. Install dependencies

```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    ninja-build \
    qt6-base-dev \
    qt6-base-dev-tools \
    gcc \
    clang \
    cppcheck \
    clang-tidy \
    clang-format
```

### 2. Clone

```bash
git clone https://github.com/Lamouchi-Bayrem/embedded-c-static-analyzer.git
cd embedded-c-static-analyzer
```

If the repository has not yet been renamed, use its current GitHub URL and update the local remote after renaming.

### 3. Configure and build

```bash
cmake \
    -S . \
    -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build build --parallel "$(nproc)"
```

### 4. Run

```bash
./build/EmbeddedCStaticAnalyzer
```

## Development build

```bash
rm -rf build

cmake \
    -S . \
    -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build build --parallel "$(nproc)"
```

## Usage

1. Start the application.
2. Click **Open project...**.
3. Select a directory containing embedded C code.
4. Check the `.c` files that should be analyzed.
5. Select C11 or C17.
6. Enable the installed engines.
7. Click **Run analysis**.
8. Filter and review findings.
9. Double-click a finding to open its source location.
10. Export JSON and HTML reports.

## Included examples

### Clean example

Open:

```text
examples/clean
```

This example is intended to compile cleanly with strict warnings.

### Intentionally problematic example

Open:

```text
examples/issues
```

It includes examples of problematic constructs so the analyzer workflow can be demonstrated.

## Compiler diagnostics

The compiler engine enables warnings such as:

```text
-Wall
-Wextra
-Wpedantic
-Wconversion
-Wsign-conversion
-Wshadow
-Wundef
-Wformat=2
-Wcast-align
-Wcast-qual
-Wstrict-prototypes
-Wmissing-prototypes
-Wswitch-enum
-Wdouble-promotion
```

Warnings are recorded as findings. They are not automatically converted to fatal errors during interactive analysis.

## Report outputs

The v1 application creates:

```text
analysis-report.json
analysis-report.html
```

The JSON report is intended for automation and future baseline comparison. The HTML report is intended for technical review and sharing.

Example finding model:

```json
{
  "severity": "Warning",
  "engine": "Compiler",
  "rule": "COMPILER",
  "file": "Core/Src/gpio.c",
  "line": 42,
  "column": 12,
  "message": "conversion may change value",
  "status": "Open"
}
```

## MISRA-oriented scope

The application can support a MISRA workflow by:

- Running analyzers configured for the project
- Preserving rule/check identifiers
- Recording source locations
- Exporting reproducible findings
- Preparing for suppression and deviation management
- Avoiding copied proprietary rule text

Formal compliance also requires an agreed guideline baseline, documented enforcement methods, review, deviations, tool qualification considerations, compiler assumptions, external-component treatment, and target evidence.

## Known v1 limitations

- No native Clang AST rules yet
- No `compile_commands.json` import yet
- Include directories are detected only from common project paths
- No preprocessor-definition editor
- No analyzer timeout yet
- No per-file concurrent execution
- No baseline comparison
- No suppression or deviation manager
- No SARIF export
- No structured analyzer-version manifest
- Finding parsing currently relies on common diagnostic formats
- No automated source modification

These limitations define the next development milestones rather than hidden capabilities.

## Roadmap

See [ROADMAP.md](ROADMAP.md) for the detailed plan.

The immediate priorities are:

1. Reliable diagnostic capture and parser tests
2. `compile_commands.json` import
3. Include-path and macro configuration
4. Analyzer timeouts and per-file status
5. Baseline comparison
6. Suppression and deviation management
7. SARIF export
8. Native Clang LibTooling engine

## Quality checks for contributors

Format the code:

```bash
clang-format -i src/*.cpp include/*.h
```

Run Cppcheck:

```bash
cppcheck \
    --std=c++17 \
    --enable=warning,style,performance,portability \
    --suppress=missingIncludeSystem \
    -Iinclude \
    src include
```

Build with a fresh directory:

```bash
rm -rf build
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel "$(nproc)"
```

## Security and robustness

- Never execute analyzed source files automatically.
- Treat project paths and analyzer output as untrusted input.
- Keep analyzer processes isolated from the GUI.
- Apply timeouts before accepting untrusted large projects in future releases.
- Do not include access tokens, credentials, proprietary standards, or licensed analyzer files in the repository.

## Contributing

Read [CONTRIBUTING.md](CONTRIBUTING.md) before submitting changes.

Useful contribution areas include:

- Diagnostic parser tests
- Additional analyzer adapters
- Report improvements
- CMake compilation-database support
- Source-viewer improvements
- Baseline and deviation workflows
- Native Clang AST checks

## Author

**Bayrem Lamouchi**

- GitHub: [@Lamouchi-Bayrem](https://github.com/Lamouchi-Bayrem)

## License

Add a `LICENSE` file before public distribution. Do not add a license badge until the repository contains the matching license text.

---

<div align="center">

**Built to make embedded-C analysis clearer, reproducible, and scalable.**

</div>
