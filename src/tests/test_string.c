#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strchr) {
  const char *str = "Lindsyis";
  int c = 's';
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_strchr_not_found) {
  const char *str = "Lindsyis";
  int c = 'I';
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_strchr_null) {
  const char *str = "Lindsyis";
  int c = '\0';
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_strchr_empty) {
  const char *str = "";
  int c = 'A';
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_strchr_empty_null) {
  const char *str = "";
  int c = '\0';
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_strstr) {
  const char *haystack = "Lolik hahaha";
  const char *needle = "hahaha";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_not_found) {
  const char *haystack = "Lolik hahaha";
  const char *needle = "hehehe";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  const char *haystack = "Lolik hahaha";
  const char *needle = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_long_needle) {
  const char *haystack = "Lol";
  const char *needle = "Lolik";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_empty_haystack) {
  const char *haystack = "";
  const char *needle = "lol";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_both_empty) {
  const char *haystack = "";
  const char *needle = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strncmp_same) {
  const char *s1 = "Lolik";
  const char *s2 = "Lolik";
  s21_size_t n = 5;
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
}
END_TEST

START_TEST(test_strncmp_diff) {
  const char *s1 = "Bolik";
  const char *s2 = "Lolik";
  s21_size_t n = 5;
  ck_assert_int_lt(s21_strncmp(s1, s2, n), 0);
}
END_TEST

START_TEST(test_strncmp_cut) {
  const char *s1 = "Lolik";
  const char *s2 = "Lolim";
  s21_size_t n = 4;
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
}
END_TEST

START_TEST(test_strncmp_empty) {
  const char *s1 = "";
  const char *s2 = "";
  s21_size_t n = 1;
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
}
END_TEST

START_TEST(test_strncmp_short) {
  const char *s1 = "Lol";
  const char *s2 = "Lolik";
  s21_size_t n = 3;
  ck_assert_int_eq(s21_strncmp(s1, s2, n), 0);
}
END_TEST

START_TEST(test_strncat) {
  char s1[30] = "Lolik";
  char s2[30] = "Lolik";
  const char *src = " hahaha";
  s21_size_t n = 7;
  s21_strncat(s1, src, n);
  strncat(s2, src, n);

  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strncat_cut) {
  char s1[30] = "Lolik";
  char s2[30] = "Lolik";
  const char *src = " hahaha";
  s21_size_t n = 3;
  s21_strncat(s1, src, n);
  strncat(s2, src, n);

  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strncat_empty_src) {
  char s1[30] = "Lolik";
  char s2[30] = "Lolik";
  const char *src = "";
  s21_size_t n = 5;
  s21_strncat(s1, src, n);
  strncat(s2, src, n);

  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strncat_empty_dest) {
  char s1[30] = "";
  char s2[30] = "";
  const char *src = "Lolik";
  s21_size_t n = 5;
  s21_strncat(s1, src, n);
  strncat(s2, src, n);

  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strncat_zero_n) {
  char s1[30] = "Lolik";
  char s2[30] = "Lolik";
  const char *src = " hahaha";
  s21_strncat(s1, src, 0);
  strncat(s2, src, 0);

  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strncpy) {
  char s1[20] = "1234567890";
  char s2[20] = "1234567890";
  const char *src = "Lolik";
  s21_size_t n = 8;
  s21_strncpy(s1, src, n);
  strncpy(s2, src, n);

  ck_assert_mem_eq(s1, s2, n);
}
END_TEST

START_TEST(test_strncpy_cut) {
  char s1[20] = "";
  char s2[20] = "";
  const char *src = "Lolik hahaha";
  s21_size_t n = 5;

  s21_strncpy(s1, src, n);
  strncpy(s2, src, n);

  ck_assert_mem_eq(s1, s2, n);
}
END_TEST

START_TEST(test_strncpy_empty) {
  char s1[10] = "lol";
  char s2[10] = "lol";
  const char *src = "";
  s21_size_t n = 3;

  s21_strncpy(s1, src, n);
  strncpy(s2, src, n);

  ck_assert_mem_eq(s1, s2, n);
}
END_TEST

