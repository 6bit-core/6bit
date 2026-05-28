# Fuzzing Sixbit Core

## libFuzzer Quickstart

```bash
git clone https://github.com/sixbit-core/sixbit
cd sixbit

cmake --preset=libfuzzer
cmake --build build_fuzz

FUZZ=process_message build_fuzz/bin/fuzz
```

## Overview

Fuzzing tests software by feeding randomized inputs to uncover crashes,
undefined behavior, and edge-case bugs.

- `NEW` indicates new code coverage
- Corpus stores useful test cases

## Using a Corpus

```bash
mkdir corpus/
FUZZ=process_message build_fuzz/bin/fuzz corpus/
```

## Passing Arguments

```bash
FUZZ=address_deserialize build_fuzz/bin/fuzz \
  -runs=1 corpus/ --checkaddrman=5 --printtoconsole=1
```

## Seed Corpora

```bash
git clone --depth=1 https://github.com/sixbit-core/qa-assets

FUZZ=process_message build_fuzz/bin/fuzz \
  qa-assets/fuzz_corpora/process_message/
```

## Sanitizers vs Throughput

- Use sanitizers for bug detection
- Disable for faster, deeper fuzzing runs

## Build Modes

### Full Fuzz Mode
`-DBUILD_FOR_FUZZING=ON`

### Debug Mode
`-DBUILD_FUZZ_BINARY=ON -DCMAKE_BUILD_TYPE=Debug`

### Release Mode
`-DBUILD_FUZZ_BINARY=ON -DCMAKE_BUILD_TYPE=Release`

## afl++

```bash
git clone https://github.com/AFLplusplus/AFLplusplus
make -C AFLplusplus/ source-only
```

## Honggfuzz

```bash
git clone https://github.com/google/honggfuzz
make -C honggfuzz
```

## Notes

- Long fuzz runs improve results
- Submit new corpus inputs to improve coverage
