#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MY_string.h"

// Цвета для вывода / Colors for output
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

static int tests_passed = 0;
static int tests_failed = 0;

/**
 * @brief Сравнивает результаты MY_sprintf и sprintf
 *        Compares MY_sprintf and sprintf results
 */
void compare_results(const char *MY_buf, const char *std_buf, int MY_ret,
                     int std_ret, const char *test_name) {
  if (strcmp(MY_buf, std_buf) == 0 && MY_ret == std_ret) {
    printf(GREEN "✓ PASS" RESET ": %s\n", test_name);
    tests_passed++;
  } else {
    printf(RED "✗ FAIL" RESET ": %s\n", test_name);
    printf("  Expected: \"%s\" (ret=%d)\n", std_buf, std_ret);
    printf("  Got:      \"%s\" (ret=%d)\n", MY_buf, MY_ret);
    tests_failed++;
  }
}

/**
 * @brief Тесты для спецификатора %c / Tests for %c specifier
 */
void test_char(void) {
  printf("\n" YELLOW "=== Testing %%c ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  MY_r = MY_sprintf(MY, "%c", 'A');
  std_r = sprintf(std, "%c", 'A');
  compare_results(MY, std, MY_r, std_r, "%c with 'A'");

  MY_r = MY_sprintf(MY, "%5c", 'X');
  std_r = sprintf(std, "%5c", 'X');
  compare_results(MY, std, MY_r, std_r, "%5c with 'X'");

  MY_r = MY_sprintf(MY, "%-5c", 'X');
  std_r = sprintf(std, "%-5c", 'X');
  compare_results(MY, std, MY_r, std_r, "%-5c with 'X'");

  MY_r = MY_sprintf(MY, "%c%c%c", 'a', 'b', 'c');
  std_r = sprintf(std, "%c%c%c", 'a', 'b', 'c');
  compare_results(MY, std, MY_r, std_r, "%c%c%c");
}

/**
 * @brief Тесты для спецификатора %s / Tests for %s specifier
 */
void test_string(void) {
  printf("\n" YELLOW "=== Testing %%s ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  MY_r = MY_sprintf(MY, "%s", "Hello");
  std_r = sprintf(std, "%s", "Hello");
  compare_results(MY, std, MY_r, std_r, "%s with 'Hello'");

  MY_r = MY_sprintf(MY, "%s", "");
  std_r = sprintf(std, "%s", "");
  compare_results(MY, std, MY_r, std_r, "%s with empty string");

  MY_r = MY_sprintf(MY, "%10s", "test");
  std_r = sprintf(std, "%10s", "test");
  compare_results(MY, std, MY_r, std_r, "%10s");

  MY_r = MY_sprintf(MY, "%-10s", "test");
  std_r = sprintf(std, "%-10s", "test");
  compare_results(MY, std, MY_r, std_r, "%-10s");

  MY_r = MY_sprintf(MY, "%.3s", "Hello");
  std_r = sprintf(std, "%.3s", "Hello");
  compare_results(MY, std, MY_r, std_r, "%.3s");

  MY_r = MY_sprintf(MY, "%10.3s", "Hello");
  std_r = sprintf(std, "%10.3s", "Hello");
  compare_results(MY, std, MY_r, std_r, "%10.3s");
}

/**
 * @brief Тесты для спецификатора %d / Tests for %d specifier
 */
void test_int(void) {
  printf("\n" YELLOW "=== Testing %%d ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  MY_r = MY_sprintf(MY, "%d", 0);
  std_r = sprintf(std, "%d", 0);
  compare_results(MY, std, MY_r, std_r, "%d with 0");

  MY_r = MY_sprintf(MY, "%d", 42);
  std_r = sprintf(std, "%d", 42);
  compare_results(MY, std, MY_r, std_r, "%d with 42");

  MY_r = MY_sprintf(MY, "%d", -42);
  std_r = sprintf(std, "%d", -42);
  compare_results(MY, std, MY_r, std_r, "%d with -42");

  MY_r = MY_sprintf(MY, "%5d", 42);
  std_r = sprintf(std, "%5d", 42);
  compare_results(MY, std, MY_r, std_r, "%5d");

  MY_r = MY_sprintf(MY, "%-5d", 42);
  std_r = sprintf(std, "%-5d", 42);
  compare_results(MY, std, MY_r, std_r, "%-5d");

  MY_r = MY_sprintf(MY, "%05d", 42);
  std_r = sprintf(std, "%05d", 42);
  compare_results(MY, std, MY_r, std_r, "%05d");

  MY_r = MY_sprintf(MY, "%+d", 42);
  std_r = sprintf(std, "%+d", 42);
  compare_results(MY, std, MY_r, std_r, "%+d");

  MY_r = MY_sprintf(MY, "% d", 42);
  std_r = sprintf(std, "% d", 42);
  compare_results(MY, std, MY_r, std_r, "% d");

  MY_r = MY_sprintf(MY, "%.5d", 42);
  std_r = sprintf(std, "%.5d", 42);
  compare_results(MY, std, MY_r, std_r, "%.5d");

  MY_r = MY_sprintf(MY, "%10.5d", 42);
  std_r = sprintf(std, "%10.5d", 42);
  compare_results(MY, std, MY_r, std_r, "%10.5d");

  MY_r = MY_sprintf(MY, "%.0d", 0);
  std_r = sprintf(std, "%.0d", 0);
  compare_results(MY, std, MY_r, std_r, "%.0d with 0");

  MY_r = MY_sprintf(MY, "%ld", 2147483647L);
  std_r = sprintf(std, "%ld", 2147483647L);
  compare_results(MY, std, MY_r, std_r, "%ld");
}

/**
 * @brief Тесты для спецификатора %u / Tests for %u specifier
 */
void test_unsigned(void) {
  printf("\n" YELLOW "=== Testing %%u ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  MY_r = MY_sprintf(MY, "%u", 42U);
  std_r = sprintf(std, "%u", 42U);
  compare_results(MY, std, MY_r, std_r, "%u with 42");

  MY_r = MY_sprintf(MY, "%5u", 42U);
  std_r = sprintf(std, "%5u", 42U);
  compare_results(MY, std, MY_r, std_r, "%5u");

  MY_r = MY_sprintf(MY, "%05u", 42U);
  std_r = sprintf(std, "%05u", 42U);
  compare_results(MY, std, MY_r, std_r, "%05u");
}

/**
 * @brief Тесты для спецификаторов %o, %x, %X
 */
void test_octal_hex(void) {
  printf("\n" YELLOW "=== Testing %%o, %%x, %%X ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  MY_r = MY_sprintf(MY, "%o", 63U);
  std_r = sprintf(std, "%o", 63U);
  compare_results(MY, std, MY_r, std_r, "%o with 63");

  MY_r = MY_sprintf(MY, "%#o", 8U);
  std_r = sprintf(std, "%#o", 8U);
  compare_results(MY, std, MY_r, std_r, "%#o");

  MY_r = MY_sprintf(MY, "%x", 255U);
  std_r = sprintf(std, "%x", 255U);
  compare_results(MY, std, MY_r, std_r, "%x with 255");

  MY_r = MY_sprintf(MY, "%X", 255U);
  std_r = sprintf(std, "%X", 255U);
  compare_results(MY, std, MY_r, std_r, "%X with 255");

  MY_r = MY_sprintf(MY, "%#x", 255U);
  std_r = sprintf(std, "%#x", 255U);
  compare_results(MY, std, MY_r, std_r, "%#x");

  MY_r = MY_sprintf(MY, "%08x", 255U);
  std_r = sprintf(std, "%08x", 255U);
  compare_results(MY, std, MY_r, std_r, "%08x");
}

/**
 * @brief Тесты для спецификатора %f / Tests for %f specifier
 */
void test_float(void) {
  printf("\n" YELLOW "=== Testing %%f ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  MY_r = MY_sprintf(MY, "%f", 3.14159);
  std_r = sprintf(std, "%f", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%f with 3.14159");

  MY_r = MY_sprintf(MY, "%f", -3.14159);
  std_r = sprintf(std, "%f", -3.14159);
  compare_results(MY, std, MY_r, std_r, "%f with -3.14159");

  MY_r = MY_sprintf(MY, "%.2f", 3.14159);
  std_r = sprintf(std, "%.2f", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%.2f");

  MY_r = MY_sprintf(MY, "%10.2f", 3.14);
  std_r = sprintf(std, "%10.2f", 3.14);
  compare_results(MY, std, MY_r, std_r, "%10.2f");

  MY_r = MY_sprintf(MY, "%-10.2f", 3.14);
  std_r = sprintf(std, "%-10.2f", 3.14);
  compare_results(MY, std, MY_r, std_r, "%-10.2f");

  MY_r = MY_sprintf(MY, "%+f", 3.14);
  std_r = sprintf(std, "%+f", 3.14);
  compare_results(MY, std, MY_r, std_r, "%+f");

  MY_r = MY_sprintf(MY, "%010.2f", 3.14);
  std_r = sprintf(std, "%010.2f", 3.14);
  compare_results(MY, std, MY_r, std_r, "%010.2f");
}

/**
 * @brief Тесты для спецификаторов %e и %E / Tests for %e and %E
 */
void test_exp(void) {
  printf("\n" YELLOW "=== Testing %%e and %%E ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  MY_r = MY_sprintf(MY, "%e", 3.14159);
  std_r = sprintf(std, "%e", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%e");

  MY_r = MY_sprintf(MY, "%E", 3.14159);
  std_r = sprintf(std, "%E", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%E");

  MY_r = MY_sprintf(MY, "%.2e", 3.14159);
  std_r = sprintf(std, "%.2e", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%.2e");

  MY_r = MY_sprintf(MY, "%e", 1234567.89);
  std_r = sprintf(std, "%e", 1234567.89);
  compare_results(MY, std, MY_r, std_r, "%e with large number");
}

/**
 * @brief Тесты для спецификаторов %g и %G / Tests for %g and %G
 */
void test_g(void) {
  printf("\n" YELLOW "=== Testing %%g and %%G ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  MY_r = MY_sprintf(MY, "%g", 3.14159);
  std_r = sprintf(std, "%g", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%g");

  MY_r = MY_sprintf(MY, "%G", 3.14159);
  std_r = sprintf(std, "%G", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%G");

  MY_r = MY_sprintf(MY, "%g", 0.000001);
  std_r = sprintf(std, "%g", 0.000001);
  compare_results(MY, std, MY_r, std_r, "%g with small number");
}

/**
 * @brief Тесты для спецификатора %p / Tests for %p specifier
 */
void test_pointer(void) {
  printf("\n" YELLOW "=== Testing %%p ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;
  int x = 42;

  MY_r = MY_sprintf(MY, "%p", (void *)&x);
  std_r = sprintf(std, "%p", (void *)&x);
  compare_results(MY, std, MY_r, std_r, "%p");
}

/**
 * @brief Тесты для %% / Tests for %%
 */
void test_percent(void) {
  printf("\n" YELLOW "=== Testing %%%% ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  MY_r = MY_sprintf(MY, "%%");
  std_r = sprintf(std, "%%");
  compare_results(MY, std, MY_r, std_r, "%%");

  MY_r = MY_sprintf(MY, "100%%");
  std_r = sprintf(std, "100%%");
  compare_results(MY, std, MY_r, std_r, "100%%");
}

/**
 * @brief Тесты для * ширины и точности / Tests for * width and precision
 */
void test_star(void) {
  printf("\n" YELLOW "=== Testing * width and precision ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  MY_r = MY_sprintf(MY, "%*d", 10, 42);
  std_r = sprintf(std, "%*d", 10, 42);
  compare_results(MY, std, MY_r, std_r, "%*d");

  MY_r = MY_sprintf(MY, "%.*d", 5, 42);
  std_r = sprintf(std, "%.*d", 5, 42);
  compare_results(MY, std, MY_r, std_r, "%.*d");

  MY_r = MY_sprintf(MY, "%*.*f", 10, 2, 3.14159);
  std_r = sprintf(std, "%*.*f", 10, 2, 3.14159);
  compare_results(MY, std, MY_r, std_r, "%*.*f");

  MY_r = MY_sprintf(MY, "%.f", 3.14159);
  std_r = sprintf(std, "%.f", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%.f");
}

/**
 * @brief Тесты для %n / Tests for %n
 */
void test_n(void) {
  printf("\n" YELLOW "=== Testing %%n ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_n = 0, std_n = 0;

  MY_sprintf(MY, "Hello%n World", &MY_n);
  sprintf(std, "Hello%n World", &std_n);

  if (strcmp(MY, std) == 0 && MY_n == std_n) {
    printf(GREEN "✓ PASS" RESET ": %%n (n=%d)\n", MY_n);
    tests_passed++;
  } else {
    printf(RED "✗ FAIL" RESET ": %%n\n");
    printf("  MY: \"%s\" (n=%d), std: \"%s\" (n=%d)\n", MY, MY_n, std,
           std_n);
    tests_failed++;
  }
}

/**
 * @brief Комбинированные тесты / Combined tests
 */
void test_combined(void) {
  printf("\n" YELLOW "=== Combined tests ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  MY_r = MY_sprintf(MY, "Hello, %s! You have %d messages.", "World", 5);
  std_r = sprintf(std, "Hello, %s! You have %d messages.", "World", 5);
  compare_results(MY, std, MY_r, std_r, "String and int");

  MY_r = MY_sprintf(MY, "Pi is approximately %.4f", 3.14159265);
  std_r = sprintf(std, "Pi is approximately %.4f", 3.14159265);
  compare_results(MY, std, MY_r, std_r, "Float with precision");

  MY_r = MY_sprintf(MY, "Hex: %#x, Oct: %#o, Dec: %d", 255U, 255U, 255);
  std_r = sprintf(std, "Hex: %#x, Oct: %#o, Dec: %d", 255U, 255U, 255);
  compare_results(MY, std, MY_r, std_r, "Hex, Oct, Dec");
}

void test_float_additional(void) {
  printf("\n" YELLOW "=== Additional %%f tests ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  // Тест 1: Очень большие числа
  MY_r = MY_sprintf(MY, "%f", 1.0e10);
  std_r = sprintf(std, "%f", 1.0e10);
  compare_results(MY, std, MY_r, std_r, "%f with 1.0e10");

  // Тест 2: Очень маленькие числа
  MY_r = MY_sprintf(MY, "%f", 1.0e-10);
  std_r = sprintf(std, "%f", 1.0e-10);
  compare_results(MY, std, MY_r, std_r, "%f with 1.0e-10");

  // Тест 3: Точность 0 с флагом #
  MY_r = MY_sprintf(MY, "%#.0f", 3.0);
  std_r = sprintf(std, "%#.0f", 3.0);
  compare_results(MY, std, MY_r, std_r, "%#.0f with 3.0");

  // Тест 4: Точность 0 без флага #
  MY_r = MY_sprintf(MY, "%.0f", 3.0);
  std_r = sprintf(std, "%.0f", 3.0);
  compare_results(MY, std, MY_r, std_r, "%.0f with 3.0");

  // Тест 6: Большая точность
  MY_r = MY_sprintf(MY, "%.10f", 3.1415926535);
  std_r = sprintf(std, "%.10f", 3.1415926535);
  compare_results(MY, std, MY_r, std_r, "%.10f");

  // Тест 7: Ширина + точность + флаг 0
  MY_r = MY_sprintf(MY, "%015.5f", 3.14159);
  std_r = sprintf(std, "%015.5f", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%015.5f");

  // Тест 8: Комбинация флагов + и 0
  MY_r = MY_sprintf(MY, "%+015.2f", 3.14);
  std_r = sprintf(std, "%+015.2f", 3.14);
  compare_results(MY, std, MY_r, std_r, "%+015.2f");

  // Тест 9: NaN
  MY_r = MY_sprintf(MY, "%f", NAN);
  std_r = sprintf(std, "%f", NAN);
  compare_results(MY, std, MY_r, std_r, "%f with NAN");
}

void test_exp_additional(void) {
  printf("\n" YELLOW "=== Additional %%e/%%E tests ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  // Тест 1: Экспонента с 3 цифрами
  MY_r = MY_sprintf(MY, "%e", 1.0e100);
  std_r = sprintf(std, "%e", 1.0e100);
  compare_results(MY, std, MY_r, std_r, "%e with 1.0e100");

  // Тест 2: Отрицательная экспонента
  MY_r = MY_sprintf(MY, "%e", 1.0e-100);
  std_r = sprintf(std, "%e", 1.0e-100);
  compare_results(MY, std, MY_r, std_r, "%e with 1.0e-100");

  // Тест 3: Точность 0
  MY_r = MY_sprintf(MY, "%.0e", 3.14159);
  std_r = sprintf(std, "%.0e", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%.0e");

  // Тест 4: Флаг #
  MY_r = MY_sprintf(MY, "%#.0e", 3.0);
  std_r = sprintf(std, "%#.0e", 3.0);
  compare_results(MY, std, MY_r, std_r, "%#.0e");

  MY_r = MY_sprintf(MY, "%E", NAN);
  std_r = sprintf(std, "%E", NAN);
  compare_results(MY, std, MY_r, std_r, "%E with NAN");
}

void test_g_additional(void) {
  printf("\n" YELLOW "=== Additional %%g/%%G tests ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  // Тест 1: Число в экспоненциальной форме (экспонента >= точность)
  MY_r = MY_sprintf(MY, "%g", 1234567.89);
  std_r = sprintf(std, "%g", 1234567.89);
  compare_results(MY, std, MY_r, std_r, "%g with 1234567.89");

  // Тест 2: Число в обычной форме (экспонента < -4)
  MY_r = MY_sprintf(MY, "%g", 0.00001);
  std_r = sprintf(std, "%g", 0.00001);
  compare_results(MY, std, MY_r, std_r, "%g with 0.00001");

  // Тест 3: Число в обычной форме (экспонента < точность)
  MY_r = MY_sprintf(MY, "%g", 123.456);
  std_r = sprintf(std, "%g", 123.456);
  compare_results(MY, std, MY_r, std_r, "%g with 123.456");

  // Тест 4: Точность 0
  MY_r = MY_sprintf(MY, "%.0g", 3.14159);
  std_r = sprintf(std, "%.0g", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%.0g");

  // Тест 5: Флаг #
  MY_r = MY_sprintf(MY, "%#.4g", 3.14159);
  std_r = sprintf(std, "%#.4g", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%#.4g");
}

void test_length_modifiers(void) {
  printf("\n" YELLOW "=== Testing length modifiers ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  // Тест 1: %ld
  MY_r = MY_sprintf(MY, "%ld", 2147483647L);
  std_r = sprintf(std, "%ld", 2147483647L);
  compare_results(MY, std, MY_r, std_r, "%ld");

  // Тест 2: %hd
  MY_r = MY_sprintf(MY, "%hd", 32767);
  std_r = sprintf(std, "%hd", 32767);
  compare_results(MY, std, MY_r, std_r, "%hd");

  // Тест 3: %lu
  MY_r = MY_sprintf(MY, "%lu", 4294967295UL);
  std_r = sprintf(std, "%lu", 4294967295UL);
  compare_results(MY, std, MY_r, std_r, "%lu");

  // Тест 4: %lf
  MY_r = MY_sprintf(MY, "%lf", 3.14159);
  std_r = sprintf(std, "%lf", 3.14159);
  compare_results(MY, std, MY_r, std_r, "%lf");

  // Тест 5: %Lf
  long double ld = 3.14159265358979323846L;
  MY_r = MY_sprintf(MY, "%Lf", ld);
  std_r = sprintf(std, "%Lf", ld);
  compare_results(MY, std, MY_r, std_r, "%Lf");
}

void test_edge_cases(void) {
  printf("\n" YELLOW "=== Testing edge cases ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  // Тест 1: Большая ширина (но не слишком большая для буфера)
  MY_r = MY_sprintf(MY, "%100d", 42);
  std_r = sprintf(std, "%100d", 42);
  compare_results(MY, std, MY_r, std_r, "%100d (large width)");

  // Тест 2: Умеренная точность для float (избегаем переполнения)
  MY_r = MY_sprintf(MY, "%.10f", 3.1415926535);
  std_r = sprintf(std, "%.10f", 3.1415926535);
  compare_results(MY, std, MY_r, std_r, "%.10f (moderate precision)");

  // Тест 3: Отрицательная ширина через *
  MY_r = MY_sprintf(MY, "%*d", -10, 42);
  std_r = sprintf(std, "%*d", -10, 42);
  compare_results(MY, std, MY_r, std_r, "%*d with negative width");

  // Тест 4: Отрицательная точность через * для float
  MY_r = MY_sprintf(MY, "%.*f", -5, 3.14159);
  std_r = sprintf(std, "%.*f", -5, 3.14159);
  compare_results(MY, std, MY_r, std_r, "%.*f with negative precision");

  // Тест 5: Несколько спецификаторов подряд
  MY_r = MY_sprintf(MY, "%d%d%d", 1, 2, 3);
  std_r = sprintf(std, "%d%d%d", 1, 2, 3);
  compare_results(MY, std, MY_r, std_r, "%d%d%d");

  // Тест 8: Только обычные символы, без спецификаторов
  MY_r = MY_sprintf(MY, "Hello World!");
  std_r = sprintf(std, "Hello World!");
  compare_results(MY, std, MY_r, std_r, "Plain text without format");

  // Тест 9: Символ процента в середине строки
  MY_r = MY_sprintf(MY, "50%% discount");
  std_r = sprintf(std, "50%% discount");
  compare_results(MY, std, MY_r, std_r, "Percent sign in middle");

  // Тест 10: Ширина 0
  MY_r = MY_sprintf(MY, "%0d", 42);
  std_r = sprintf(std, "%0d", 42);
  compare_results(MY, std, MY_r, std_r, "%0d");

  // Тест 11: Точность 0 для integer
  MY_r = MY_sprintf(MY, "%.0d", 0);
  std_r = sprintf(std, "%.0d", 0);
  compare_results(MY, std, MY_r, std_r, "%.0d with 0");
}

void test_octal_additional(void) {
  printf("\n" YELLOW "=== Additional %%o tests ===" RESET "\n");
  char MY[1024], std[1024];
  int MY_r, std_r;

  // Тест 2: 0 с точностью 0 без флага #
  MY_r = MY_sprintf(MY, "%.0o", 0);
  std_r = sprintf(std, "%.0o", 0);
  compare_results(MY, std, MY_r, std_r, "%.0o with 0");

  // Тест 3: 0 с точностью 0 с флагом #
  MY_r = MY_sprintf(MY, "%#.0o", 0);
  std_r = sprintf(std, "%#.0o", 0);
  compare_results(MY, std, MY_r, std_r, "%#.0o with 0");
}
/**
 * @brief Главная функция / Main function
 */
int main(void) {
  printf(YELLOW "======================================\n");
  printf("  MY_sprintf Test Suite\n");
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
  test_octal_additional();
  test_float_additional();
  test_exp_additional();
  test_g_additional();
  test_length_modifiers();
  test_edge_cases();

  printf("\n" YELLOW "======================================" RESET "\n");
  printf("Total: %d tests\n", tests_passed + tests_failed);
  printf(GREEN "Passed: %d" RESET "\n", tests_passed);
  printf(RED "Failed: %d" RESET "\n", tests_failed);
  printf(YELLOW "======================================" RESET "\n");

  return tests_failed > 0 ? 1 : 0;
}