START_TEST(test_strncpy_zero) {
  char s1[10] = "lol";
  char s2[10] = "lol";
  const char *src = "hah";
  s21_size_t n = 0;

  s21_strncpy(s1, src, n);
  strncpy(s2, src, n);

  ck_assert_mem_eq(s1, s2, 10);
}
END_TEST

START_TEST(test_strrchr) {
  const char *str = "Lolik";
  ck_assert_ptr_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));
}
END_TEST

START_TEST(test_strrchr_multi) {
  const char *str = "lolhahalolhahalol";
  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
}
END_TEST

START_TEST(test_strrchr_not_found) {
  const char *str = "Lolik";
  ck_assert_ptr_eq(s21_strrchr(str, 'Z'), strrchr(str, 'Z'));
}
END_TEST

START_TEST(test_strrchr_null) {
  const char *str = "Lol";
  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

START_TEST(test_strrchr_empty) {
  const char *str = "";
  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

START_TEST(test_memcpy_char) {
  char src[] = "Lolik";
  char my[20] = {0};
  char orig[20] = {0};
  s21_size_t n = 5;

  s21_memcpy(my, src, n);
  memcpy(orig, src, n);

  ck_assert_mem_eq(my, orig, 20);
}
END_TEST

START_TEST(test_memcpy_arr) {
  char src[] = {1, 2, 3, 4, 5};
  char my[5] = {0};
  char orig[5] = {0};

  s21_memcpy(my, src, sizeof(src));
  memcpy(orig, src, sizeof(src));

  ck_assert_mem_eq(my, orig, sizeof(src));
}
END_TEST

START_TEST(test_memcpy_empty_src) {
  char src[] = "";
  char my[10] = "Lolik";
  char orig[10] = "Lolik";

  s21_memcpy(my, src, 1);
  memcpy(orig, src, 1);

  ck_assert_mem_eq(my, orig, 10);
}
END_TEST

START_TEST(test_memcpy_rewrite) {
  char src[] = "123";
  char my[10] = "asdfgh";
  char orig[10] = "asdfgh";

  s21_memcpy(my, src, 3);
  memcpy(orig, src, 3);

  ck_assert_mem_eq(my, orig, 10);
}
END_TEST

START_TEST(test_memcpy_piece) {
  char src[] = "Hello World";
  char dest_my[20] = {0};
  char dest_std[20] = {0};

  s21_memcpy(dest_my, src, 4);
  memcpy(dest_std, src, 4);

  ck_assert_mem_eq(dest_my, dest_std, 20);
}
END_TEST

START_TEST(test_memset) {
  char my[20] = "Lolik hahaha";
  char orig[20] = "Lolik hahaha";

  s21_memset(my, 'z', 5);
  memset(orig, 'z', 5);

  ck_assert_mem_eq(my, orig, 20);
}
END_TEST

START_TEST(test_memset_zeros) {
  char my[10] = "123456789";
  char orig[10] = "123456789";

  s21_memset(my, 0, 10);
  memset(orig, 0, 10);

  ck_assert_mem_eq(my, orig, 10);
}
END_TEST

START_TEST(test_memset_part) {
  char my[10] = "asdfgh";
  char orig[10] = "asdfgh";

  s21_memset(my, '1', 3);
  memset(orig, '1', 3);

  ck_assert_mem_eq(my, orig, 10);
}
END_TEST

START_TEST(test_memset_empty) {
  char my[10] = "";
  char orig[10] = "";

  s21_memset(my, '0', 3);
  memset(orig, '0', 3);

  ck_assert_mem_eq(my, orig, 10);
}
END_TEST

START_TEST(test_memcmp) {
  char s1[] = "Lolik";
  char s2[] = "Lolik";
  s21_size_t n = 5;

  ck_assert_int_eq(s21_memcmp(s1, s2, n), memcmp(s1, s2, n));
}
END_TEST

START_TEST(test_memcmp_less) {
  char s1[] = "ABC";
  char s2[] = "ABD";
  s21_size_t n = 3;

  int my = s21_memcmp(s1, s2, n);
  int orig = memcmp(s1, s2, n);

  if (my < 0) {
    ck_assert_int_lt(orig, 0);
  } else if (my > 0) {
    ck_assert_int_gt(orig, 0);
  } else {
    ck_assert_int_eq(orig, 0);
  }
}
END_TEST

START_TEST(test_memcmp_greater) {
  char s1[] = "Zov";
  char s2[] = "Abc";
  s21_size_t n = 3;

  int my = s21_memcmp(s1, s2, n);
  int orig = memcmp(s1, s2, n);

  if (my < 0) {
    ck_assert_int_lt(orig, 0);
  } else if (my > 0) {
    ck_assert_int_gt(orig, 0);
  } else {
    ck_assert_int_eq(orig, 0);
  }
}
END_TEST

START_TEST(test_memcmp_int_array) {
  int a[] = {1, 2, 300};
  int b[] = {1, 2, 400};
  s21_size_t n = sizeof(a);

  int my = s21_memcmp(a, b, n);
  int orig = memcmp(a, b, n);

  if (my < 0) {
    ck_assert_int_lt(orig, 0);
  } else if (my > 0) {
    ck_assert_int_gt(orig, 0);
  } else {
    ck_assert_int_eq(orig, 0);
  }
}
END_TEST

START_TEST(test_memcmp_with_null) {
  char s1[] = "ABC\0A";
  char s2[] = "ABC\0Z";
  s21_size_t n = 5;

  int my = s21_memcmp(s1, s2, n);
  int orig = memcmp(s1, s2, n);

  if (my < 0) {
    ck_assert_int_lt(orig, 0);
  } else if (my > 0) {
    ck_assert_int_gt(orig, 0);
  } else {
    ck_assert_int_eq(orig, 0);
  }
}
END_TEST

START_TEST(test_memcmp_zeros) {
  char s1[10] = {0};
  char s2[10] = {0};
  s21_size_t n = 5;

  ck_assert_int_eq(s21_memcmp(s1, s2, n), memcmp(s1, s2, n));
}
END_TEST

START_TEST(test_memchr) {
  char str[] = "Lolik Hahaha";
  int c = 'H';
  s21_size_t n = 12;

  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_memchr_not_found) {
  char str[] = "Lolik";
  int c = 'Z';
  s21_size_t n = 5;

  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_memchr_null) {
  char str[] = "Lol";
  int c = '\0';
  s21_size_t n = 4;

  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_memchr_with_null) {
  char str[] = "A\0B";
  int c = 'B';
  s21_size_t n = 3;

  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_memchr_int_array) {
  int arr[] = {1, 2, 3, 4};
  int c = 3;
  s21_size_t n = sizeof(arr);

  ck_assert_ptr_eq(s21_memchr(arr, c, n), memchr(arr, c, n));
}
END_TEST

START_TEST(test_to_upper) {
  const char *str = "Lolik Hahaha";
  char *res = s21_to_upper(str);
  ck_assert_str_eq(res, "LOLIK HAHAHA");
  if (res != NULL) {
    free(res);
  }
}
END_TEST

START_TEST(test_to_upper_mix) {
  const char *str = "aSdFgH 123";
  char *res = s21_to_upper(str);
  ck_assert_str_eq(res, "ASDFGH 123");
  if (res != NULL) {
    free(res);
  }
}
END_TEST

START_TEST(test_to_upper_null) {
  char *res = s21_to_upper(NULL);
  ck_assert_ptr_eq(res, NULL);
  if (res != NULL) {
    free(res);
  }
}
END_TEST

START_TEST(test_to_upper_empty) {
  const char *str = "";
  char *res = s21_to_upper(str);
  ck_assert_str_eq(res, "");
  if (res != NULL) {
    free(res);
  }
}
END_TEST

START_TEST(test_to_lower) {
  const char *str = "LOLIK HAHAHA";
  char *res = s21_to_lower(str);
  ck_assert_str_eq(res, "lolik hahaha");
  if (res != NULL) {
    free(res);
  }
}
END_TEST

START_TEST(test_to_lower_mix) {
  const char *str = "AsDfGh 123";
  char *res = s21_to_lower(str);
  ck_assert_str_eq(res, "asdfgh 123");
  if (res != NULL) {
    free(res);
  }
}
END_TEST

START_TEST(test_to_lower_null) {
  char *res = s21_to_lower(NULL);
  ck_assert_ptr_eq(res, NULL);
  if (res != NULL) {
    free(res);
  }
}
END_TEST

START_TEST(test_to_lower_empty) {
  const char *str = "";
  char *res = s21_to_lower(str);
  ck_assert_str_eq(res, "");
  if (res != NULL) {
    free(res);
  }
}
END_TEST

START_TEST(test_strlen_basic) {
  const char *test_str1 = "Georgitw";
  ck_assert_int_eq(s21_strlen(test_str1), strlen(test_str1));
}
END_TEST

START_TEST(test_strlen_empty) {
  const char *test_str2 = "";
  ck_assert_int_eq(s21_strlen(test_str2), strlen(test_str2));
}
END_TEST

START_TEST(test_strlen_one_char) {
  const char *test_str3 = "G";
  ck_assert_int_eq(s21_strlen(test_str3), strlen(test_str3));
}
END_TEST

START_TEST(test_strlen_space) {
  const char *test_str4 = "There's a space here";
  ck_assert_int_eq(s21_strlen(test_str4), strlen(test_str4));
}
END_TEST

START_TEST(test_strlen_numbers) {
  const char *test_str5 = "1234567890";
  ck_assert_int_eq(s21_strlen(test_str5), strlen(test_str5));
}
END_TEST

START_TEST(test_strlen_escape) {
  const char *test_str6 = "he\x16llo\nwor\x7Fld\t!";
  ck_assert_int_eq(s21_strlen(test_str6), strlen(test_str6));
}
END_TEST

START_TEST(test_strlen_NULL) {
  const char *test_str7 = NULL;
  ck_assert_int_eq(s21_strlen(test_str7), 0);
}
END_TEST

START_TEST(test_strlen_long) {
  char test_str8[1001];
  for (int i = 0; i < 1000; i++) {
    test_str8[i] = 'x';
  }
  test_str8[1000] = '\0';
  ck_assert_int_eq(s21_strlen(test_str8), 1000);
}
END_TEST

START_TEST(test_strlen_spaces_only) {
  ck_assert_int_eq(s21_strlen("     "), 5);
}
END_TEST

START_TEST(test_s21_strerror) {
  ck_assert_str_eq(s21_strerror(1), strerror(1));
  ck_assert_str_eq(s21_strerror(0), strerror(0));
  ck_assert_str_eq(s21_strerror(-1), strerror(-1));
  ck_assert_str_eq(s21_strerror(-1), strerror(-1));
  ck_assert_str_eq(s21_strerror(12), strerror(12));
}
END_TEST

START_TEST(test_s21_strcspn) {
  char str1[] = "Hello World";
  char str2[] = " o";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));

  char str3[] = "xyz";
  ck_assert_int_eq(s21_strcspn(str1, str3), strcspn(str1, str3));

  char str4[] = "H";
  ck_assert_int_eq(s21_strcspn(str1, str4), strcspn(str1, str4));

  char empty[] = "";
  ck_assert_int_eq(s21_strcspn(empty, str2), strcspn(empty, str2));
  ck_assert_int_eq(s21_strcspn(str1, empty), strcspn(str1, empty));
}
END_TEST

