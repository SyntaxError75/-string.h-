CC = gcc -Wall -Wextra -Werror -std=c11

.PHONY: all clean test s21_string.a rebuild

all: s21_string.a

s21_string.o: s21_sprintf.c s21_string.h
	$(CC) -c s21_sprintf.c -o s21_string.o -lm

s21_string.a: s21_string.o
	ar rcs s21_string.a s21_string.o

test: s21_string.a test_sprintf.c s21_string.h
	$(CC) test_sprintf.c s21_string.a -o test -lm
	./test

clean:
	rm -f s21_string.a s21_string.o test

rebuild: clean all

