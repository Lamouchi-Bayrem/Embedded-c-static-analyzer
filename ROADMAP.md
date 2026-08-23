# Roadmap

## v1.0 — Analysis workbench foundation

- [x] Qt 6 desktop application
- [x] Recursive C/header discovery
- [x] Per-file translation-unit selection
- [x] Asynchronous analyzer execution
- [x] Cancellation and partial results
- [x] GCC/Clang diagnostics
- [x] Cppcheck adapter
- [x] Clang-Tidy adapter
- [x] Finding normalization
- [x] Basic deduplication
- [x] Source navigation
- [x] JSON and HTML reports

## v1.1 — Precision and reliability

- [ ] Capture all process output before parsing
- [ ] Unit tests for GCC, Clang, Cppcheck, and Clang-Tidy parsers
- [ ] Per-job timeout
- [ ] Per-file state: pending, running, passed, failed, incomplete
- [ ] Better diagnostic multiline handling
- [ ] Tool-version discovery
- [ ] Analysis manifest with commands and environment
- [ ] Configurable include directories
- [ ] Configurable preprocessor definitions
- [ ] User-selectable compiler
- [ ] Persisted project settings

## v1.2 — Real build context

- [ ] Import `compile_commands.json`
- [ ] CMake project detection
- [ ] Translation-unit-specific compiler arguments
- [ ] Target triple and data-model configuration
- [ ] Custom system-header paths
- [ ] Exclusion patterns
- [ ] Generated-code classification

## v1.3 — Engineering workflow

- [ ] Save/load analysis sessions
- [ ] Baseline JSON
- [ ] New, existing, changed, and resolved findings
- [ ] Suppression manager with rationale
- [ ] Deviation manager with approval state
- [ ] Finding comments and ownership
- [ ] CSV and Markdown reports
- [ ] SARIF 2.1.0 export
- [ ] Git commit and working-tree metadata

## v1.4 — Performance and scale

- [ ] Bounded parallel worker pool
- [ ] Incremental analysis of changed files
- [ ] Result cache keyed by file hash and command hash
- [ ] Large-project progress model
- [ ] Project cancellation with process-group termination
- [ ] Memory and output-size limits
- [ ] Symlink-loop protection

## v2.0 — Native Clang AST engine

Introduce a separate process named `eca-clang-engine` using Clang LibTooling.

Initial custom checks:

- [ ] Assignment in conditions
- [ ] Implicit narrowing conversions
- [ ] Mixed signed/unsigned expressions
- [ ] Dangerous shifts
- [ ] Integer/pointer conversions
- [ ] Discarded qualifiers
- [ ] Variable-length arrays
- [ ] Dynamic allocation
- [ ] Recursion
- [ ] Missing prototypes
- [ ] Writable file-scope objects
- [ ] Floating-point equality
- [ ] Missing switch default
- [ ] Unannotated fall-through
- [ ] Complex-expression side effects

The engine should emit versioned JSON Lines and remain isolated from the Qt process.

## v2.1 — Rule coverage and profiles

- [ ] Public coverage matrix
- [ ] MISRA-oriented project profile
- [ ] CERT C-oriented profile
- [ ] ST-inspired embedded-quality profile
- [ ] Project-specific rule configuration
- [ ] Manual-review checklist for non-automatable guidelines

## v2.2 — Deployment and CI

- [ ] Headless CLI mode
- [ ] SARIF upload workflow
- [ ] GitHub Actions example
- [ ] AppImage packaging
- [ ] Debian package
- [ ] Signed release artifacts
- [ ] Reproducible release manifest

## Success criteria

The project is ready to scale when:

1. Parser behavior is covered by automated tests.
2. Project compilation context is loaded from a compilation database.
3. Analyzer crashes and timeouts cannot freeze the GUI.
4. Reports record all commands, versions, inputs, and exclusions.
5. Baseline comparison is stable across machines.
6. The native AST engine has a documented coverage matrix.
