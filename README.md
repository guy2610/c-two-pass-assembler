# C Two-Pass Assembler

A C implementation of a two-pass assembler for an assembly-like language, originally developed as part of the Open University Systems Programming Lab.

The project parses source assembly files, builds a symbol table, encodes instructions and data into machine-word representations, and generates assembler output files such as object, entry, and external symbol files.

## Overview

The assembler follows a classic two-pass architecture:

1. **First Pass**
   - Parses labels, directives, instructions, and operands.
   - Builds the symbol table.
   - Calculates instruction and data counters.
   - Encodes preliminary instruction and data words.

2. **Second Pass**
   - Resolves symbol references.
   - Handles `.entry` declarations.
   - Finalizes encoded output.
   - Produces assembler output files.

The project is written in C and focuses on low-level parsing, symbol management, memory handling, and binary/hex encoding.

## Features

- Two-pass assembler flow
- Label and symbol table handling
- Support for code and data sections
- Support for directives such as:
  - `.data`
  - `.string`
  - `.entry`
  - `.extern`
- Object file generation
- Entry and external symbol output generation
- Golden-output regression test using `diff`
- AddressSanitizer test target for memory-safety validation

## Repository Structure

```text
.
├── assemblerMain.c
├── FirstPass.c / FirstPass.h
├── SecondPass.c / ScondPass.h
├── data.c / data.h
├── label.c / label.h
├── util.c / util.h
├── Header.h
├── Makefile
└── tests
    ├── inputs
    │   └── progInput.as
    └── expected
        └── progInput.ob
```

## Build

```bash
make
```

This builds the assembler executable:

```bash
./assembler
```

## Run

The assembler expects the input path without the `.as` extension.

Example:

```bash
./assembler tests/inputs/progInput
```

This reads:

```text
tests/inputs/progInput.as
```

and generates output files next to the input file:

```text
tests/inputs/progInput.ob
tests/inputs/progInput.ent
tests/inputs/progInput.ext
```

## Test

Run the golden-output regression test:

```bash
make test
```

The test builds the assembler, runs it on the sample input, and compares the generated object, entry, and external-symbol files against the expected outputs:

```bash
diff -u tests/expected/progInput.ob tests/inputs/progInput.ob
diff -u tests/expected/progInput.ent tests/inputs/progInput.ent
diff -u tests/expected/progInput.ext tests/inputs/progInput.ext
```

## AddressSanitizer Test

Build and run with AddressSanitizer:

```bash
make test-asan
```

This target helps detect memory-safety issues such as buffer overflows and invalid memory access while still validating the generated object output.

## Clean

```bash
make clean
```

This removes local binaries and generated assembler output files.

## Notes

This repository is based on an academic assembler project and was later cleaned up as a portfolio project.

The cleanup included:

- Fixing memory-safety issues found with AddressSanitizer
- Fixing output mismatches against a golden expected object file
- Organizing sample input and expected output files
- Adding a Makefile
- Adding regression-test targets for object, entry, and external-symbol outputs
- Removing compiler warnings under `-Wall -Wextra -pedantic`

## Limitations

This is an academic assembler implementation and not a production-grade assembler. The focus is on demonstrating parsing, two-pass symbol resolution, output generation, C memory management, and regression testing.

## Current Status

The project currently builds successfully with:

```bash
make test
```

and passes the golden object-output comparison.

It also passes the AddressSanitizer test target:

```bash
make test-asan
```
