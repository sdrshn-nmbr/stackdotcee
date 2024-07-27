# VARIABLES
#
# ASSIGNMENT INFO, etc.
ASG_NICKNAME = HW02
BASE_NAME = stack

# EXECUTABLES
EXECUTABLE = test_$(BASE_NAME)
EXECUTABLE_GCOV = $(EXECUTABLE)_gcov

# SOURCE FILES
SRC_C = $(BASE_NAME).c
TEST_C = $(EXECUTABLE).c
SRC_H = $(BASE_NAME).h clog.h miniunit.h
SUBMIT_FILES = $(TEST_C) $(SRC_C) $(SRC_H) Makefile

# SYSTEM
SHELL = /bin/bash
CC = gcc
CFLAGS = -g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV = $(CFLAGS) -fprofile-arcs -ftest-coverage


# RULES
#
$(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) $(SRC_C) $(TEST_C) stack_utils.c -o $(EXECUTABLE) $(CFLAGS)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

valgrind: $(EXECUTABLE)
	valgrind $(EXECUTABLE)

submit: $(SUBMIT_FILES)
	368submit $(ASG_NICKNAME) $(SUBMIT_FILES)

pretest: submit
	368test $(ASG_NICKNAME)

coverage: $(SRC_C) $(TEST_C)
	 $(CC) $(SRC_C) $(TEST_C) -o $(EXECUTABLE_GCOV) $(CFLAGS_GCOV)
	 ./$(EXECUTABLE_GCOV)
	 gcov -f $(SRC_C)

clean:
	rm -f $(EXECUTABLE) $(EXECUTABLE_GCOV) *.gc*

restore:
	368get $(ASG_NICKNAME) -r

list:
	368get $(ASG_NICKNAME) -l

get:
	368get $(ASG_NICKNAME)

help:
	@echo ------------------------------------------------------------
	@echo "Usage: make [target]"
	@echo "Targets:"
	@echo "            : Build the executable (default target)"
	@echo "  test      : Run tests using the executable"
	@echo "  valgrind  : Run tests using valgrind for memory checking"
	@echo "  submit    : Submit necessary files for assignment"
	@echo "  pretest   : Submit and run pretest"
	@echo "  coverage  : Generate code coverage report"
	@echo "  clean     : Remove generated files"
	@echo "  restore   : Restore most recent submission"
	@echo "  list      : List files in submission"
	@echo "  get       : Get submission files"
	@echo ------------------------------------------------------------

.PHONY: all test valgrind submit pretest coverage clean restore list get help
