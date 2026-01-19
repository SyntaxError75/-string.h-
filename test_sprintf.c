#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "s21_string.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

static int tests_passed = 0;
static int tests_failed = 0;
float inf = INFINITY;

void compare_results(const char *s21_buf, const char *std_buf, int s21_ret,
                     int std_ret, const char *test_name) {
  if (strcmp(s21_buf, std_buf) == 0 && s21_ret == std_ret) {
    printf(GREEN "✓ PASS" RESET ": %s\n", test_name);
    tests_passed++;
  } else {
    printf(RED "✗ FAIL" RESET ": %s\n", test_name);
    printf("  Expected: \"%s\" (ret=%d)\n", std_buf, std_ret);
    printf("  Got:      \"%s\" (ret=%d)\n", s21_buf, s21_ret);
    tests_failed++;
  }
}

void test_char(void) {
  printf("\n" YELLOW "=== Testing %%c ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;

  s21_r = s21_sprintf(s21, "%c", 'A');
  std_r = sprintf(std, "%c", 'A');
  compare_results(s21, std, s21_r, std_r, "%c with 'A'");

  s21_r = s21_sprintf(s21, "%5c", 'X');
  std_r = sprintf(std, "%5c", 'X');
  compare_results(s21, std, s21_r, std_r, "%5c with 'X'");

  s21_r = s21_sprintf(s21, "%-5c", 'X');
  std_r = sprintf(std, "%-5c", 'X');
  compare_results(s21, std, s21_r, std_r, "%-5c with 'X'");

  s21_r = s21_sprintf(s21, "%c%c%c", 'a', 'b', 'c');
  std_r = sprintf(std, "%c%c%c", 'a', 'b', 'c');
  compare_results(s21, std, s21_r, std_r, "%c%c%c");
}

void test_string(void) {
  printf("\n" YELLOW "=== Testing %%s ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;

  s21_r = s21_sprintf(s21, "%s", "Hello");
  std_r = sprintf(std, "%s", "Hello");
  compare_results(s21, std, s21_r, std_r, "%s with 'Hello'");

  s21_r = s21_sprintf(s21, "%s", "");
  std_r = sprintf(std, "%s", "");
  compare_results(s21, std, s21_r, std_r, "%s with empty string");

  s21_r = s21_sprintf(s21, "%10s", "test");
  std_r = sprintf(std, "%10s", "test");
  compare_results(s21, std, s21_r, std_r, "%10s");

  s21_r = s21_sprintf(s21, "%-10s", "test");
  std_r = sprintf(std, "%-10s", "test");
  compare_results(s21, std, s21_r, std_r, "%-10s");

  s21_r = s21_sprintf(s21, "%.3s", "Hello");
  std_r = sprintf(std, "%.3s", "Hello");
  compare_results(s21, std, s21_r, std_r, "%.3s");

  s21_r = s21_sprintf(s21, "%10.3s", "Hello");
  std_r = sprintf(std, "%10.3s", "Hello");
  compare_results(s21, std, s21_r, std_r, "%10.3s");
}

void test_int(void) {
  printf("\n" YELLOW "=== Testing %%d ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;

  s21_r = s21_sprintf(s21, "%d", 0);
  std_r = sprintf(std, "%d", 0);
  compare_results(s21, std, s21_r, std_r, "%d with 0");

  s21_r = s21_sprintf(s21, "%d", 42);
  std_r = sprintf(std, "%d", 42);
  compare_results(s21, std, s21_r, std_r, "%d with 42");

  s21_r = s21_sprintf(s21, "%d", -42);
  std_r = sprintf(std, "%d", -42);
  compare_results(s21, std, s21_r, std_r, "%d with -42");

  s21_r = s21_sprintf(s21, "%5d", 42);
  std_r = sprintf(std, "%5d", 42);
  compare_results(s21, std, s21_r, std_r, "%5d");

  s21_r = s21_sprintf(s21, "%-5d", 42);
  std_r = sprintf(std, "%-5d", 42);
  compare_results(s21, std, s21_r, std_r, "%-5d");

  s21_r = s21_sprintf(s21, "%05d", 42);
  std_r = sprintf(std, "%05d", 42);
  compare_results(s21, std, s21_r, std_r, "%05d");

  s21_r = s21_sprintf(s21, "%+d", 42);
  std_r = sprintf(std, "%+d", 42);
  compare_results(s21, std, s21_r, std_r, "%+d");

  s21_r = s21_sprintf(s21, "% d", 42);
  std_r = sprintf(std, "% d", 42);
  compare_results(s21, std, s21_r, std_r, "% d");

  s21_r = s21_sprintf(s21, "%.5d", 42);
  std_r = sprintf(std, "%.5d", 42);
  compare_results(s21, std, s21_r, std_r, "%.5d");

  s21_r = s21_sprintf(s21, "%10.5d", 42);
  std_r = sprintf(std, "%10.5d", 42);
  compare_results(s21, std, s21_r, std_r, "%10.5d");

  s21_r = s21_sprintf(s21, "%.0d", 0);
  std_r = sprintf(std, "%.0d", 0);
  compare_results(s21, std, s21_r, std_r, "%.0d with 0");

  s21_r = s21_sprintf(s21, "%ld", 2147483647L);
  std_r = sprintf(std, "%ld", 2147483647L);
  compare_results(s21, std, s21_r, std_r, "%ld");
}

void test_unsigned(void) {
  printf("\n" YELLOW "=== Testing %%u ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;

  s21_r = s21_sprintf(s21, "%u", 42U);
  std_r = sprintf(std, "%u", 42U);
  compare_results(s21, std, s21_r, std_r, "%u with 42");

  s21_r = s21_sprintf(s21, "%5u", 42U);
  std_r = sprintf(std, "%5u", 42U);
  compare_results(s21, std, s21_r, std_r, "%5u");

  s21_r = s21_sprintf(s21, "%05u", 42U);
  std_r = sprintf(std, "%05u", 42U);
  compare_results(s21, std, s21_r, std_r, "%05u");
}

void test_octal_hex(void) {
  printf("\n" YELLOW "=== Testing %%o, %%x, %%X ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;

  s21_r = s21_sprintf(s21, "%o", 63U);
  std_r = sprintf(std, "%o", 63U);
  compare_results(s21, std, s21_r, std_r, "%o with 63");

  s21_r = s21_sprintf(s21, "%#o", 8U);
  std_r = sprintf(std, "%#o", 8U);
  compare_results(s21, std, s21_r, std_r, "%#o");

  s21_r = s21_sprintf(s21, "%x", 255U);
  std_r = sprintf(std, "%x", 255U);
  compare_results(s21, std, s21_r, std_r, "%x with 255");

  s21_r = s21_sprintf(s21, "%X", 255U);
  std_r = sprintf(std, "%X", 255U);
  compare_results(s21, std, s21_r, std_r, "%X with 255");

  s21_r = s21_sprintf(s21, "%#x", 255U);
  std_r = sprintf(std, "%#x", 255U);
  compare_results(s21, std, s21_r, std_r, "%#x");

  s21_r = s21_sprintf(s21, "%08x", 255U);
  std_r = sprintf(std, "%08x", 255U);
  compare_results(s21, std, s21_r, std_r, "%08x");
}

void test_float(void) {
  printf("\n" YELLOW "=== Testing %%f ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;

  s21_r = s21_sprintf(s21, "%f", 3.14159);
  std_r = sprintf(std, "%f", 3.14159);
  compare_results(s21, std, s21_r, std_r, "%f with 3.14159");

  s21_r = s21_sprintf(s21, "%f", -3.14159);
  std_r = sprintf(std, "%f", -3.14159);
  compare_results(s21, std, s21_r, std_r, "%f with -3.14159");

  s21_r = s21_sprintf(s21, "%.2f", 3.14159);
  std_r = sprintf(std, "%.2f", 3.14159);
  compare_results(s21, std, s21_r, std_r, "%.2f");

  s21_r = s21_sprintf(s21, "%10.2f", 3.14);
  std_r = sprintf(std, "%10.2f", 3.14);
  compare_results(s21, std, s21_r, std_r, "%10.2f");

  s21_r = s21_sprintf(s21, "%-10.2f", 3.14);
  std_r = sprintf(std, "%-10.2f", 3.14);
  compare_results(s21, std, s21_r, std_r, "%-10.2f");

  s21_r = s21_sprintf(s21, "%+f", 3.14);
  std_r = sprintf(std, "%+f", 3.14);
  compare_results(s21, std, s21_r, std_r, "%+f");

  s21_r = s21_sprintf(s21, "%010.2f", 3.14);
  std_r = sprintf(std, "%010.2f", 3.14);
  compare_results(s21, std, s21_r, std_r, "%010.2f");

  s21_r = s21_sprintf(s21, "%010.2f", inf);
  std_r = sprintf(std, "%010.2f", inf);
  compare_results(s21, std, s21_r, std_r, "INFINITY");
}

void test_exp(void) {
  printf("\n" YELLOW "=== Testing %%e and %%E ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;

  s21_r = s21_sprintf(s21, "%e", 3.14159);
  std_r = sprintf(std, "%e", 3.14159);
  compare_results(s21, std, s21_r, std_r, "%e");

  s21_r = s21_sprintf(s21, "%E", 3.14159);
  std_r = sprintf(std, "%E", 3.14159);
  compare_results(s21, std, s21_r, std_r, "%E");

  s21_r = s21_sprintf(s21, "%.2e", 3.14159);
  std_r = sprintf(std, "%.2e", 3.14159);
  compare_results(s21, std, s21_r, std_r, "%.2e");

  s21_r = s21_sprintf(s21, "%e", 1234567.89);
  std_r = sprintf(std, "%e", 1234567.89);
  compare_results(s21, std, s21_r, std_r, "%e with large number");

  printf("==========Тесты для precision = 0 ===============\n");
  s21_r = s21_sprintf(s21, "%.0e", 123.456);
  std_r = sprintf(std, "%.0e", 123.456);
  compare_results(s21, std, s21_r, std_r, "1e+02");

  s21_r = s21_sprintf(s21, "%#.0e", 123.456);
  std_r = sprintf(std, "%#.0e", 123.456);
  compare_results(s21, std, s21_r, std_r, "1.e+02");

  s21_r = s21_sprintf(s21, "%.0e", 99.999);
  std_r = sprintf(std, "%.0e", 99.999);
  compare_results(s21, std, s21_r, std_r, "1e+02 (округление)");

  s21_r = s21_sprintf(s21, "%.0e", 0.00123);
  std_r = sprintf(std, "%.0e", 0.00123);
  compare_results(s21, std, s21_r, std_r, "1e-03");

  s21_r = s21_sprintf(s21, "%.0e", 0.0);
  std_r = sprintf(std, "%.0e", 0.0);
  compare_results(s21, std, s21_r, std_r, "0e+00");

  s21_r = s21_sprintf(s21, "%#.0e", 0.0);
  std_r = sprintf(std, "%#.0e", 0.0);
  compare_results(s21, std, s21_r, std_r, "0e+00");

  printf("==========Тесты для обычных precision ===============\n");

  s21_r = s21_sprintf(s21, "%.1e", 123.456);
  std_r = sprintf(std, "%.1e", 123.456);
  compare_results(s21, std, s21_r, std_r, "1.2e+02");

  s21_r = s21_sprintf(s21, "%.2e", 123.456);
  std_r = sprintf(std, "%.2e", 123.456);
  compare_results(s21, std, s21_r, std_r, "1.23e+02");

  s21_r = s21_sprintf(s21, "%.3e", 123.456);
  std_r = sprintf(std, "%.3e", 123.456);
  compare_results(s21, std, s21_r, std_r, "1.25e+02");
}

void test_g(void) {
  printf("\n" YELLOW "=== Testing %%g and %%G ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;

  s21_r = s21_sprintf(s21, "%g", 3.14159);
  std_r = sprintf(std, "%g", 3.14159);
  compare_results(s21, std, s21_r, std_r, "%g");

  s21_r = s21_sprintf(s21, "%G", 3.14159);
  std_r = sprintf(std, "%G", 3.14159);
  compare_results(s21, std, s21_r, std_r, "%G");

  s21_r = s21_sprintf(s21, "%g", 0.000001);
  std_r = sprintf(std, "%g", 0.000001);
  compare_results(s21, std, s21_r, std_r, "%g with small number");
}

void test_pointer(void) {
  printf("\n" YELLOW "=== Testing %%p ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;
  int x = 42;

  s21_r = s21_sprintf(s21, "%p", (void *)&x);
  std_r = sprintf(std, "%p", (void *)&x);
  compare_results(s21, std, s21_r, std_r, "%p");
}

void test_percent(void) {
  printf("\n" YELLOW "=== Testing %%%% ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;

  s21_r = s21_sprintf(s21, "%%");
  std_r = sprintf(std, "%%");
  compare_results(s21, std, s21_r, std_r, "%%");

  s21_r = s21_sprintf(s21, "100%%");
  std_r = sprintf(std, "100%%");
  compare_results(s21, std, s21_r, std_r, "100%%");
}

void test_star(void) {
  printf("\n" YELLOW "=== Testing * width and precision ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;

  s21_r = s21_sprintf(s21, "%*d", 10, 42);
  std_r = sprintf(std, "%*d", 10, 42);
  compare_results(s21, std, s21_r, std_r, "%*d");

  s21_r = s21_sprintf(s21, "%.*d", 5, 42);
  std_r = sprintf(std, "%.*d", 5, 42);
  compare_results(s21, std, s21_r, std_r, "%.*d");

  s21_r = s21_sprintf(s21, "%*.*f", 10, 2, 3.14159);
  std_r = sprintf(std, "%*.*f", 10, 2, 3.14159);
  compare_results(s21, std, s21_r, std_r, "%*.*f");

  s21_r = s21_sprintf(s21, "%.f", 3.14159);
  std_r = sprintf(std, "%.f", 3.14159);
  compare_results(s21, std, s21_r, std_r, "%.f");
}

void test_n(void) {
  printf("\n" YELLOW "=== Testing %%n ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_n = 0, std_n = 0;

  s21_sprintf(s21, "Hello%n World", &s21_n);
  sprintf(std, "Hello%n World", &std_n);

  if (strcmp(s21, std) == 0 && s21_n == std_n) {
    printf(GREEN "✓ PASS" RESET ": %%n (n=%d)\n", s21_n);
    tests_passed++;
  } else {
    printf(RED "✗ FAIL" RESET ": %%n\n");
    printf("  s21: \"%s\" (n=%d), std: \"%s\" (n=%d)\n", s21, s21_n, std,
           std_n);
    tests_failed++;
  }
}

void test_combined(void) {
  printf("\n" YELLOW "=== Combined tests ===" RESET "\n");
  char s21[1024], std[1024];
  int s21_r, std_r;

  s21_r = s21_sprintf(s21, "Hello, %s! You have %d messages.", "World", 5);
  std_r = sprintf(std, "Hello, %s! You have %d messages.", "World", 5);
  compare_results(s21, std, s21_r, std_r, "String and int");

  s21_r = s21_sprintf(s21, "Pi is approximately %.4f", 3.14159265);
  std_r = sprintf(std, "Pi is approximately %.4f", 3.14159265);
  compare_results(s21, std, s21_r, std_r, "Float with precision");

  s21_r = s21_sprintf(s21, "Hex: %#x, Oct: %#o, Dec: %d", 255U, 255U, 255);
  std_r = sprintf(std, "Hex: %#x, Oct: %#o, Dec: %d", 255U, 255U, 255);
  compare_results(s21, std, s21_r, std_r, "Hex, Oct, Dec");
}

int main(void) {
  printf(YELLOW "======================================\n");
  printf("  s21_sprintf Test Suite\n");
  printf("======================================" RESET "\n");

  test_char();
  test_string();
  test_int();
  test_unsigned();
  test_octal_hex();
  test_float();
  test_exp();
  test_g();
  test_pointer();
  test_percent();
  test_star();
  test_n();
  test_combined();

  printf("\n" YELLOW "======================================" RESET "\n");
  printf("Total: %d tests\n", tests_passed + tests_failed);
  printf(GREEN "Passed: %d" RESET "\n", tests_passed);
  printf(RED "Failed: %d" RESET "\n", tests_failed);
  printf(YELLOW "======================================" RESET "\n");

  return tests_failed > 0 ? 1 : 0;
}
