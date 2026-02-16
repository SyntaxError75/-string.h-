#ifndef MY_STRING_H
#define MY_STRING_H

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#ifndef MY_NULL
#define MY_NULL ((void *)0)
#endif

typedef unsigned long MY_size_t;

// Прототипы основных функций string.h
// Prototypes of main string.h functions

void *MY_memchr(const void *str, int c, MY_size_t n);
int MY_memcmp(const void *str1, const void *str2, MY_size_t n);
void *MY_memcpy(void *dest, const void *src, MY_size_t n);//ПОКА НЕ РЕАЛИЗОВАНА
void *MY_memset(void *str, int c, MY_size_t n);//ПОКА НЕ РЕАЛИЗОВАНА
char *MY_strncat(char *dest, const char *src, MY_size_t n);//ПОКА НЕ РЕАЛИЗОВАНА
char *MY_strchr(const char *str, int c);//ПОКА НЕ РЕАЛИЗОВАНА
int MY_strncmp(const char *str1, const char *str2, MY_size_t n);//ПОКА НЕ РЕАЛИЗОВАНА
char *MY_strncpy(char *dest, const char *src, MY_size_t n);//ПОКА НЕ РЕАЛИЗОВАНА
MY_size_t MY_strcspn(const char *str1, const char *str2);//ПОКА НЕ РЕАЛИЗОВАНА
char *MY_strerror(int errnum);//ПОКА НЕ РЕАЛИЗОВАНА
MY_size_t MY_strlen(const char *str);//ПОКА НЕ РЕАЛИЗОВАНА
char *MY_strpbrk(const char *str1, const char *str2);//ПОКА НЕ РЕАЛИЗОВАНА
char *MY_strrchr(const char *str, int c);//ПОКА НЕ РЕАЛИЗОВАНА
char *MY_strstr(const char *haystack, const char *needle);//ПОКА НЕ РЕАЛИЗОВАНА
char *MY_strtok(char *str, const char *delim);//ПОКА НЕ РЕАЛИЗОВАНА


// sprintf and sscanf
int MY_sprintf(char *str, const char *format, ...);
int MY_sscanf(const char *str, const char *format, ...); //ПОКА НЕ РЕАЛИЗОВАНА

// Специальные функции обработки строк (вдохновленные C#)
// Special string processing functions (inspired by C#)
void *MY_to_upper(const char *str);
void *MY_to_lower(const char *str);
void *MY_insert(const char *src, const char *str, MY_size_t start_index);
void *MY_trim(const char *src, const char *trim_chars);

#endif