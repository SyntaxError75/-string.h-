#ifndef S21_STRING_H
#define S21_STRING_H

#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define S21_NULL ((void *)0)

typedef unsigned long s21_size_t;
typedef struct {
  int minus;
  int plus;
  int space;
  int hash;
  int zero;
  int width;
  int width_star;
  int precision;
  int prec_star;
  int has_precision;
  char length;
  char specifier;
} FormatSpec;
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

void s21_parse_format(const char **format, FormatSpec *spec);
int s21_handle_specifier(char *str, FormatSpec *spec, va_list *args);
int s21_format_char(char *str, FormatSpec *spec, int c);
int s21_format_string(char *str, FormatSpec *spec, const char *s);
int s21_format_int(char *str, FormatSpec *spec, long long value);
int s21_format_uint(char *str, FormatSpec *spec, unsigned long long value);
int s21_format_octal(char *str, FormatSpec *spec, unsigned long long value);
int s21_format_hex(char *str, FormatSpec *spec, unsigned long long value,
                   int uppercase);
int s21_format_float(char *str, FormatSpec *spec, long double value);
int s21_handle_special_float(char *str, FormatSpec *spec, long double value,
                             int is_negative, int uppercase);
int s21_format_exp(char *str, FormatSpec *spec, long double value,
                   int uppercase);
int s21_format_g(char *str, FormatSpec *spec, long double value, int uppercase);
int s21_format_pointer(char *str, FormatSpec *spec, void *ptr);
int s21_format_percent(char *str, FormatSpec *spec);

#endif