START_TEST(test_s21_strpbrk) {
  char str1[] = "Hello World";
  char str2[] = "Wo";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));

  char str3[] = "zxy";
  ck_assert_ptr_eq(s21_strpbrk(str1, str3), strpbrk(str1, str3));

  char str4[] = "xH";
  ck_assert_ptr_eq(s21_strpbrk(str1, str4), strpbrk(str1, str4));

  char empty[] = "";
  ck_assert_ptr_eq(s21_strpbrk(empty, str2), strpbrk(empty, str2));
  ck_assert_ptr_eq(s21_strpbrk(str1, empty), strpbrk(str1, empty));
}
END_TEST

START_TEST(test_s21_strtok) {
  {
    char s1[] = "Test/string/split";
    char s2[] = "Test/string/split";
    char delim[] = "/";
    ck_assert_str_eq(s21_strtok(s1, delim), strtok(s2, delim));
    ck_assert_str_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
    ck_assert_str_eq(s21_strtok(NULL, delim), strtok(NULL, delim));

    ck_assert_ptr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  }

  {
    char s1[] = ",,Hello,,,World,,";
    char s2[] = ",,Hello,,,World,,";
    char delim[] = ",";

    ck_assert_str_eq(s21_strtok(s1, delim), strtok(s2, delim));

    ck_assert_str_eq(s21_strtok(NULL, delim), strtok(NULL, delim));

    ck_assert_ptr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  }

  {
    char s1[] = "Abrakadabra";
    char s2[] = "Abrakadabra";
    char delim[] = "/";
    ck_assert_str_eq(s21_strtok(s1, delim), strtok(s2, delim));
    ck_assert_ptr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  }
}
END_TEST
START_TEST(test_s21_insert) {
  char *src = "Hello !";
  char *str = "World";
  char *res = (char *)s21_insert(src, str, 6);
  ck_assert_str_eq(res, "Hello World!");
  free(res);

  char *res2 = (char *)s21_insert("World", "Hello ", 0);
  ck_assert_str_eq(res2, "Hello World");
  free(res2);

  char *src3 = "Hello";
  char *res3 = (char *)s21_insert(src3, " World", 5);
  ck_assert_str_eq(res3, "Hello World");
  free(res3);

  char *res4 = (char *)s21_insert("", "Hello", 0);
  ck_assert_str_eq(res4, "Hello");
  free(res4);

  ck_assert_ptr_eq(s21_insert(NULL, "str", 0), NULL);
  ck_assert_ptr_eq(s21_insert("src", NULL, 0), NULL);
  ck_assert_ptr_eq(s21_insert("src", "str", 100), NULL);
  END_TEST
}
START_TEST(test_s21_trim) {
  {
    char *src = "***Hello World***";
    char *trim_chars = "*";
    char *res = (char *)s21_trim(src, trim_chars);
    ck_assert_str_eq(res, "Hello World");
    free(res);
  }

  {
    char *src = "  ...Hello...  ";
    char *trim_chars = " .";
    char *res = (char *)s21_trim(src, trim_chars);
    ck_assert_str_eq(res, "Hello");
    free(res);
  }

  {
    char *src = ".....";
    char *trim_chars = ".";
    char *res = (char *)s21_trim(src, trim_chars);
    ck_assert_str_eq(res, "");
    free(res);
  }

  {
    char *src = "Hello";
    char *trim_chars = "xyz";
    char *res = (char *)s21_trim(src, trim_chars);
    ck_assert_str_eq(res, "Hello");
    free(res);
  }

  {
    char *src = "Hello";
    char *res = (char *)s21_trim(src, NULL);
    ck_assert_str_eq(res, "Hello");
    free(res);
  }

  ck_assert_ptr_eq(s21_trim(NULL, "*"), NULL);
}
END_TEST

