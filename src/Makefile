CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic -I.
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
TEST_FLAGS = -lcheck -lm -lpthread -lsubunit 

SRC_FILES = MY_string.c  MY_sprintf.c
OBJ_FILES = $(SRC_FILES:.c=.o)

LIBRARY = MY_string.a
GCOV_LIBRARY = MY_string_gcov.a

FORMAT_FILES = *.c *.h tests/*.c

TEST_STRING_APP = test_string_app
TEST_SSCANF_APP = test_sscanf_app
TEST_SPRINTF_APP = test_sprintf_app
GCOV_STRING_APP = test_string_gcov
GCOV_SSCANF_APP = test_sscanf_gcov
GCOV_SPRINTF_APP = test_sprintf_gcov

all: $(LIBRARY)

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(LIBRARY): $(OBJ_FILES)
	ar rcs $@ $^

test_string: $(LIBRARY)
	$(CC) $(CFLAGS) tests/test_string.c $(LIBRARY) $(TEST_FLAGS) -o $(TEST_STRING_APP)
	 ./$(TEST_STRING_APP)
test_sscanf: $(LIBRARY)
	$(CC) $(CFLAGS) tests/test_sscanf.c $(LIBRARY) $(TEST_FLAGS) -o $(TEST_SSCANF_APP)
	 ./$(TEST_SSCANF_APP)
test_sprintf: $(LIBRARY)
	$(CC) $(CFLAGS) tests/test_sprintf.c $(LIBRARY) $(TEST_FLAGS) -o $(TEST_SPRINTF_APP)
	 ./$(TEST_SPRINTF_APP)

test: test_string test_sprintf test_sscanf 

$(GCOV_LIBRARY): $(SRC_FILES)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $^
	ar rcs $@ *.o

test_gcov_string: $(GCOV_LIBRARY)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) tests/test_string.c $(GCOV_LIBRARY) $(TEST_FLAGS) -o $(GCOV_STRING_APP)
	./$(GCOV_STRING_APP)

test_gcov_sprintf: $(GCOV_LIBRARY)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) tests/test_sprintf.c $(GCOV_LIBRARY) $(TEST_FLAGS) -o $(GCOV_SPRINTF_APP)
	./$(GCOV_SPRINTF_APP)

test_gcov_sscanf: $(GCOV_LIBRARY)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) tests/test_sscanf.c $(GCOV_LIBRARY) $(TEST_FLAGS) -o $(GCOV_SSCANF_APP)
	./$(GCOV_SSCANF_APP)

test_gcov_all: test_gcov_string test_gcov_sprintf test_gcov_sscanf

gcov_report: test_gcov_all
	gcov -b -c $(SRC_FILES)
	
	mkdir -p report
	
	lcov -c -d . -o coverage.info --rc lcov_branch_coverage=1
	lcov --remove coverage.info '/usr/*' 'tests/*' -o filtered.info --ignore-errors unused
	genhtml -o report --rc genhtml_branch_coverage=1 filtered.info

style:
	clang-format -i $(FORMAT_FILES)

check_style:
	clang-format -n $(FORMAT_FILES)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --force --std=c11 -I. $(FORMAT_FILES)

valgrind: test
	@echo "--- Checking Memory: String ---"
	valgrind --tool=memcheck --leak-check=full ./test_string_app  2>&1 | grep -E "lost:|ERROR SUMMARY" || true
	@echo "--- Checking Memory: Sscanf ---"
	valgrind --tool=memcheck --leak-check=full ./test_sscanf_app 2>&1 | grep -E "lost:|ERROR SUMMARY" || true
	@echo "--- Checking Memory: Sprintf ---"
	valgrind --tool=memcheck --leak-check=full ./test_sprintf_app 2>&1 | grep -E "lost:|ERROR SUMMARY" || true



clean:
	rm -f $(OBJ_FILES) $(LIBRARY) $(GCOV_LIBRARY)
	rm -f $(TEST_STRING_APP) $(TEST_SSCANF_APP) $(TEST_SPRINTF_APP)  
	rm -f $(GCOV_STRING_APP) $(GCOV_SSCANF_APP) $(GCOV_SPRINTF_APP)
	rm -f *.gcda *.gcno *.gcov 
	rm -f coverage.info filtered.info
	rm -rf report
	rm -f *.o 

.PHONY: all clean test test_gcov_all gcov_report \
		test_string test_sprintf test_sscanf \
		test_gcov_string test_gcov_sprintf test_gcov_sscanf \
		style check_style cppcheck valgrind


		 
