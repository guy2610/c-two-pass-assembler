CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -pedantic
ASANFLAGS := -std=c99 -g -fsanitize=address -fno-omit-frame-pointer

SOURCES := assemblerMain.c FirstPass.c SecondPass.c data.c label.c util.c
TARGET := assembler
ASAN_TARGET := assembler_asan

TEST_INPUT := tests/inputs/progInput
EXPECTED_OB := tests/expected/progInput.ob
GENERATED_OB := tests/inputs/progInput.ob
EXPECTED_ENT := tests/expected/progInput.ent
GENERATED_ENT := tests/inputs/progInput.ent
EXPECTED_EXT := tests/expected/progInput.ext
GENERATED_EXT := tests/inputs/progInput.ext

.PHONY: all asan test test-asan clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

asan: $(SOURCES)
	$(CC) $(ASANFLAGS) $(SOURCES) -o $(ASAN_TARGET)

test: $(TARGET)
	./$(TARGET) $(TEST_INPUT)
	@echo
	diff -u $(EXPECTED_OB) $(GENERATED_OB)
	diff -u $(EXPECTED_ENT) $(GENERATED_ENT)
	diff -u $(EXPECTED_EXT) $(GENERATED_EXT)

test-asan: asan
	./$(ASAN_TARGET) $(TEST_INPUT)
	@echo
	diff -u $(EXPECTED_OB) $(GENERATED_OB)
	diff -u $(EXPECTED_ENT) $(GENERATED_ENT)
	diff -u $(EXPECTED_EXT) $(GENERATED_EXT)

clean:
	rm -f $(TARGET) $(ASAN_TARGET)
	rm -f tests/inputs/*.ob tests/inputs/*.ent tests/inputs/*.ext
