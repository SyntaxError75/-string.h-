#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

// Макрос S21_NULL - значение константы нулевого указателя
#define S21_NULL ((void *)0)

// Тип size_t - целочисленный тип без знака, результат ключевого слова sizeof
typedef unsigned long s21_size_t;

// Структура для хранения спецификаторов формата
// Structure for storing format specifiers
typedef struct {
    int minus;       // флаг '-' - выравнивание по левому краю
    int plus;        // флаг '+' - знак для положительных чисел
    int space;       // флаг ' ' - пробел перед положительным числом
    int hash;        // флаг '#' - альтернативная форма
    int zero;        // флаг '0' - заполнение нулями
    int width;       // ширина поля
    int width_star;  // ширина задана через '*'
    int precision;   // точность
    int prec_star;   // точность задана через '*'
    int has_precision; // флаг наличия точности
    char length;     // модификатор длины: 'h', 'l', 'L'
    char specifier;  // спецификатор: c, d, i, e, E, f, g, G, o, s, u, x, X, p, n, %
} FormatSpec;

// Прототипы основных функций string.h
// Prototypes of main string.h functions
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

// sprintf и sscanf
// sprintf and sscanf
int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);

// Специальные функции обработки строк (вдохновленные C#)
// Special string processing functions (inspired by C#)
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

// Вспомогательные функции для sprintf
// Helper functions for sprintf
void s21_parse_format(const char **format, FormatSpec *spec);
int s21_handle_specifier(char *str, FormatSpec *spec, va_list *args);
int s21_format_char(char *str, FormatSpec *spec, int c);
int s21_format_string(char *str, FormatSpec *spec, const char *s);
int s21_format_int(char *str, FormatSpec *spec, long long value);
int s21_format_uint(char *str, FormatSpec *spec, unsigned long long value);
int s21_format_octal(char *str, FormatSpec *spec, unsigned long long value);
int s21_format_hex(char *str, FormatSpec *spec, unsigned long long value, int uppercase);
int s21_format_float(char *str, FormatSpec *spec, long double value);
int s21_format_exp(char *str, FormatSpec *spec, long double value, int uppercase);
int s21_format_g(char *str, FormatSpec *spec, long double value, int uppercase);
int s21_format_pointer(char *str, FormatSpec *spec, void *ptr);
int s21_format_percent(char *str, FormatSpec *spec);

#endif  // S21_STRING_H
