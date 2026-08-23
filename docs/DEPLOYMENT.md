# Deployment preparation

## Current local deployment

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel "$(nproc)"
./build/EmbeddedCStaticAnalyzer
```

## Before producing a public release

- Add a license
- Add automated build tests
- Record compiler and Qt versions
- Test on a clean Ubuntu installation
- Test missing-tool behavior
- Test paths containing spaces
- Test cancellation
- Test malformed and large analyzer output
- Add application icon and desktop file
- Add screenshots to the README
- Create a versioned release tag

## Recommended release artifacts

```text
EmbeddedCStaticAnalyzer-x86_64.AppImage
source.tar.gz
checksums.txt
release-manifest.json
```

## Future CI jobs

```text
Linux Debug build
Linux Release build
Formatting check
Cppcheck
Unit tests
Parser fixture tests
Example-project analysis
Package smoke test
```
