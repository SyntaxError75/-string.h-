#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(test_1_basic_literal_match) {
  printf("Test 1: basic literal match\n");

  const char *str = "Hello World";

  int our_result = s21_sscanf(str, "Hello World");
  int std_result = sscanf(str, "Hello World");

  printf("  Input: '%s'\n", str);
  printf("  Format: '%s'\n", "Hello World");
  printf("  Our result: %d\n", our_result);
  printf("  Std result: %d\n", std_result);

  ck_assert_int_eq(our_result, std_result);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_2_percent_literal) {
  printf("Test 2: percent literal\n");

  const char *str = "%";

  int our_result = s21_sscanf(str, "%%");
  int std_result = sscanf(str, "%%");

  printf("  Input: '%s'\n", str);
  printf("  Format: '%s'\n", "%%");
  printf("  Our result: %d\n", our_result);
  printf("  Std result: %d\n", std_result);

  ck_assert_int_eq(our_result, std_result);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_3_empty_string) {
  printf("Test 3: empty string\n");

  const char *str = "";

  int our_result = s21_sscanf(str, "");
  int std_result = sscanf(str, " ");

  printf("  Input: '%s'\n", str);
  printf("  Format: '%s' (our: empty, std: space)\n", "");
  printf("  Our result: %d\n", our_result);
  printf("  Std result: %d\n", std_result);

  ck_assert_int_eq(our_result, std_result);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_4_mismatch) {
  printf("Test 4: mismatch\n");

  const char *str = "Hello";

  int our_result = s21_sscanf(str, "World");
  int std_result = sscanf(str, "World");

  printf("  Input: '%s'\n", str);
  printf("  Format: '%s'\n", "World");
  printf("  Our result: %d\n", our_result);
  printf("  Std result: %d\n", std_result);

  ck_assert_int_eq(our_result, std_result);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_5_partial_match) {
  printf("Test 5: partial match\n");

  const char *str = "Hello World";

  int our_result = s21_sscanf(str, "Hello");
  int std_result = sscanf(str, "Hello");

  printf("  Input: '%s'\n", str);
  printf("  Format: '%s'\n", "Hello");
  printf("  Our result: %d\n", our_result);
  printf("  Std result: %d\n", std_result);

  ck_assert_int_eq(our_result, std_result);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_6_null_pointer) {
  printf("Test 6: NULL test\n");

  int our_result1 = s21_sscanf(NULL, "test");

  printf("  s21_sscanf(NULL, \"test\"): %d\n", our_result1);

  ck_assert_int_eq(our_result1, -1);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_7_char_basic) {
  printf("Test 7: char basic\n");

  char our_char = 0, std_char = 0;
  const char *str = "y";

  int our_result = s21_sscanf(str, "%c", &our_char);
  int std_result = sscanf(str, "%c", &std_char);

  printf("  Input: '%s'\n", str);
  printf("  Format: '%s'\n", "%c");
  printf("  Our: result = %d, char = '%c'\n", our_result, our_char);
  printf("  Std: result = %d, char = '%c'\n", std_result, std_char);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_char, std_char);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_8_char_space) {
  printf("Test 8: char space\n");

  char our_char = 0, std_char = 0;
  const char *str = "  ";

  int our_result = s21_sscanf(str, "%c", &our_char);
  int std_result = sscanf(str, "%c", &std_char);

  printf("  Input: '%s'\n", str);
  printf("  Format: '%s'\n", "%c");
  printf("  Our: result = %d, char = '%c' (ASCII %d)\n", our_result, our_char,
         our_char);
  printf("  Std: result = %d, char = '%c' (ASCII %d)\n", std_result, std_char,
         std_char);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_char, std_char);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_9_char_skip) {
  printf("Test 9: char skip\n");

  char our_char1 = 0, std_char1 = 0, our_char2 = 0, std_char2 = 0,
       our_char3 = 0, std_char3 = 0;
  const char *str = "abcde";

  int our_result =
      s21_sscanf(str, "%c%*c%c%*c%c", &our_char1, &our_char2, &our_char3);
  int std_result =
      sscanf(str, "%c%*c%c%*c%c", &std_char1, &std_char2, &std_char3);

  printf("  Input: '%s'\n", str);
  printf("  Format: '%s'\n", "%c%*c%c%*c%c");
  printf("  Our: result = %d, char1 = '%c', char2 = '%c', char3 = '%c'\n",
         our_result, our_char1, our_char2, our_char3);
  printf("  Std: result = %d, char1 = '%c', char2 = '%c', char3 = '%c'\n",
         std_result, std_char1, std_char2, std_char3);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_char1, std_char1);
  ck_assert_int_eq(our_char2, std_char2);
  ck_assert_int_eq(our_char3, std_char3);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_10_string_basic) {
  printf("Test 10: string basic\n");

  char our_str[20] = {0}, std_str[20] = {0};
  const char *str = "Aleksandr Chernov";

  int our_result = s21_sscanf(str, "%s", our_str);
  int std_result = sscanf(str, "%s", std_str);

  printf("  Input: '%s'\n", str);
  printf("  Format: '%s'\n", "%s");
  printf("  Our: result = %d, str = '%s'\n", our_result, our_str);
  printf("  Std: result = %d, str = '%s'\n", std_result, std_str);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_str_eq(our_str, std_str);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_11_string_multiple) {
  printf("Test 11: string multiple\n");

  char our_str1[20] = {0}, std_str1[20] = {0}, our_str2[20] = {0},
       std_str2[20] = {0};
  const char *input = "One Two Three";

  int our_result = s21_sscanf(input, "%s %s", our_str1, our_str2);
  int std_result = sscanf(input, "%s %s", std_str1, std_str2);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%s %s");
  printf("  Our: result = %d, str1 = '%s', str2 = '%s'\n", our_result, our_str1,
         our_str2);
  printf("  Std: result = %d, str1 = '%s', str2 = '%s'\n", std_result, std_str1,
         std_str2);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_str_eq(our_str1, std_str1);
  ck_assert_str_eq(our_str2, std_str2);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_12_string_with_skip) {
  printf("Test 12: string with skip\n");

  char our_str[20] = {0}, std_str[20] = {0};
  const char *input = "Skip This Word";

  int our_result = s21_sscanf(input, "%*s %s", our_str);
  int std_result = sscanf(input, "%*s %s", std_str);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%*s %s");
  printf("  Our: result = %d, str = '%s'\n", our_result, our_str);
  printf("  Std: result = %d, str = '%s'\n", std_result, std_str);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_str_eq(our_str, std_str);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_13_string_empty) {
  printf("Test 13: string empty\n");

  char our_str[20], std_str[20];

  memset(our_str, 'X', 19);
  memset(std_str, 'X', 19);
  our_str[19] = '\0';
  std_str[19] = '\0';

  const char *input = "";

  int our_result = s21_sscanf(input, "%s", our_str);
  int std_result = sscanf(input, "%s", std_str);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%s");
  printf("  Our: result = %d, str = 'XXXXXXXXXXXXXXXXXXX'\n", our_result);
  printf("  Std: result = %d, str = 'XXXXXXXXXXXXXXXXXXX'\n", std_result);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_str_eq(our_str, "XXXXXXXXXXXXXXXXXXX");
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_14_string_only_spaces) {
  printf("Test 14: string only spaces\n");

  char our_str[20], std_str[20];

  memset(our_str, 'X', 19);
  memset(std_str, 'X', 19);
  our_str[19] = '\0';
  std_str[19] = '\0';

  const char *input = "     ";

  int our_result = s21_sscanf(input, "%s", our_str);
  int std_result = sscanf(input, "%s", std_str);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%s");
  printf("  Our: result = %d, str = 'XXXXXXXXXXXXXXXXXXX'\n", our_result);
  printf("  Std: result = %d, str = 'XXXXXXXXXXXXXXXXXXX'\n", std_result);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_str_eq(our_str, "XXXXXXXXXXXXXXXXXXX");
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_15_string_mixed_with_char) {
  printf("Test 15: string mixed with char\n");

  char our_char1 = 0, std_char1 = 0, our_char2 = 0, std_char2 = 0;
  char our_str[20] = {0}, std_str[20] = {0};

  const char *input = "XAleksandr WorldB";

  int our_result = s21_sscanf(input, "%c%s%c", &our_char1, our_str, &our_char2);
  int std_result = sscanf(input, "%c%s%c", &std_char1, std_str, &std_char2);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%c%s%c");
  printf("  Our: result = %d, char1 = '%c', str = '%s', char2 = '%c'\n",
         our_result, our_char1, our_str, our_char2);
  printf("  Std: result = %d, char1 = '%c', str = '%s', char2 = '%c'\n",
         std_result, std_char1, std_str, std_char2);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_char1, std_char1);
  ck_assert_int_eq(our_char2, std_char2);
  ck_assert_str_eq(our_str, std_str);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_16_sscanf_empty_string) {
  printf("Test 16: sscanf empty string variants\n");

  char buf[20] = "XXXXX";

  int r1 = sscanf("", "%s", buf);
  int r1_our = s21_sscanf("", "%s", buf);
  printf("  sscanf(\"\", \"%%s\", buf) = %d (our: %d)\n", r1, r1_our);
  ck_assert_int_eq(r1, r1_our);

  int r3 = sscanf("", "hello");
  int r3_our = s21_sscanf("", "hello");
  printf("  sscanf(\"\", \"hello\") = %d (our: %d)\n", r3, r3_our);
  ck_assert_int_eq(r3, r3_our);

  int r4 = sscanf("", "%%");
  int r4_our = s21_sscanf("", "%%");
  printf("  sscanf(\"\", \"%%\") = %d (our: %d)\n", r4, r4_our);
  ck_assert_int_eq(r4, r4_our);

  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_17_int_basic) {
  printf("Test 17: int basic\n");

  int our_val = 0, std_val = 0;
  const char *input = "123";

  int our_result = s21_sscanf(input, "%d", &our_val);
  int std_result = sscanf(input, "%d", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%d");
  printf("  Our: result = %d, value = %d\n", our_result, our_val);
  printf("  Std: result = %d, value = %d\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_18_int_negative) {
  printf("Test 18: int negative\n");

  int our_val = 0, std_val = 0;
  const char *input = "-456";

  int our_result = s21_sscanf(input, "%d", &our_val);
  int std_result = sscanf(input, "%d", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%d");
  printf("  Our: result = %d, value = %d\n", our_result, our_val);
  printf("  Std: result = %d, value = %d\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_19_int_with_spaces) {
  printf("Test 19: int with spaces\n");

  int our_val = 0, std_val = 0;
  const char *input = "   789   ";

  int our_result = s21_sscanf(input, "%d", &our_val);
  int std_result = sscanf(input, "%d", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%d");
  printf("  Our: result = %d, value = %d\n", our_result, our_val);
  printf("  Std: result = %d, value = %d\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_20_int_skip) {
  printf("Test 20: int skip\n");

  int our_val = 0, std_val = 0;
  const char *input = "123 456";

  int our_result = s21_sscanf(input, "%*d %d", &our_val);
  int std_result = sscanf(input, "%*d %d", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%*d %d");
  printf("  Our: result = %d, value = %d\n", our_result, our_val);
  printf("  Std: result = %d, value = %d\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_21_int_no_number) {
  printf("Test 21: int no number\n");

  int our_val = 999, std_val = 999;
  const char *input = "abc";

  int our_result = s21_sscanf(input, "%d", &our_val);
  int std_result = sscanf(input, "%d", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%d");
  printf("  Our: result = %d, value = %d (unchanged)\n", our_result, our_val);
  printf("  Std: result = %d, value = %d (unchanged)\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val, 999);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_22_uint_basic) {
  printf("Test 22: uint basic\n");

  unsigned int our_val = 0, std_val = 0;
  const char *input = "123";

  int our_result = s21_sscanf(input, "%u", &our_val);
  int std_result = sscanf(input, "%u", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%u");
  printf("  Our: result = %d, value = %u\n", our_result, our_val);
  printf("  Std: result = %d, value = %u\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_uint_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_23_uint_large) {
  printf("Test 23: uint large\n");

  unsigned int our_val = 0, std_val = 0;
  const char *input = "4294967295";

  int our_result = s21_sscanf(input, "%u", &our_val);
  int std_result = sscanf(input, "%u", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%u");
  printf("  Our: result = %d, value = %u (max uint)\n", our_result, our_val);
  printf("  Std: result = %d, value = %u (max uint)\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_uint_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_24_uint_with_sign) {
  printf("Test 24: uint with sign\n");

  unsigned int our_val = 0, std_val = 0;
  const char *input = "-123";

  int our_result = s21_sscanf(input, "%u", &our_val);
  int std_result = sscanf(input, "%u", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%u");
  printf("  Our: result = %d, value = %u\n", our_result, our_val);
  printf("  Std: result = %d, value = %u\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_uint_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_25_octal_basic) {
  printf("Test 25: octal basic\n");

  unsigned int our_val1 = 0, std_val1 = 0, our_val2 = 0, std_val2 = 0;
  const char *input = "657 327";

  int our_result = s21_sscanf(input, "%o%o", &our_val1, &our_val2);
  int std_result = sscanf(input, "%o%o", &std_val1, &std_val2);

  printf("  Input: '%s' (octal)\n", input);
  printf("  Format: '%s'\n", "%o%o");
  printf(
      "  Our: result = %d, value1 = %u (octal: %o), value2 = %u (octal: %o)\n",
      our_result, our_val1, our_val1, our_val2, our_val2);
  printf(
      "  Std: result = %d, value1 = %u (octal: %o), value2 = %u (octal: %o)\n",
      std_result, std_val1, std_val1, std_val2, std_val2);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_uint_eq(our_val1, std_val1);
  ck_assert_uint_eq(our_val2, std_val2);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_26_octal_with_zero_prefix) {
  printf("Test 26: octal with zero prefix\n");

  unsigned int our_val = 999, std_val = 999;
  const char *input = "0123";

  int our_result = s21_sscanf(input, "%o", &our_val);
  int std_result = sscanf(input, "%o", &std_val);

  printf("  Input: '%s' (octal with leading zero)\n", input);
  printf("  Format: '%s'\n", "%o");
  printf("  Our: result = %d, value = %u (decimal: %u, octal: %o)\n",
         our_result, our_val, our_val, our_val);
  printf("  Std: result = %d, value = %u (decimal: %u, octal: %o)\n",
         std_result, std_val, std_val, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_uint_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_27_octal_large) {
  printf("Test 27: octal large\n");

  unsigned int our_val = 0, std_val = 0;
  const char *input = "7777777777";

  int our_result = s21_sscanf(input, "%o", &our_val);
  int std_result = sscanf(input, "%o", &std_val);

  printf("  Input: '%s' (octal)\n", input);
  printf("  Format: '%s'\n", "%o");
  printf("  Our: result = %d, value = %u (octal: %o)\n", our_result, our_val,
         our_val);
  printf("  Std: result = %d, value = %u (octal: %o)\n", std_result, std_val,
         std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_uint_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_28_octal_invalid) {
  printf("Test 28: octal invalid\n");

  unsigned int our_val = 999, std_val = 999;
  const char *input = "128";

  int our_result = s21_sscanf(input, "%o", &our_val);
  int std_result = sscanf(input, "%o", &std_val);

  printf("  Input: '%s' (contains digit 8 - invalid for octal)\n", input);
  printf("  Format: '%s'\n", "%o");
  printf("  Our: result = %d, value = %u (unchanged: %u)\n", our_result,
         our_val, our_val);
  printf("  Std: result = %d, value = %u (unchanged: %u)\n", std_result,
         std_val, std_val);

  ck_assert_int_eq(our_result, std_result);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_29_hex_basic) {
  printf("Test 29: hex basic\n");

  unsigned int our_val = 0, std_val = 0;
  const char *input = "1a3f";

  int our_result = s21_sscanf(input, "%x", &our_val);
  int std_result = sscanf(input, "%x", &std_val);

  printf("  Input: '%s' (hex)\n", input);
  printf("  Format: '%s'\n", "%x");
  printf("  Our: result = %d, value = %u (0x%X)\n", our_result, our_val,
         our_val);
  printf("  Std: result = %d, value = %u (0x%X)\n", std_result, std_val,
         std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_uint_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_30_hex_uppercase) {
  printf("Test 30: hex uppercase\n");

  unsigned int our_val = 0, std_val = 0;
  const char *input = "ABCDEF";

  int our_result = s21_sscanf(input, "%X", &our_val);
  int std_result = sscanf(input, "%X", &std_val);

  printf("  Input: '%s' (hex uppercase)\n", input);
  printf("  Format: '%s'\n", "%X");
  printf("  Our: result = %d, value = %u (0x%X)\n", our_result, our_val,
         our_val);
  printf("  Std: result = %d, value = %u (0x%X)\n", std_result, std_val,
         std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_uint_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_31_hex_with_prefix) {
  printf("Test 31: hex with 0x prefix\n");

  unsigned int our_val = 0, std_val = 0;
  const char *input = "0x1A3F";

  int our_result = s21_sscanf(input, "%x", &our_val);
  int std_result = sscanf(input, "%x", &std_val);

  printf("  Input: '%s' (hex with 0x)\n", input);
  printf("  Format: '%s'\n", "%x");
  printf("  Our: result = %d, value = %u (0x%X)\n", our_result, our_val,
         our_val);
  printf("  Std: result = %d, value = %u (0x%X)\n", std_result, std_val,
         std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_uint_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_32_hex_mixed_case) {
  printf("Test 32: hex mixed case\n");

  unsigned int our_val = 0, std_val = 0;
  const char *input = "AaBbCc";

  int our_result = s21_sscanf(input, "%x", &our_val);
  int std_result = sscanf(input, "%x", &std_val);

  printf("  Input: '%s' (hex mixed case)\n", input);
  printf("  Format: '%s'\n", "%x");
  printf("  Our: result = %d, value = %u (0x%X)\n", our_result, our_val,
         our_val);
  printf("  Std: result = %d, value = %u (0x%X)\n", std_result, std_val,
         std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_uint_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_33_i_decimal) {
  printf("Test 33: %%i decimal\n");

  int our_val = 0, std_val = 0;
  const char *input = "123";

  int our_result = s21_sscanf(input, "%i", &our_val);
  int std_result = sscanf(input, "%i", &std_val);

  printf("  Input: '%s' (decimal for %%i)\n", input);
  printf("  Format: '%s'\n", "%i");
  printf("  Our: result = %d, value = %d\n", our_result, our_val);
  printf("  Std: result = %d, value = %d\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_34_i_octal) {
  printf("Test 34: %%i octal (leading 0)\n");

  int our_val = 0, std_val = 0;
  const char *input = "0123";

  int our_result = s21_sscanf(input, "%i", &our_val);
  int std_result = sscanf(input, "%i", &std_val);

  printf("  Input: '%s' (octal for %%i)\n", input);
  printf("  Format: '%s'\n", "%i");
  printf("  Our: result = %d, value = %d (decimal)\n", our_result, our_val);
  printf("  Std: result = %d, value = %d (decimal)\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_35_i_hex) {
  printf("Test 35: %%i hex (0x prefix)\n");

  int our_val = 0, std_val = 0;
  const char *input = "0x1A3F";

  int our_result = s21_sscanf(input, "%i", &our_val);
  int std_result = sscanf(input, "%i", &std_val);

  printf("  Input: '%s' (hex for %%i)\n", input);
  printf("  Format: '%s'\n", "%i");
  printf("  Our: result = %d, value = %d (decimal)\n", our_result, our_val);
  printf("  Std: result = %d, value = %d (decimal)\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_36_i_negative) {
  printf("Test 36: %%i negative decimal\n");

  int our_val = 0, std_val = 0;
  const char *input = "-123";

  int our_result = s21_sscanf(input, "%i", &our_val);
  int std_result = sscanf(input, "%i", &std_val);

  printf("  Input: '%s' (negative for %%i)\n", input);
  printf("  Format: '%s'\n", "%i");
  printf("  Our: result = %d, value = %d\n", our_result, our_val);
  printf("  Std: result = %d, value = %d\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_37_i_negative_octal) {
  printf("Test 37: %%i negative octal\n");

  int our_val = 0, std_val = 0;
  const char *input = "-0123";

  int our_result = s21_sscanf(input, "%i", &our_val);
  int std_result = sscanf(input, "%i", &std_val);

  printf("  Input: '%s' (negative octal for %%i)\n", input);
  printf("  Format: '%s'\n", "%i");
  printf("  Our: result = %d, value = %d (decimal)\n", our_result, our_val);
  printf("  Std: result = %d, value = %d (decimal)\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_38_n_basic) {
  printf("Test 38: %%n basic\n");

  int our_n = 0, std_n = 0;
  int our_val = 0, std_val = 0;
  const char *input = "1234567890";

  int our_result = s21_sscanf(input, "%d%n", &our_val, &our_n);
  int std_result = sscanf(input, "%d%n", &std_val, &std_n);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%d%n");
  printf("  Our: result = %d, value = %d, n = %d\n", our_result, our_val,
         our_n);
  printf("  Std: result = %d, value = %d, n = %d\n", std_result, std_val,
         std_n);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val, std_val);
  ck_assert_int_eq(our_n, std_n);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_39_n_middle) {
  printf("Test 39: %%n in middle\n");

  int our_n = 0, std_n = 0;
  int our_val1 = 0, std_val1 = 0;
  int our_val2 = 0, std_val2 = 0;
  const char *input = "1238 45656";

  int our_result = s21_sscanf(input, "%d%n%d", &our_val1, &our_n, &our_val2);
  int std_result = sscanf(input, "%d%n%d", &std_val1, &std_n, &std_val2);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%d%n%d");
  printf("  Our: result = %d, val1 = %d, n = %d, val2 = %d\n", our_result,
         our_val1, our_n, our_val2);
  printf("  Std: result = %d, val1 = %d, n = %d, val2 = %d\n", std_result,
         std_val1, std_n, std_val2);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_val1, std_val1);
  ck_assert_int_eq(our_n, std_n);
  ck_assert_int_eq(our_val2, std_val2);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_40_n_with_skip) {
  printf("Test 40: %%n with skip\n");

  int our_n = 0, std_n = 0;
  const char *input = "6785439";

  int our_result = s21_sscanf(input, "%*d%n", &our_n);
  int std_result = sscanf(input, "%*d%n", &std_n);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%*d%n");
  printf("  Our: result = %d, n = %d\n", our_result, our_n);
  printf("  Std: result = %d, n = %d\n", std_result, std_n);

  ck_assert_int_eq(our_result, std_result);
  ck_assert_int_eq(our_n, std_n);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_41_multiple_specifiers_in_row) {
  printf("Test 41: multiple specifiers in row\n");

  char our_c = 0, std_c = 0;
  int our_d = 0, std_d = 0;
  unsigned int our_x = 0, std_x = 0;
  unsigned int our_X = 0, std_X = 0;
  unsigned int our_o = 0, std_o = 0;
  char our_s[20] = {0}, std_s[20] = {0};
  int our_i = 0, std_i = 0;

  const char *input = "A123 dead BEEF 777 Hello -0x1A";

  int our_result = s21_sscanf(input, "%c%d%x%X%o%s%i", &our_c, &our_d, &our_x,
                              &our_X, &our_o, our_s, &our_i);
  int std_result = sscanf(input, "%c%d%x%X%o%s%i", &std_c, &std_d, &std_x,
                          &std_X, &std_o, std_s, &std_i);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%c%d%x%X%o%s%i");
  printf("  Our: result = %d\n", our_result);
  printf("  Our values: c='%c', d=%d, x=0x%X, X=0x%X, o=%o, s='%s', i=%d\n",
         our_c, our_d, our_x, our_X, our_o, our_s, our_i);
  printf("  Std: result = %d\n", std_result);
  printf("  Std values: c='%c', d=%d, x=0x%X, X=0x%X, o=%o, s='%s', i=%d\n",
         std_c, std_d, std_x, std_X, std_o, std_s, std_i);

  ck_assert_int_eq(our_result, std_result);
  if (our_result >= 1) ck_assert_int_eq(our_c, std_c);
  if (our_result >= 2) ck_assert_int_eq(our_d, std_d);
  if (our_result >= 3) ck_assert_uint_eq(our_x, std_x);
  if (our_result >= 4) ck_assert_uint_eq(our_X, std_X);
  if (our_result >= 5) ck_assert_uint_eq(our_o, std_o);
  if (our_result >= 6) ck_assert_str_eq(our_s, std_s);
  if (our_result >= 7) ck_assert_int_eq(our_i, std_i);

  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_42_n_at_beginning) {
  printf("Test 42: %%n at beginning\n");

  int our_n = 999, std_n = 999;
  int our_val = 0, std_val = 0;
  const char *input = "12345";

  int our_result = s21_sscanf(input, "%n%d", &our_n, &our_val);
  int std_result = sscanf(input, "%n%d", &std_n, &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%n%d");
  printf("  Our: result = %d, n = %d, value = %d\n", our_result, our_n,
         our_val);
  printf("  Std: result = %d, n = %d, value = %d\n", std_result, std_n,
         std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result >= 1) ck_assert_int_eq(our_n, std_n);
  if (our_result >= 2) ck_assert_int_eq(our_val, std_val);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_43_n_with_multiple_values) {
  printf("Test 43: multiple %%n\n");

  int our_n1 = 0, std_n1 = 0;
  int our_n2 = 0, std_n2 = 0;
  int our_n3 = 0, std_n3 = 0;
  int our_val1 = 0, std_val1 = 0, our_val3 = 0, std_val3 = 0;
  char our_val2[20] = {0}, std_val2[20] = {0};

  const char *input = "123 abc 456";

  int our_result = s21_sscanf(input, "%d%n%s%n%d%n", &our_val1, &our_n1,
                              our_val2, &our_n2, &our_val3, &our_n3);
  int std_result = sscanf(input, "%d%n%s%n%d%n", &std_val1, &std_n1, std_val2,
                          &std_n2, &std_val3, &std_n3);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%d%n%s%n%d%n");
  printf("  Our: result = %d\n", our_result);
  printf("  Our: n1=%d, n2=%d, n3=%d\n", our_n1, our_n2, our_n3);
  printf("  Std: result = %d\n", std_result);
  printf("  Std: n1=%d, n2=%d, n3=%d\n", std_n1, std_n2, std_n3);

  ck_assert_int_eq(our_result, std_result);
  if (our_result >= 2) ck_assert_int_eq(our_n1, std_n1);
  if (our_result >= 4) ck_assert_int_eq(our_n2, std_n2);
  if (our_result >= 5) ck_assert_int_eq(our_n3, std_n3);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_44_n_with_skip_and_spaces) {
  printf("Test 44: %%n with skip and spaces\n");

  int our_n1 = 0, std_n1 = 0;
  int our_n2 = 0, std_n2 = 0;
  int our_val = 0, std_val = 0;

  const char *input = "  123  456  789  ";

  int our_result = s21_sscanf(input, "%*d%n%d%n", &our_n1, &our_val, &our_n2);
  int std_result = sscanf(input, "%*d%n%d%n", &std_n1, &std_val, &std_n2);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%*d%n%d%n");
  printf("  Our: result = %d, n1=%d, value=%d, n2=%d\n", our_result, our_n1,
         our_val, our_n2);
  printf("  Std: result = %d, n1=%d, value=%d, n2=%d\n", std_result, std_n1,
         std_val, std_n2);

  ck_assert_int_eq(our_result, std_result);
  if (our_result >= 1) ck_assert_int_eq(our_n1, std_n1);
  if (our_result >= 2) ck_assert_int_eq(our_val, std_val);
  if (our_result >= 3) ck_assert_int_eq(our_n2, std_n2);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_45_n_empty_string) {
  printf("Test 45: %%n empty string\n");

  int our_n = 999, std_n = 999;
  const char *input = "";

  int our_result = s21_sscanf(input, "%n", &our_n);
  int std_result = sscanf(input, "%n", &std_n);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%n");
  printf("  Our: result = %d, n = %d\n", our_result, our_n);
  printf("  Std: result = %d, n = %d\n", std_result, std_n);

  ck_assert_int_eq(our_result, std_result);
  if (our_result != EOF) ck_assert_int_eq(our_n, std_n);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_46_pointer_basic) {
  printf("Test 46: %%p basic\n");

  void *our_ptr = NULL, *std_ptr = NULL;
  const char *input = "0x1A3F";

  int our_result = s21_sscanf(input, "%p", &our_ptr);
  int std_result = sscanf(input, "%p", &std_ptr);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%p");
  printf("  Our: result = %d, ptr = %p\n", our_result, our_ptr);
  printf("  Std: result = %d, ptr = %p\n", std_result, std_ptr);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_ptr_eq(our_ptr, std_ptr);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_47_pointer_no_prefix) {
  printf("Test 47: %%p no 0x prefix\n");

  void *our_ptr = NULL, *std_ptr = NULL;
  const char *input = "DEADBEEF";

  int our_result = s21_sscanf(input, "%p", &our_ptr);
  int std_result = sscanf(input, "%p", &std_ptr);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%p");
  printf("  Our: result = %d, ptr = %p\n", our_result, our_ptr);
  printf("  Std: result = %d, ptr = %p\n", std_result, std_ptr);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_ptr_eq(our_ptr, std_ptr);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_48_pointer_null) {
  printf("Test 48: %%p null (0x0)\n");

  void *our_ptr = (void *)0x12345678, *std_ptr = (void *)0x12345678;
  const char *input = "0x0";

  int our_result = s21_sscanf(input, "%p", &our_ptr);
  int std_result = sscanf(input, "%p", &std_ptr);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%p");
  printf("  Our: result = %d, ptr = %p\n", our_result, our_ptr);
  printf("  Std: result = %d, ptr = %p\n", std_result, std_ptr);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_ptr_eq(our_ptr, std_ptr);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_49_pointer_with_other_specifiers) {
  printf("Test 49: %%p with other specifiers\n");

  void *our_ptr1 = NULL, *std_ptr1 = NULL;
  void *our_ptr2 = NULL, *std_ptr2 = NULL;
  int our_val = 0, std_val = 0;

  const char *input = "0x1234 5678 0xABCD";

  int our_result = s21_sscanf(input, "%p%d%p", &our_ptr1, &our_val, &our_ptr2);
  int std_result = sscanf(input, "%p%d%p", &std_ptr1, &std_val, &std_ptr2);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%p%d%p");
  printf("  Our: result = %d, ptr1 = %p, val = %d, ptr2 = %p\n", our_result,
         our_ptr1, our_val, our_ptr2);
  printf("  Std: result = %d, ptr1 = %p, val = %d, ptr2 = %p\n", std_result,
         std_ptr1, std_val, std_ptr2);

  ck_assert_int_eq(our_result, std_result);
  if (our_result >= 1) ck_assert_ptr_eq(our_ptr1, std_ptr1);
  if (our_result >= 2) ck_assert_int_eq(our_val, std_val);
  if (our_result >= 3) ck_assert_ptr_eq(our_ptr2, std_ptr2);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_50_pointer_complex) {
  printf("Test 50: %%p complex\n");

  void *our_ptr1 = NULL, *std_ptr1 = NULL;
  void *our_ptr2 = NULL, *std_ptr2 = NULL;
  char our_str[20] = {0}, std_str[20] = {0};
  int our_n = 0, std_n = 0;

  const char *input = "0x1234abcd 0x0 Hello";

  int our_result =
      s21_sscanf(input, "%p%n%p%s", &our_ptr1, &our_n, &our_ptr2, our_str);
  int std_result =
      sscanf(input, "%p%n%p%s", &std_ptr1, &std_n, &std_ptr2, std_str);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%p%n%p%s");
  printf("  Our: result = %d, ptr1 = %p, n = %d, ptr2 = %p, str = '%s'\n",
         our_result, our_ptr1, our_n, our_ptr2, our_str);
  printf("  Std: result = %d, ptr1 = %p, n = %d, ptr2 = %p, str = '%s'\n",
         std_result, std_ptr1, std_n, std_ptr2, std_str);

  ck_assert_int_eq(our_result, std_result);
  if (our_result >= 1) ck_assert_ptr_eq(our_ptr1, std_ptr1);
  if (our_result >= 2) ck_assert_int_eq(our_n, std_n);
  if (our_result >= 3) ck_assert_ptr_eq(our_ptr2, std_ptr2);
  if (our_result >= 4) ck_assert_str_eq(our_str, std_str);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_51_pointer_edge_cases) {
  printf("Test 51: %%p edge cases\n");

  void *our_ptr = NULL, *std_ptr = NULL;

  const char *input1 = "0xFFFFFFFFFFFFFFFF";
  const char *format1 = "%p";

  int our_result1 = s21_sscanf(input1, format1, &our_ptr);
  int std_result1 = sscanf(input1, format1, &std_ptr);

  printf("  Test 1 - Max value:\n");
  printf("  Input: '%s'\n", input1);
  printf("  Our: result = %d, ptr = %p\n", our_result1, our_ptr);
  printf("  Std: result = %d, ptr = %p\n", std_result1, std_ptr);
  ck_assert_int_eq(our_result1, std_result1);

  const char *input2 = "0x1";
  our_ptr = NULL;
  std_ptr = NULL;

  int our_result2 = s21_sscanf(input2, format1, &our_ptr);
  int std_result2 = sscanf(input2, format1, &std_ptr);

  printf("  Test 2 - Small value:\n");
  printf("  Input: '%s'\n", input2);
  printf("  Our: result = %d, ptr = %p\n", our_result2, our_ptr);
  printf("  Std: result = %d, ptr = %p\n", std_result2, std_ptr);
  ck_assert_int_eq(our_result2, std_result2);

  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_52_pointer_empty_string) {
  printf("Test 52: %%p empty string\n");

  void *our_ptr = (void *)0x12345678;
  void *std_ptr = (void *)0x12345678;

  const char *input1 = "";
  const char *format1 = "%p";

  int our_result1 = s21_sscanf(input1, format1, &our_ptr);
  int std_result1 = sscanf(input1, format1, &std_ptr);

  printf("  Empty string:\n");
  printf("  Input: '%s'\n", input1);
  printf("  Our: result = %d\n", our_result1);
  printf("  Std: result = %d\n", std_result1);
  ck_assert_int_eq(our_result1, std_result1);
  ck_assert_ptr_eq(our_ptr, (void *)0x12345678);

  const char *input2 = "   ";
  our_ptr = (void *)0x12345678;
  std_ptr = (void *)0x12345678;

  int our_result2 = s21_sscanf(input2, format1, &our_ptr);
  int std_result2 = sscanf(input2, format1, &std_ptr);

  printf("  Only spaces:\n");
  printf("  Input: '%s'\n", input2);
  printf("  Our: result = %d\n", our_result2);
  printf("  Std: result = %d\n", std_result2);
  ck_assert_int_eq(our_result2, std_result2);
  ck_assert_ptr_eq(our_ptr, (void *)0x12345678);

  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_53_float_basic) {
  printf("Test 53: %%f basic\n");

  float our_val = 0.0f, std_val = 0.0f;
  const char *input = "123.456";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.6f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.6f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_val - std_val) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_54_float_integer) {
  printf("Test 54: %%f integer\n");

  float our_val = 0.0f, std_val = 0.0f;
  const char *input = "789";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.6f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.6f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    float diff = our_val - std_val;
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.000001f);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_55_float_fraction_only) {
  printf("Test 55: %%f fraction only (.789)\n");

  float our_val = 0.0f, std_val = 0.0f;
  const char *input = ".789";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.6f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.6f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    float diff = our_val - std_val;
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.000001f);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_56_float_negative) {
  printf("Test 56: %%f negative\n");

  float our_val = 0.0f, std_val = 0.0f;
  const char *input = "-123.456";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.6f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.6f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    float diff = our_val - std_val;
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.000001f);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_57_float_empty_string) {
  printf("Test 57: %%f empty string\n");

  float our_val = 999.999f, std_val = 999.999f;
  const char *input = "";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.6f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.6f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert(fabs(our_val - 999.999f) < 0.000001f);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_58_float_only_spaces) {
  printf("Test 58: %%f only spaces\n");

  float our_val = 888.888f, std_val = 888.888f;
  const char *input = "   ";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.6f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.6f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert(fabs(our_val - 888.888f) < 0.000001f);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_59_float_dot_only) {
  printf("Test 59: %%f dot only\n");

  float our_val = 777.777f, std_val = 777.777f;
  const char *input = ".";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.6f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.6f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert(fabs(our_val - 777.777f) < 0.000001f);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_60_float_sign_only) {
  printf("Test 60: %%f sign only\n");

  float our_val = 666.666f, std_val = 666.666f;
  const char *input = "+";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.6f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.6f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  ck_assert(fabs(our_val - 666.666f) < 0.000001f);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_61_float_very_small) {
  printf("Test 61: %%f very small\n");

  float our_val = 0.0f, std_val = 0.0f;
  const char *input = "0.000001";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.10f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.10f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    float diff = our_val - std_val;
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0000001f);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_62_float_with_others) {
  printf("Test 62: %%f with other types\n");

  float our_f1 = 0.0f, our_f2 = 0.0f;
  int our_i = 0, std_i = 0;
  char our_s[20] = {0}, std_s[20] = {0};

  const char *input = "12.34 -56.78 999 hello";

  int our_result =
      s21_sscanf(input, "%f%f%d%s", &our_f1, &our_f2, &our_i, our_s);
  int std_result = sscanf(input, "%f%f%d%s", &our_f1, &our_f2, &std_i, std_s);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f%f%d%s");
  printf("  Our: result = %d, f1=%.2f, f2=%.2f, i=%d, s='%s'\n", our_result,
         our_f1, our_f2, our_i, our_s);
  printf("  Std: result = %d, f1=%.2f, f2=%.2f, i=%d, s='%s'\n", std_result,
         our_f1, our_f2, std_i, std_s);

  ck_assert_int_eq(our_result, std_result);
  if (our_result >= 1) {
    float diff = our_f1 - our_f1;
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001f);
  }
  if (our_result >= 2) {
    float diff = our_f2 - our_f2;
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.0001f);
  }
  if (our_result >= 3) ck_assert_int_eq(our_i, std_i);
  if (our_result >= 4) ck_assert_str_eq(our_s, std_s);

  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_63_float_scientific_positive) {
  printf("Test 63: %%f scientific positive (1.23e4)\n");

  float our_val = 0.0f, std_val = 0.0f;
  const char *input = "1.23e4";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.2f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.2f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    float diff = our_val - std_val;
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.01f);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_64_float_scientific_negative) {
  printf("Test 64: %%f scientific negative (5.6E-7)\n");

  float our_val = 0.0f, std_val = 0.0f;
  const char *input = "5.6E-7";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.10f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.10f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    float diff = our_val - std_val;
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.000000001f);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_65_float_scientific_uppercase) {
  printf("Test 65: %%f scientific uppercase (2.5E+3)\n");

  float our_val = 0.0f, std_val = 0.0f;
  const char *input = "2.5E+3";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.2f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.2f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    float diff = our_val - std_val;
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.01f);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_66_float_scientific_no_sign) {
  printf("Test 66: %%f scientific no sign (7.89e2)\n");

  float our_val = 0.0f, std_val = 0.0f;
  const char *input = "7.89e2";

  int our_result = s21_sscanf(input, "%f", &our_val);
  int std_result = sscanf(input, "%f", &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f");
  printf("  Our: result = %d, value = %.2f\n", our_result, our_val);
  printf("  Std: result = %d, value = %.2f\n", std_result, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    float diff = our_val - std_val;
    if (diff < 0) diff = -diff;
    ck_assert(diff < 0.01f);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_67_float_specifiers) {
  printf("Test 67: %%f %%e %%E %%g specifiers\n");

  float our_f1 = 0.0f, our_f2 = 0.0f, our_f3 = 0.0f, our_f4 = 0.0f,
        our_f5 = 0.0f;
  float std_f1 = 0.0f, std_f2 = 0.0f, std_f3 = 0.0f, std_f4 = 0.0f,
        std_f5 = 0.0f;
  const char *input = "123.456 789.012 1.23e4 4.56E-2 3.14159";

  int our_result = s21_sscanf(input, "%f %f %e %E %g", &our_f1, &our_f2,
                              &our_f3, &our_f4, &our_f5);
  int std_result = sscanf(input, "%f %f %e %E %g", &std_f1, &std_f2, &std_f3,
                          &std_f4, &std_f5);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f %f %e %E %g");
  printf("  Our: result = %d, values = [%.6f, %.6f, %.6f, %.6f, %.6f]\n",
         our_result, our_f1, our_f2, our_f3, our_f4, our_f5);
  printf("  Std: result = %d, values = [%.6f, %.6f, %.6f, %.6f, %.6f]\n",
         std_result, std_f1, std_f2, std_f3, std_f4, std_f5);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f1 - std_f1) < 1e-6);
    ck_assert(fabs(our_f2 - std_f2) < 1e-6);
    ck_assert(fabs(our_f3 - std_f3) < 1e-6);
    ck_assert(fabs(our_f4 - std_f4) < 1e-6);
    ck_assert(fabs(our_f5 - std_f5) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_68_float_with_skip) {
  printf("Test 68: %%f with skip\n");

  float our_f1 = 0.0f, our_f2 = 0.0f;
  float std_f1 = 0.0f, std_f2 = 0.0f;
  const char *input = "1.0 2.0 3.0 4.0 5.0";

  int our_result = s21_sscanf(input, "%f %*f %f %*f %*f", &our_f1, &our_f2);
  int std_result = sscanf(input, "%f %*f %f %*f %*f", &std_f1, &std_f2);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f %*f %f %*f %*f");
  printf("  Our: result = %d, values = [%.6f, %.6f]\n", our_result, our_f1,
         our_f2);
  printf("  Std: result = %d, values = [%.6f, %.6f]\n", std_result, std_f1,
         std_f2);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f1 - std_f1) < 1e-6);
    ck_assert(fabs(our_f2 - std_f2) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_69_float_signs) {
  printf("Test 69: %%f with different signs\n");

  float our_f1 = 0.0f, our_f2 = 0.0f, our_f3 = 0.0f;
  float std_f1 = 0.0f, std_f2 = 0.0f, std_f3 = 0.0f;
  const char *input = "+123.456 -789.012 0.0";

  int our_result = s21_sscanf(input, "%f %f %f", &our_f1, &our_f2, &our_f3);
  int std_result = sscanf(input, "%f %f %f", &std_f1, &std_f2, &std_f3);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f %f %f");
  printf("  Our: result = %d, values = [%.6f, %.6f, %.6f]\n", our_result,
         our_f1, our_f2, our_f3);
  printf("  Std: result = %d, values = [%.6f, %.6f, %.6f]\n", std_result,
         std_f1, std_f2, std_f3);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f1 - std_f1) < 1e-6);
    ck_assert(fabs(our_f2 - std_f2) < 1e-6);
    ck_assert(fabs(our_f3 - std_f3) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_70_float_exponential) {
  printf("Test 70: %%e exponential format\n");

  float our_f1 = 0.0f, our_f2 = 0.0f, our_f3 = 0.0f, our_f4 = 0.0f;
  float std_f1 = 0.0f, std_f2 = 0.0f, std_f3 = 0.0f, std_f4 = 0.0f;
  const char *input = "1.23e4 5.67E-3 1e6 2.5e+10";

  int our_result =
      s21_sscanf(input, "%e %e %e %e", &our_f1, &our_f2, &our_f3, &our_f4);
  int std_result =
      sscanf(input, "%e %e %e %e", &std_f1, &std_f2, &std_f3, &std_f4);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%e %e %e %e");
  printf("  Our: result = %d, values = [%g, %g, %g, %g]\n", our_result, our_f1,
         our_f2, our_f3, our_f4);
  printf("  Std: result = %d, values = [%g, %g, %g, %g]\n", std_result, std_f1,
         std_f2, std_f3, std_f4);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f1 - std_f1) < 1e-6);
    ck_assert(fabs(our_f2 - std_f2) < 1e-6);
    ck_assert(fabs(our_f3 - std_f3) < 1e-6);
    ck_assert(fabs(our_f4 - std_f4) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_71_float_edge_cases) {
  printf("Test 71: %%f edge cases\n");

  float our_f1 = 0.0f, our_f2 = 0.0f, our_f3 = 0.0f, our_f4 = 0.0f;
  float std_f1 = 0.0f, std_f2 = 0.0f, std_f3 = 0.0f, std_f4 = 0.0f;
  const char *input = ".123 456. .007 100.";

  int our_result =
      s21_sscanf(input, "%f %f %f %f", &our_f1, &our_f2, &our_f3, &our_f4);
  int std_result =
      sscanf(input, "%f %f %f %f", &std_f1, &std_f2, &std_f3, &std_f4);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f %f %f %f");
  printf("  Our: result = %d, values = [%f, %f, %f, %f]\n", our_result, our_f1,
         our_f2, our_f3, our_f4);
  printf("  Std: result = %d, values = [%f, %f, %f, %f]\n", std_result, std_f1,
         std_f2, std_f3, std_f4);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f1 - std_f1) < 1e-6);
    ck_assert(fabs(our_f2 - std_f2) < 1e-6);
    ck_assert(fabs(our_f3 - std_f3) < 1e-6);
    ck_assert(fabs(our_f4 - std_f4) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_72_float_empty_mismatch) {
  printf("Test 72: %%f empty/mismatch\n");

  float our_val = 0.0f, std_val = 0.0f;
  const char *input1 = "";
  const char *input2 = "abc";
  const char *input3 = "   ";

  int our_result1 = s21_sscanf(input1, "%f", &our_val);
  int our_result2 = s21_sscanf(input2, "%f", &our_val);
  int our_result3 = s21_sscanf(input3, "%f", &our_val);

  int std_result1 = sscanf(input1, "%f", &std_val);
  int std_result2 = sscanf(input2, "%f", &std_val);
  int std_result3 = sscanf(input3, "%f", &std_val);

  printf("  Input1: '%s'\n", input1);
  printf("  Input2: '%s'\n", input2);
  printf("  Input3: '%s'\n", input3);
  printf("  Format: '%s'\n", "%f");
  printf("  Empty: Our=%d, Std=%d\n", our_result1, std_result1);
  printf("  Non-numeric: Our=%d, Std=%d\n", our_result2, std_result2);
  printf("  Only spaces: Our=%d, Std=%d\n", our_result3, std_result3);

  ck_assert_int_eq(our_result1, std_result1);
  ck_assert_int_eq(our_result2, std_result2);
  ck_assert_int_eq(our_result3, std_result3);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_73_float_length_modifiers) {
  printf("Test 73: %%lf and %%Lf length modifiers\n");

  double our_d1 = 0.0, std_d1 = 0.0;
  long double our_ld1 = 0.0, std_ld1 = 0.0;
  const char *input = "123.456789";

  int our_result1 = s21_sscanf(input, "%lf", &our_d1);
  int std_result1 = sscanf(input, "%lf", &std_d1);

  int our_result2 = s21_sscanf(input, "%Lf", &our_ld1);
  int std_result2 = sscanf(input, "%Lf", &std_ld1);

  printf("  Input: '%s'\n", input);
  printf("  Format '%%lf':\n");
  printf("  Our: result = %d, value = %.9f\n", our_result1, our_d1);
  printf("  Std: result = %d, value = %.9f\n", std_result1, std_d1);

  printf("  Format '%%Lf':\n");
  printf("  Our: result = %d, value = %.9Lf\n", our_result2, our_ld1);
  printf("  Std: result = %d, value = %.9Lf\n", std_result2, std_ld1);

  ck_assert_int_eq(our_result1, std_result1);
  ck_assert_int_eq(our_result2, std_result2);

  if (our_result1 > 0) {
    ck_assert(fabs(our_d1 - std_d1) < 1e-9);
  }
  if (our_result2 > 0) {
    long double diff = our_ld1 - std_ld1;
    if (diff < 0) diff = -diff;
    ck_assert(diff < 1e-9L);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_74_float_mixed_types) {
  printf("Test 74: %%f mixed with int and string\n");

  int our_i = 0, std_i = 0;
  float our_f = 0.0f, std_f = 0.0f;
  char our_s[20] = {0}, std_s[20] = {0};
  const char *input = "42 3.14 hello";

  int our_result = s21_sscanf(input, "%d %f %s", &our_i, &our_f, our_s);
  int std_result = sscanf(input, "%d %f %s", &std_i, &std_f, std_s);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%d %f %s");
  printf("  Our: result = %d, values = [%d, %.6f, '%s']\n", our_result, our_i,
         our_f, our_s);
  printf("  Std: result = %d, values = [%d, %.6f, '%s']\n", std_result, std_i,
         std_f, std_s);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_int_eq(our_i, std_i);
    ck_assert(fabs(our_f - std_f) < 1e-6);
    ck_assert_str_eq(our_s, std_s);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_75_float_g_G) {
  printf("Test 75: %%g and %%G specifiers\n");

  float our_f1 = 0.0f, our_f2 = 0.0f, our_f3 = 0.0f;
  float std_f1 = 0.0f, std_f2 = 0.0f, std_f3 = 0.0f;
  const char *input = "123.456 1.23456e8 0.000001";

  int our_result = s21_sscanf(input, "%g %G %g", &our_f1, &our_f2, &our_f3);
  int std_result = sscanf(input, "%g %G %g", &std_f1, &std_f2, &std_f3);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%g %G %g");
  printf("  Our: result = %d, values = [%g, %g, %g]\n", our_result, our_f1,
         our_f2, our_f3);
  printf("  Std: result = %d, values = [%g, %g, %g]\n", std_result, std_f1,
         std_f2, std_f3);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f1 - std_f1) < 1e-6);
    ck_assert(fabs(our_f2 - std_f2) < 1e-6);
    ck_assert(fabs(our_f3 - std_f3) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_76_float_extreme_values) {
  printf("Test 76: %%f extreme values\n");

  float our_f1 = 0.0f, our_f2 = 0.0f;
  float std_f1 = 0.0f, std_f2 = 0.0f;
  const char *input = "3.402823e+38 1.175494e-38";

  int our_result = s21_sscanf(input, "%f %f", &our_f1, &our_f2);
  int std_result = sscanf(input, "%f %f", &std_f1, &std_f2);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f %f");
  printf("  Our: result = %d, values = [%g, %g]\n", our_result, our_f1, our_f2);
  printf("  Std: result = %d, values = [%g, %g]\n", std_result, std_f1, std_f2);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f1 - std_f1) < 1e-6);
    ck_assert(fabs(our_f2 - std_f2) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_77_float_multiple_skips) {
  printf("Test 77: %%f multiple skips\n");

  float our_f = 0.0f, std_f = 0.0f;
  const char *input = "1.1 2.2 3.3 4.4 5.5";

  int our_result = s21_sscanf(input, "%f %*f %*f %*f %*f", &our_f);
  int std_result = sscanf(input, "%f %*f %*f %*f %*f", &std_f);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f %*f %f %*f %*f");
  printf("  Our: result = %d, value = %f\n", our_result, our_f);
  printf("  Std: result = %d, value = %f\n", std_result, std_f);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f - std_f) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_78_float_all_skipped) {
  printf("Test 78: %%f all skipped\n");

  const char *input = "1.0 2.0 3.0";

  int our_result = s21_sscanf(input, "%*f %*f %*f");
  int std_result = sscanf(input, "%*f %*f %*f");

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%*f %*f %*f");
  printf("  Our: result = %d\n", our_result);
  printf("  Std: result = %d\n", std_result);

  ck_assert_int_eq(our_result, std_result);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_79_float_short_input) {
  printf("Test 79: %%f short input\n");

  float our_f1 = 0.0f, our_f2 = 0.0f;
  float std_f1 = 0.0f, std_f2 = 0.0f;
  const char *input = "1.5";

  int our_result = s21_sscanf(input, "%f %f", &our_f1, &our_f2);
  int std_result = sscanf(input, "%f %f", &std_f1, &std_f2);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f %f");
  printf("  Our: result = %d, values = [%f, %f]\n", our_result, our_f1, our_f2);
  printf("  Std: result = %d, values = [%f, %f]\n", std_result, std_f1, std_f2);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f1 - std_f1) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_80_float_partial_match) {
  printf("Test 80: %%f partial match\n");

  float our_f1 = 0.0f, our_f2 = 0.0f, our_f3 = 0.0f;
  float std_f1 = 0.0f, std_f2 = 0.0f, std_f3 = 0.0f;
  const char *input = "12.34 abc 56.78";

  int our_result = s21_sscanf(input, "%f %f %f", &our_f1, &our_f2, &our_f3);
  int std_result = sscanf(input, "%f %f %f", &std_f1, &std_f2, &std_f3);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f %f %f");
  printf("  Our: result = %d, values = [%f, %f, %f]\n", our_result, our_f1,
         our_f2, our_f3);
  printf("  Std: result = %d, values = [%f, %f, %f]\n", std_result, std_f1,
         std_f2, std_f3);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f1 - std_f1) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_81_float_exponent_edge) {
  printf("Test 81: %%e exponent edge cases\n");

  float our_f1 = 0.0f, our_f2 = 0.0f, our_f3 = 0.0f;
  float std_f1 = 0.0f, std_f2 = 0.0f, std_f3 = 0.0f;
  const char *input = "1e0 1e+0 1e-0";

  int our_result = s21_sscanf(input, "%e %e %e", &our_f1, &our_f2, &our_f3);
  int std_result = sscanf(input, "%e %e %e", &std_f1, &std_f2, &std_f3);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%e %e %e");
  printf("  Our: result = %d, values = [%g, %g, %g]\n", our_result, our_f1,
         our_f2, our_f3);
  printf("  Std: result = %d, values = [%g, %g, %g]\n", std_result, std_f1,
         std_f2, std_f3);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f1 - std_f1) < 1e-6);
    ck_assert(fabs(our_f2 - std_f2) < 1e-6);
    ck_assert(fabs(our_f3 - std_f3) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_82_float_whitespace) {
  printf("Test 82: %%f with various whitespace\n");

  float our_f1 = 0.0f, our_f2 = 0.0f;
  float std_f1 = 0.0f, std_f2 = 0.0f;
  const char *input = "   12.5   \t   \n   34.6   ";

  int our_result = s21_sscanf(input, "%f %f", &our_f1, &our_f2);
  int std_result = sscanf(input, "%f %f", &std_f1, &std_f2);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f %f");
  printf("  Our: result = %d, values = [%f, %f]\n", our_result, our_f1, our_f2);
  printf("  Std: result = %d, values = [%f, %f]\n", std_result, std_f1, std_f2);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_f1 - std_f1) < 1e-6);
    ck_assert(fabs(our_f2 - std_f2) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_83_float_only_sign) {
  printf("Test 83: %%f only sign\n");

  float our_val = 0.0f, std_val = 0.0f;
  const char *input1 = "+";
  const char *input2 = "-";

  int our_result1 = s21_sscanf(input1, "%f", &our_val);
  int our_result2 = s21_sscanf(input2, "%f", &our_val);

  int std_result1 = sscanf(input1, "%f", &std_val);
  int std_result2 = sscanf(input2, "%f", &std_val);

  printf("  Input1: '%s'\n", input1);
  printf("  Input2: '%s'\n", input2);
  printf("  Format: '%s'\n", "%f");
  printf("  '+': Our=%d, Std=%d\n", our_result1, std_result1);
  printf("  '-': Our=%d, Std=%d\n", our_result2, std_result2);

  ck_assert_int_eq(our_result1, std_result1);
  ck_assert_int_eq(our_result2, std_result2);
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_84_char_modifiers) {
  printf("Test 84: %%c and %%lc modifiers\n");

  char our_c = 0, std_c = 0;
  int our_lc = 0;
  const char *input = "A";

  int our_result1 = s21_sscanf(input, "%c", &our_c);
  int std_result1 = sscanf(input, "%c", &std_c);

  int our_result2 = s21_sscanf(input, "%lc", &our_lc);

  printf("  Input: '%s'\n", input);
  printf("  Format '%%c':   Our=%d, value='%c' (%d), Std=%d, value='%c'\n",
         our_result1, our_c, (int)our_c, std_result1, std_c);
  printf("  Format '%%lc':  Our=%d, value=%d ('%c')\n", our_result2, our_lc,
         (char)our_lc);

  ck_assert_int_eq(our_result1, std_result1);
  ck_assert_int_eq(our_result2, 1);
  if (our_result1 > 0) {
    ck_assert_int_eq(our_c, 'A');
  }
  if (our_result2 > 0) {
    ck_assert_int_eq(our_lc, 'A');
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_85_string_modifiers) {
  printf("Test 85: %%s and %%ls modifiers\n");

  char our_s[20] = {0}, std_s[20] = {0};
  int our_ls[20] = {0};
  const char *input = "Hello";

  int our_result1 = s21_sscanf(input, "%s", our_s);
  int std_result1 = sscanf(input, "%s", std_s);

  int our_result2 = s21_sscanf(input, "%ls", our_ls);

  printf("  Input: '%s'\n", input);
  printf("  Format '%%s':   Our=%d, value='%s', Std=%d, value='%s'\n",
         our_result1, our_s, std_result1, std_s);

  printf("  Format '%%ls':  Our=%d, value as ints: [", our_result2);
  for (int i = 0; i < 5 && our_ls[i] != 0; i++) {
    printf("%d('%c') ", our_ls[i], (char)our_ls[i]);
  }
  printf("]\n");

  ck_assert_int_eq(our_result1, std_result1);
  ck_assert_int_eq(our_result2, 1);

  if (our_result1 > 0) {
    ck_assert_str_eq(our_s, std_s);
  }

  if (our_result2 > 0) {
    ck_assert_int_eq(our_ls[0], 'H');
    ck_assert_int_eq(our_ls[1], 'e');
    ck_assert_int_eq(our_ls[2], 'l');
    ck_assert_int_eq(our_ls[3], 'l');
    ck_assert_int_eq(our_ls[4], 'o');
    ck_assert_int_eq(our_ls[5], 0);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_86_mixed_with_wide) {
  printf("Test 86: mixed with wide strings\n");

  int our_i = 0;
  int our_ls[20] = {0};
  float our_f = 0.0f;
  const char *input = "42 Hello 3.14";

  int our_result = s21_sscanf(input, "%d %ls %f", &our_i, our_ls, &our_f);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%%d %%ls %%f'\n");
  printf("  Our: result=%d, values=[%d, ", our_result, our_i);

  printf("\"");
  for (int i = 0; our_ls[i] != 0; i++) {
    printf("%c", (char)our_ls[i]);
  }
  printf("\", %.2f]\n", our_f);

  ck_assert_int_eq(our_result, 3);
  if (our_result > 0) {
    ck_assert_int_eq(our_i, 42);
    ck_assert_int_eq(our_ls[0], 'H');
    ck_assert_int_eq(our_ls[1], 'e');
    ck_assert_int_eq(our_ls[2], 'l');
    ck_assert_int_eq(our_ls[3], 'l');
    ck_assert_int_eq(our_ls[4], 'o');
    ck_assert(fabs(our_f - 3.14f) < 0.01f);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_87_complex_hex_octal_skip) {
  printf("Test 87: complex hex/octal with skip\n");

  unsigned int our_hex = 0, std_hex = 0;
  unsigned long our_octal = 0, std_octal = 0;
  int our_n = 0, std_n = 0;
  const char *input = "Data: Hello 0xFF 777 25";

  int our_result =
      s21_sscanf(input, "Data: %*s 0x%x %lo %n", &our_hex, &our_octal, &our_n);
  int std_result =
      sscanf(input, "Data: %*s 0x%x %lo %n", &std_hex, &std_octal, &std_n);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "Data: %*s 0x%x %lo %n");
  printf("  Our: result = %d, values = [0x%x, %lo, n=%d]\n", our_result,
         our_hex, our_octal, our_n);
  printf("  Std: result = %d, values = [0x%x, %lo, n=%d]\n", std_result,
         std_hex, std_octal, std_n);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_uint_eq(our_hex, std_hex);
    ck_assert_uint_eq(our_octal, std_octal);
    ck_assert_int_eq(our_n, std_n);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_88_date_time_fixed_width) {
  printf("Test 88: date/time with fixed width\n");

  unsigned int our_day = 0, our_month = 0, our_year = 0, our_hour = 0,
               our_minute = 0;
  unsigned int std_day = 0, std_month = 0, std_year = 0, std_hour = 0,
               std_minute = 0;
  const char *input = "25/12/2023 15:30";

  int our_result = s21_sscanf(input, "%2u/%2u/%4u %*c %2u:%2u", &our_day,
                              &our_month, &our_year, &our_hour, &our_minute);
  int std_result = sscanf(input, "%2u/%2u/%4u %*c %2u:%2u", &std_day,
                          &std_month, &std_year, &std_hour, &std_minute);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%2u/%2u/%4u %*c %2u:%2u");
  printf("  Our: result = %d, values = [%02u/%02u/%04u %02u:%02u]\n",
         our_result, our_day, our_month, our_year, our_hour, our_minute);
  printf("  Std: result = %d, values = [%02u/%02u/%04u %02u:%02u]\n",
         std_result, std_day, std_month, std_year, std_hour, std_minute);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_uint_eq(our_day, std_day);
    ck_assert_uint_eq(our_month, std_month);
    ck_assert_uint_eq(our_year, std_year);
    ck_assert_uint_eq(our_hour, std_hour);
    ck_assert_uint_eq(our_minute, std_minute);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_89_ip_address_extraction) {
  printf("Test 89: IP address extraction\n");

  unsigned int our_a = 0, our_b = 0, our_c = 0, our_d = 0;
  int our_n = 0, std_n = 0;
  unsigned int std_a = 0, std_b = 0, std_c = 0, std_d = 0;

  const char *input = "192.168.1.1 connected 42";

  int our_result = s21_sscanf(input, "%u.%u.%u.%u %*s %n", &our_a, &our_b,
                              &our_c, &our_d, &our_n);
  int std_result = sscanf(input, "%u.%u.%u.%u %*s %n", &std_a, &std_b, &std_c,
                          &std_d, &std_n);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%u.%u.%u.%u %*s %n");
  printf("  Our: result = %d, values = [%u.%u.%u.%u, n=%d]\n", our_result,
         our_a, our_b, our_c, our_d, our_n);
  printf("  Std: result = %d, values = [%u.%u.%u.%u, n=%d]\n", std_result,
         std_a, std_b, std_c, std_d, std_n);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_uint_eq(our_a, std_a);
    ck_assert_uint_eq(our_b, std_b);
    ck_assert_uint_eq(our_c, std_c);
    ck_assert_uint_eq(our_d, std_d);
    ck_assert_int_eq(our_n, std_n);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_90_mixed_types_with_length) {
  printf("Test 90: mixed types with length modifiers\n");

  unsigned int our_id = 0, our_hex1 = 0, our_hex2 = 0;
  unsigned int std_id = 0, std_hex1 = 0, std_hex2 = 0;
  const char *input = "ID:12345 ABC 3.14 ff";

  int our_result =
      s21_sscanf(input, "ID:%5u %X %*f %x", &our_id, &our_hex1, &our_hex2);
  int std_result =
      sscanf(input, "ID:%5u %X %*f %x", &std_id, &std_hex1, &std_hex2);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "ID:%5u %X %*f %x");
  printf("  Our: result = %d, values = [ID:%u, 0x%X, 0x%x]\n", our_result,
         our_id, our_hex1, our_hex2);
  printf("  Std: result = %d, values = [ID:%u, 0x%X, 0x%x]\n", std_result,
         std_id, std_hex1, std_hex2);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_uint_eq(our_id, std_id);
    ck_assert_uint_eq(our_hex1, std_hex1);
    ck_assert_uint_eq(our_hex2, std_hex2);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_91_coordinates_with_text) {
  printf("Test 91: coordinates with text\n");

  float our_x = 0.0f, our_y = 0.0f;
  long our_dist = 0;
  float std_x = 0.0f, std_y = 0.0f;
  long std_dist = 0;
  const char *input = "X=12.5 Y=34.7 random Dist=1000";

  int our_result =
      s21_sscanf(input, "X=%f Y=%f %*s Dist=%ld", &our_x, &our_y, &our_dist);
  int std_result =
      sscanf(input, "X=%f Y=%f %*s Dist=%ld", &std_x, &std_y, &std_dist);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "X=%f Y=%f %*s Dist=%ld");
  printf("  Our: result = %d, values = [X=%.1f, Y=%.1f, Dist=%ld]\n",
         our_result, our_x, our_y, our_dist);
  printf("  Std: result = %d, values = [X=%.1f, Y=%.1f, Dist=%ld]\n",
         std_result, std_x, std_y, std_dist);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_x - std_x) < 1e-6);
    ck_assert(fabs(our_y - std_y) < 1e-6);
    ck_assert_int_eq(our_dist, std_dist);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_92_system_parameters) {
  printf("Test 92: system parameters\n");

  unsigned int our_cpu = 0, our_val = 0;
  unsigned int std_cpu = 0, std_val = 0;
  int our_n = 0, std_n = 0;
  const char *input = "CPU:75% Idle:25 42 done";

  int our_result =
      s21_sscanf(input, "CPU:%u%% Idle:%*u %u %n", &our_cpu, &our_val, &our_n);
  int std_result =
      sscanf(input, "CPU:%u%% Idle:%*u %u %n", &std_cpu, &std_val, &std_n);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "CPU:%u%% Idle:%*u %u %n");
  printf("  Our: result = %d, values = [CPU:%u%%, Val=%u, n=%d]\n", our_result,
         our_cpu, our_val, our_n);
  printf("  Std: result = %d, values = [CPU:%u%%, Val=%u, n=%d]\n", std_result,
         std_cpu, std_val, std_n);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_uint_eq(our_cpu, std_cpu);
    ck_assert_uint_eq(our_val, std_val);
    ck_assert_int_eq(our_n, std_n);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_93_version_with_prefixes) {
  printf("Test 93: version with prefixes\n");

  unsigned short our_major = 0, our_minor = 0;
  unsigned long our_hex = 0;
  unsigned short std_major = 0, std_minor = 0;
  unsigned long std_hex = 0;
  const char *input = "ver 1.2 A DEADBEEF";

  int our_result = s21_sscanf(input, "ver %hu.%hu %*c %lx", &our_major,
                              &our_minor, &our_hex);
  int std_result =
      sscanf(input, "ver %hu.%hu %*c %lx", &std_major, &std_minor, &std_hex);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "ver %hu.%hu %*c %lx");
  printf("  Our: result = %d, values = [ver %hu.%hu, 0x%lx]\n", our_result,
         our_major, our_minor, our_hex);
  printf("  Std: result = %d, values = [ver %hu.%hu, 0x%lx]\n", std_result,
         std_major, std_minor, std_hex);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_uint_eq(our_major, std_major);
    ck_assert_uint_eq(our_minor, std_minor);
    ck_assert_uint_eq(our_hex, std_hex);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_94_log_parsing_with_skips) {
  printf("Test 94: log parsing with skips\n");

  int our_a = 0, our_b = 0;
  char our_str[10] = {0};
  float our_val = 0.0f;
  int std_a = 0, std_b = 0;
  char std_str[10] = {0};
  float std_val = 0.0f;
  const char *input = "2023-12-25 ERROR 3.14";

  int our_result =
      s21_sscanf(input, "%d-%d-%*d %5s %f", &our_a, &our_b, our_str, &our_val);
  int std_result =
      sscanf(input, "%d-%d-%*d %5s %f", &std_a, &std_b, std_str, &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%d-%d-%*d %5s %f");
  printf("  Our: result = %d, values = [%d-%d, '%s', %.2f]\n", our_result,
         our_a, our_b, our_str, our_val);
  printf("  Std: result = %d, values = [%d-%d, '%s', %.2f]\n", std_result,
         std_a, std_b, std_str, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_int_eq(our_a, std_a);
    ck_assert_int_eq(our_b, std_b);
    ck_assert_str_eq(our_str, std_str);
    ck_assert(fabs(our_val - std_val) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_95_pointers_and_sizes) {
  printf("Test 95: pointers and sizes\n");

  void *our_ptr = NULL;
  long long our_val = 0;
  void *std_ptr = NULL;
  long long std_val = 0;
  const char *input = "ptr: 0x7ffeeb39c920 42 1234567890";

  int our_result = s21_sscanf(input, "ptr: %p %*u %lli", &our_ptr, &our_val);
  int std_result = sscanf(input, "ptr: %p %*u %lli", &std_ptr, &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "ptr: %p %*u %lli");
  printf("  Our: result = %d, values = [ptr=%p, val=%lld]\n", our_result,
         our_ptr, our_val);
  printf("  Std: result = %d, values = [ptr=%p, val=%lld]\n", std_result,
         std_ptr, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_ptr_eq(our_ptr, std_ptr);
    ck_assert_int_eq(our_val, std_val);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_96_fixed_text_blocks) {
  printf("Test 96: fixed text blocks\n");

  char our_method[20] = {0};
  unsigned int our_code = 0;
  char std_method[20] = {0};
  unsigned int std_code = 0;
  const char *input = "GET /index.html HTTP/1.1 200";

  int our_result =
      s21_sscanf(input, "GET %10s HTTP/%*f %u", our_method, &our_code);
  int std_result = sscanf(input, "GET %10s HTTP/%*f %u", std_method, &std_code);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "GET %10s HTTP/%*f %u");
  printf("  Our: result = %d, values = [GET '%s', Code=%u]\n", our_result,
         our_method, our_code);
  printf("  Std: result = %d, values = [GET '%s', Code=%u]\n", std_result,
         std_method, std_code);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_str_eq(our_method, std_method);
    ck_assert_uint_eq(our_code, std_code);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_97_physical_quantities) {
  printf("Test 97: physical quantities\n");

  float our_val1 = 0.0f, our_val2 = 0.0f;
  char our_unit[10] = {0};
  int our_n = 0;
  float std_val1 = 0.0f, std_val2 = 0.0f;
  char std_unit[10] = {0};
  int std_n = 0;
  const char *input = "12.5m 3.14km 42";

  int our_result = s21_sscanf(input, "%f%*s %f%s %n", &our_val1, &our_val2,
                              our_unit, &our_n);
  int std_result =
      sscanf(input, "%f%*s %f%s %n", &std_val1, &std_val2, std_unit, &std_n);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%f%*s %f%s %n");
  printf("  Our: result = %d, values = [%.1f, %.2f'%s', n=%d]\n", our_result,
         our_val1, our_val2, our_unit, our_n);
  printf("  Std: result = %d, values = [%.1f, %.2f'%s', n=%d]\n", std_result,
         std_val1, std_val2, std_unit, std_n);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert(fabs(our_val1 - std_val1) < 1e-6);
    ck_assert(fabs(our_val2 - std_val2) < 1e-6);
    ck_assert_str_eq(our_unit, std_unit);
    ck_assert_int_eq(our_n, std_n);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_98_complex_skip_and_hex_packets) {
  printf("Test 98: complex skip and hex packets\n");

  unsigned int our_hex = 0, our_val = 0;
  unsigned int std_hex = 0, std_val = 0;
  const char *input = "FF:AA:BB packet 123";

  int our_result = s21_sscanf(input, "%*x:%*x:%x %*s %u", &our_hex, &our_val);
  int std_result = sscanf(input, "%*x:%*x:%x %*s %u", &std_hex, &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%*x:%*x:%x %*s %u");
  printf("  Our: result = %d, values = [0x%x, %u]\n", our_result, our_hex,
         our_val);
  printf("  Std: result = %d, values = [0x%x, %u]\n", std_result, std_hex,
         std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_uint_eq(our_hex, std_hex);
    ck_assert_uint_eq(our_val, std_val);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_99_error_code_and_position) {
  printf("Test 99: error code and position\n");

  int our_err = 0;
  float our_val = 0.0f;
  int std_err = 0;
  float std_val = 0.0f;
  const char *input = "Error #  123 ( 0xFF ) 3.14";

  int our_result =
      s21_sscanf(input, "Error #%5d ( %*x ) %f", &our_err, &our_val);
  int std_result = sscanf(input, "Error #%5d ( %*x ) %f", &std_err, &std_val);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "Error #%5d ( %*x ) %f");
  printf("  Our: result = %d, values = [Error #%d, %.2f]\n", our_result,
         our_err, our_val);
  printf("  Std: result = %d, values = [Error #%d, %.2f]\n", std_result,
         std_err, std_val);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_int_eq(our_err, std_err);
    ck_assert(fabs(our_val - std_val) < 1e-6);
  }
  printf("Test passed!\n\n");
}
END_TEST

START_TEST(test_100_scalable_values) {
  printf("Test 100: scalable values\n");

  long our_long = 0;
  unsigned int our_octal = 0, our_hex = 0;
  long std_long = 0;
  unsigned int std_octal = 0, std_hex = 0;
  const char *input = "1000 0xFF 777 DEAD";

  int our_result =
      s21_sscanf(input, "%ld %*i %4o %X", &our_long, &our_octal, &our_hex);
  int std_result =
      sscanf(input, "%ld %*i %4o %X", &std_long, &std_octal, &std_hex);

  printf("  Input: '%s'\n", input);
  printf("  Format: '%s'\n", "%ld %*i %4o %X");
  printf("  Our: result = %d, values = [%ld, %o, 0x%X]\n", our_result, our_long,
         our_octal, our_hex);
  printf("  Std: result = %d, values = [%ld, %o, 0x%X]\n", std_result, std_long,
         std_octal, std_hex);

  ck_assert_int_eq(our_result, std_result);
  if (our_result > 0) {
    ck_assert_int_eq(our_long, std_long);
    ck_assert_uint_eq(our_octal, std_octal);
    ck_assert_uint_eq(our_hex, std_hex);
  }
  printf("Test passed!\n\n");
}
END_TEST

Suite *sscanf_suite(void) {
  Suite *s = suite_create("sscanf");

  TCase *tc_basic = tcase_create("Basic");
  TCase *tc_char = tcase_create("Char");
  TCase *tc_string = tcase_create("String");
  TCase *tc_decimal = tcase_create("Decimal");
  TCase *tc_unsigned = tcase_create("Unsigned");
  TCase *tc_octal = tcase_create("Octal");
  TCase *tc_hexadecimal = tcase_create("Hexadecimal");
  TCase *tc_integer = tcase_create("Integer");
  TCase *tc_number = tcase_create("Number");
  TCase *tc_pointer = tcase_create("Pointer");
  TCase *tc_float = tcase_create("Float");
  TCase *tc_modifier = tcase_create("Modifier");
  TCase *tc_complex = tcase_create("Complex");

  tcase_add_test(tc_basic, test_1_basic_literal_match);
  tcase_add_test(tc_basic, test_2_percent_literal);
  tcase_add_test(tc_basic, test_3_empty_string);
  tcase_add_test(tc_basic, test_4_mismatch);
  tcase_add_test(tc_basic, test_5_partial_match);
  tcase_add_test(tc_basic, test_6_null_pointer);

  tcase_add_test(tc_char, test_7_char_basic);
  tcase_add_test(tc_char, test_8_char_space);
  tcase_add_test(tc_char, test_9_char_skip);

  tcase_add_test(tc_string, test_10_string_basic);
  tcase_add_test(tc_string, test_11_string_multiple);
  tcase_add_test(tc_string, test_12_string_with_skip);
  tcase_add_test(tc_string, test_13_string_empty);
  tcase_add_test(tc_string, test_14_string_only_spaces);
  tcase_add_test(tc_string, test_15_string_mixed_with_char);
  tcase_add_test(tc_string, test_16_sscanf_empty_string);

  tcase_add_test(tc_decimal, test_17_int_basic);
  tcase_add_test(tc_decimal, test_18_int_negative);
  tcase_add_test(tc_decimal, test_19_int_with_spaces);
  tcase_add_test(tc_decimal, test_20_int_skip);
  tcase_add_test(tc_decimal, test_21_int_no_number);

  tcase_add_test(tc_unsigned, test_22_uint_basic);
  tcase_add_test(tc_unsigned, test_23_uint_large);
  tcase_add_test(tc_unsigned, test_24_uint_with_sign);

  tcase_add_test(tc_octal, test_25_octal_basic);
  tcase_add_test(tc_octal, test_26_octal_with_zero_prefix);
  tcase_add_test(tc_octal, test_27_octal_large);
  tcase_add_test(tc_octal, test_28_octal_invalid);

  tcase_add_test(tc_hexadecimal, test_29_hex_basic);
  tcase_add_test(tc_hexadecimal, test_30_hex_uppercase);
  tcase_add_test(tc_hexadecimal, test_31_hex_with_prefix);
  tcase_add_test(tc_hexadecimal, test_32_hex_mixed_case);

  tcase_add_test(tc_integer, test_33_i_decimal);
  tcase_add_test(tc_integer, test_34_i_octal);
  tcase_add_test(tc_integer, test_35_i_hex);
  tcase_add_test(tc_integer, test_36_i_negative);
  tcase_add_test(tc_integer, test_37_i_negative_octal);

  tcase_add_test(tc_number, test_38_n_basic);
  tcase_add_test(tc_number, test_39_n_middle);
  tcase_add_test(tc_number, test_40_n_with_skip);
  tcase_add_test(tc_number, test_41_multiple_specifiers_in_row);
  tcase_add_test(tc_number, test_42_n_at_beginning);
  tcase_add_test(tc_number, test_43_n_with_multiple_values);
  tcase_add_test(tc_number, test_44_n_with_skip_and_spaces);
  tcase_add_test(tc_number, test_45_n_empty_string);

  tcase_add_test(tc_pointer, test_46_pointer_basic);
  tcase_add_test(tc_pointer, test_47_pointer_no_prefix);
  tcase_add_test(tc_pointer, test_48_pointer_null);
  tcase_add_test(tc_pointer, test_49_pointer_with_other_specifiers);
  tcase_add_test(tc_pointer, test_50_pointer_complex);
  tcase_add_test(tc_pointer, test_51_pointer_edge_cases);
  tcase_add_test(tc_pointer, test_52_pointer_empty_string);

  tcase_add_test(tc_float, test_53_float_basic);
  tcase_add_test(tc_float, test_54_float_integer);
  tcase_add_test(tc_float, test_55_float_fraction_only);
  tcase_add_test(tc_float, test_56_float_negative);
  tcase_add_test(tc_float, test_57_float_empty_string);
  tcase_add_test(tc_float, test_58_float_only_spaces);
  tcase_add_test(tc_float, test_59_float_dot_only);
  tcase_add_test(tc_float, test_60_float_sign_only);
  tcase_add_test(tc_float, test_61_float_very_small);
  tcase_add_test(tc_float, test_62_float_with_others);
  tcase_add_test(tc_float, test_63_float_scientific_positive);
  tcase_add_test(tc_float, test_64_float_scientific_negative);
  tcase_add_test(tc_float, test_65_float_scientific_uppercase);
  tcase_add_test(tc_float, test_66_float_scientific_no_sign);
  tcase_add_test(tc_float, test_67_float_specifiers);
  tcase_add_test(tc_float, test_68_float_with_skip);
  tcase_add_test(tc_float, test_69_float_signs);
  tcase_add_test(tc_float, test_70_float_exponential);
  tcase_add_test(tc_float, test_71_float_edge_cases);
  tcase_add_test(tc_float, test_72_float_empty_mismatch);
  tcase_add_test(tc_float, test_73_float_length_modifiers);
  tcase_add_test(tc_float, test_74_float_mixed_types);
  tcase_add_test(tc_float, test_75_float_g_G);
  tcase_add_test(tc_float, test_76_float_extreme_values);
  tcase_add_test(tc_float, test_77_float_multiple_skips);
  tcase_add_test(tc_float, test_78_float_all_skipped);
  tcase_add_test(tc_float, test_79_float_short_input);
  tcase_add_test(tc_float, test_80_float_partial_match);
  tcase_add_test(tc_float, test_81_float_exponent_edge);
  tcase_add_test(tc_float, test_82_float_whitespace);
  tcase_add_test(tc_float, test_83_float_only_sign);

  tcase_add_test(tc_modifier, test_84_char_modifiers);
  tcase_add_test(tc_modifier, test_85_string_modifiers);
  tcase_add_test(tc_modifier, test_86_mixed_with_wide);

  tcase_add_test(tc_complex, test_87_complex_hex_octal_skip);
  tcase_add_test(tc_complex, test_88_date_time_fixed_width);
  tcase_add_test(tc_complex, test_89_ip_address_extraction);
  tcase_add_test(tc_complex, test_90_mixed_types_with_length);
  tcase_add_test(tc_complex, test_91_coordinates_with_text);
  tcase_add_test(tc_complex, test_92_system_parameters);
  tcase_add_test(tc_complex, test_93_version_with_prefixes);
  tcase_add_test(tc_complex, test_94_log_parsing_with_skips);
  tcase_add_test(tc_complex, test_95_pointers_and_sizes);
  tcase_add_test(tc_complex, test_96_fixed_text_blocks);
  tcase_add_test(tc_complex, test_97_physical_quantities);
  tcase_add_test(tc_complex, test_98_complex_skip_and_hex_packets);
  tcase_add_test(tc_complex, test_99_error_code_and_position);
  tcase_add_test(tc_complex, test_100_scalable_values);

  suite_add_tcase(s, tc_basic);
  suite_add_tcase(s, tc_char);
  suite_add_tcase(s, tc_string);
  suite_add_tcase(s, tc_decimal);
  suite_add_tcase(s, tc_unsigned);
  suite_add_tcase(s, tc_octal);
  suite_add_tcase(s, tc_hexadecimal);
  suite_add_tcase(s, tc_integer);
  suite_add_tcase(s, tc_number);
  suite_add_tcase(s, tc_pointer);
  suite_add_tcase(s, tc_float);
  suite_add_tcase(s, tc_modifier);
  suite_add_tcase(s, tc_complex);
  return s;
}

int main(void) {
  Suite *s = sscanf_suite();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? 0 : 1;
}