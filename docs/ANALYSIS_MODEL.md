# Analysis model

## Finding fields

Every normalized finding should contain:

- Stable internal identifier
- Engine
- Engine version
- Rule/check identifier
- Severity
- File
- Line
- Column
- Message
- Evidence
- Status
- Fingerprint

## Finding status

Planned statuses:

```text
Open
Fixed
False positive
Suppressed
Deviation proposed
Deviation approved
Deferred
```

## Deduplication

V1 uses a basic fingerprint. Future versions should normalize paths and messages and combine findings reported by several engines at the same AST entity.

## Analysis completeness

A finished run must distinguish:

```text
Passed
Completed with findings
Compilation failed
Analyzer failed
Timed out
Cancelled
Incomplete
```

A failed translation unit must not invalidate successful results from other files.

## Compliance boundary

Automated findings are engineering evidence. Compliance claims require additional process, review, deviation, tool, compiler, external-component, and target-level evidence.