Suite *string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("string");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_strchr);
  tcase_add_test(tc_core, test_strchr_not_found);
  tcase_add_test(tc_core, test_strchr_null);
  tcase_add_test(tc_core, test_strchr_empty);
  tcase_add_test(tc_core, test_strchr_empty_null);

  tcase_add_test(tc_core, test_strstr);
  tcase_add_test(tc_core, test_strstr_not_found);
  tcase_add_test(tc_core, test_strstr_empty_needle);
  tcase_add_test(tc_core, test_strstr_long_needle);
  tcase_add_test(tc_core, test_strstr_empty_haystack);
  tcase_add_test(tc_core, test_strstr_both_empty);

  tcase_add_test(tc_core, test_strncmp_same);
  tcase_add_test(tc_core, test_strncmp_diff);
  tcase_add_test(tc_core, test_strncmp_cut);
  tcase_add_test(tc_core, test_strncmp_empty);
  tcase_add_test(tc_core, test_strncmp_short);

  tcase_add_test(tc_core, test_strncat);
  tcase_add_test(tc_core, test_strncat_cut);
  tcase_add_test(tc_core, test_strncat_empty_src);
  tcase_add_test(tc_core, test_strncat_empty_dest);
  tcase_add_test(tc_core, test_strncat_zero_n);

  tcase_add_test(tc_core, test_strncpy);
  tcase_add_test(tc_core, test_strncpy_cut);
  tcase_add_test(tc_core, test_strncpy_empty);
  tcase_add_test(tc_core, test_strncpy_zero);

  tcase_add_test(tc_core, test_strrchr);
  tcase_add_test(tc_core, test_strrchr_multi);
  tcase_add_test(tc_core, test_strrchr_not_found);
  tcase_add_test(tc_core, test_strrchr_null);
  tcase_add_test(tc_core, test_strrchr_empty);

  tcase_add_test(tc_core, test_memcpy_char);
  tcase_add_test(tc_core, test_memcpy_arr);
  tcase_add_test(tc_core, test_memcpy_empty_src);
  tcase_add_test(tc_core, test_memcpy_rewrite);
  tcase_add_test(tc_core, test_memcpy_piece);

  tcase_add_test(tc_core, test_memset);
  tcase_add_test(tc_core, test_memset_zeros);
  tcase_add_test(tc_core, test_memset_part);
  tcase_add_test(tc_core, test_memset_empty);

  tcase_add_test(tc_core, test_memcmp);
  tcase_add_test(tc_core, test_memcmp_less);
  tcase_add_test(tc_core, test_memcmp_greater);
  tcase_add_test(tc_core, test_memcmp_int_array);
  tcase_add_test(tc_core, test_memcmp_with_null);
  tcase_add_test(tc_core, test_memcmp_zeros);

  tcase_add_test(tc_core, test_memchr);
  tcase_add_test(tc_core, test_memchr_not_found);
  tcase_add_test(tc_core, test_memchr_null);
  tcase_add_test(tc_core, test_memchr_with_null);
  tcase_add_test(tc_core, test_memchr_int_array);

  tcase_add_test(tc_core, test_to_upper);
  tcase_add_test(tc_core, test_to_upper_mix);
  tcase_add_test(tc_core, test_to_upper_null);
  tcase_add_test(tc_core, test_to_upper_empty);

  tcase_add_test(tc_core, test_to_lower);
  tcase_add_test(tc_core, test_to_lower_mix);
  tcase_add_test(tc_core, test_to_lower_null);
  tcase_add_test(tc_core, test_to_lower_empty);

  tcase_add_test(tc_core, test_strlen_basic);
  tcase_add_test(tc_core, test_strlen_empty);
  tcase_add_test(tc_core, test_strlen_one_char);
  tcase_add_test(tc_core, test_strlen_space);
  tcase_add_test(tc_core, test_strlen_numbers);
  tcase_add_test(tc_core, test_strlen_escape);
  tcase_add_test(tc_core, test_strlen_NULL);
  tcase_add_test(tc_core, test_strlen_long);
  tcase_add_test(tc_core, test_strlen_spaces_only);

  tcase_add_test(tc_core, test_s21_strerror);
  tcase_add_test(tc_core, test_s21_strcspn);
  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strtok);
  tcase_add_test(tc_core, test_s21_insert);
  tcase_add_test(tc_core, test_s21_trim);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  Suite *s = string_suite();
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? 0 : 1;
}