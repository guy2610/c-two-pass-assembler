# C Two-Pass Assembler

A systems-programming project in C implementing a classic two-pass assembler.

The project parses assembly source files, builds a symbol table, resolves symbol references across two passes, generates object, entry, and external-symbol files, and includes automated regression testing and AddressSanitizer validation.

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

## Project Evolution

This project was significantly refactored, debugged, tested, and documented to serve as a standalone portfolio project.

Major improvements include:

- Fixing memory-safety issues discovered with AddressSanitizer
- Correcting symbol-resolution and output-generation defects
- Adding regression tests for object, entry, and external-symbol outputs
- Adding automated build and test workflows through Makefiles
- Cleaning compiler warnings and improving code quality
- Reorganizing the repository structure and documentation

## Engineering Scope

The goal of this project is to demonstrate:

- Parsing and lexical processing
- Two-pass assembler design
- Symbol-table management
- Binary and hexadecimal encoding
- C memory management
- Debugging with AddressSanitizer
- Regression testing and build automation

The implementation prioritizes educational clarity and maintainability over production-grade assembler features.

## Current Status

The project currently:

- Builds successfully with strict compiler warnings enabled
- Passes golden-output regression tests for `.ob`, `.ent`, and `.ext`
- Passes AddressSanitizer validation

```bash
make test
make test-asan
```
