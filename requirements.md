# v1 requirements

- Qt GUI must remain responsive during analysis.
- Analyzer processes must run outside the GUI event loop.
- A failed analyzer must not erase other results.
- Users must select individual translation units.
- Findings require engine, rule, severity, source location, message and status.
- Reports must be reproducible JSON and viewable HTML.
- Missing tools must be reported without crashing.
- Analysis must be cancellable.
