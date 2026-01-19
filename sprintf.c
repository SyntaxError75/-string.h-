#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>  // для NULL

#define S21_NULL NULL

// Тип size_t - целочисленный тип без знака, результат ключевого слова sizeof
typedef unsigned long s21_size_t;

typedef struct{
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

void s21_init_format_spec(FormatSpec *spec);
void s21_parse_format(const char **format, FormatSpec *spec);
void s21_parse_flags(const char **format, FormatSpec *spec);
void s21_parse_width(const char **format, FormatSpec *spec);
void s21_parse_precision(const char **format, FormatSpec *spec);
void s21_parse_length(const char **format, FormatSpec *spec);
int s21_format_float(char *p, FormatSpec *spec, long double value);
int s21_format_int(char *str, FormatSpec *spec, long long value);
int s21_format_uint(char *str, FormatSpec *spec, unsigned long long value, int base);
int s21_format_string(char *str, FormatSpec *spec, const char *value);
int s21_format_char(char *str, FormatSpec *spec, int value);
int s21_handle_specifier(char *str, FormatSpec *spec, va_list *arguments);
int sprintf_s21(char *str, const char *format, ...);
#endif

char* break_to_digits(int number);
int s21_strlen(const char *str);

int s21_strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int sprintf_s21(char* str, const char* format, ... ){
    va_list args;
    va_start(args, format);

    int total_len = 0;
    const char *p = format;

    while (*p != '\0') {
        if (*p == '%') {
            const char *percent_pos = p;  // Запоминаем позицию %
            p++; 

            if (*p == '\0') {
                // Если строка завершается после %, копируем %
                str[total_len++] = '%';
                break;
            }
            
            FormatSpec spec;
            s21_parse_format(&p, &spec);
            
            // Обработка спецификатора 'n' отдельно
            if (spec.specifier == 'n') {
                int *n_ptr = va_arg(args, int *);
                if (n_ptr != S21_NULL) {
                    *n_ptr = total_len;
                }
                continue;
            }

            int len = s21_handle_specifier(str + total_len, &spec, &args);
            if (len == -1) {
                // Если обработка не удалась, копируем символы как есть
                const char *temp = percent_pos;
                while (temp < p) {
                    str[total_len++] = *temp++;
                }
            } else {
                total_len += len;
            }
        } else {
            str[total_len++] = *p;
            p++;
        }
    }

    str[total_len] = '\0';
    va_end(args);

    return total_len;
}

char* break_to_digits(int number){
    char* buffer;
    if (number == 0){
        buffer = malloc(2);
        if(!buffer) return NULL;
        buffer[0] = '0';
        buffer[1] = '\0';
        return buffer;
    }
    
    int is_negative = number < 0;
    if (is_negative) number = -number;
    
    int temp = number;
    int digits = 0;
    while (temp > 0){
        digits++;
        temp /= 10;
    }
    
    buffer = malloc(digits + 1 + is_negative);
    if(!buffer) return NULL;
    
    int index = digits + is_negative - 1;
    buffer[digits + is_negative] = '\0';
    
    // Сохраняем исходное значение number
    //int original_number = number;
    while(number > 0){
        buffer[index--] = (number % 10) + '0';
        number /= 10;
    }
    
    if (is_negative) buffer[0] = '-';
    
    // Восстанавливаем number для использования в коде
   // number = original_number;
    return buffer;
}

void s21_parse_format(const char **format, FormatSpec *spec) {
    s21_init_format_spec(spec);
    s21_parse_flags(format, spec);
    s21_parse_width(format, spec);
    s21_parse_precision(format, spec);
    s21_parse_length(format, spec);
    if (**format) {
        spec->specifier = **format;
        (*format)++;
    }
}

void s21_init_format_spec(FormatSpec *spec) {
    spec->minus = 0;
    spec->plus = 0;
    spec->space = 0;
    spec->hash = 0;
    spec->zero = 0;
    spec->width = 0;
    spec->width_star = 0;
    spec->precision = -1;
    spec->prec_star = 0;
    spec->has_precision = 0;
    spec->length = 0;
    spec->specifier = 0;
}

void s21_parse_flags(const char **format, FormatSpec *spec) {
    int done = 0;
    while (!done) {
        switch (**format) {
            case '-':
                spec->minus = 1;
                (*format)++;
                break;
            case '+':
                spec->plus = 1;
                (*format)++;
                break;
            case ' ':
                spec->space = 1;
                (*format)++;
                break;
            case '#':
                spec->hash = 1;
                (*format)++;
                break;
            case '0':
                spec->zero = 1;
                (*format)++;
                break;
            default:
                done = 1;
                break;
        }
    }
    
    // Флаг '+' перекрывает флаг ' ' 
    if (spec->plus) {
        spec->space = 0;
    }
    
    // Флаг '-' перекрывает флаг '0'
    if (spec->minus) {
        spec->zero = 0;
    }
}

void s21_parse_width(const char **format, FormatSpec *spec) {
    if (**format == '*') {
        spec->width_star = 1;
        (*format)++;
    } else if (s21_isdigit(**format)) {
        spec->width = s21_atoi(format);
    }
}

void s21_parse_precision(const char **format, FormatSpec *spec) {
    if (**format == '.') {
        (*format)++;
        spec->has_precision = 1;
        if (**format == '*') {
            spec->prec_star = 1;
            (*format)++;
        } else if (s21_isdigit(**format)) {
            spec->precision = s21_atoi(format);
        } else {
            spec->precision = 0;
        }
    }
}
int s21_isdigit(char c){
return(c>='0' && c<='9');
}

s21_atoi(const char** str){ //Преобразует строку цифр в число
int result = 0;
while(s21_isdigit(**str)){
    result = result * 10 +(**str+'0');
    (*str)++;
}
return result;
}
void s21_parse_length(const char **format, FormatSpec *spec) {
    if (**format == 'h' || **format == 'l' || **format == 'L') {
        spec->length = **format;
        (*format)++;
    }
}

int s21_handle_specifier(char* p, FormatSpec *spec, va_list *args){
    int len = 0;
    char *temp_ptr = p;
    
    switch (spec->specifier){
        case 'c': {
            char charic = (char)va_arg(*args, int);
            *temp_ptr++ = charic;
            len = 1;
            break;
        }
        case 'd':
        case 'i': {
            int num = va_arg(*args, int);
            char* num_str = break_to_digits(num);
            if (num_str){
                char* char_in_num_str = num_str;
                while(*char_in_num_str){
                    *temp_ptr++ = *char_in_num_str++;
                    len++;
                }
                free(num_str);
            }
            break;
        }
        case 'f': {
            long double value;
            if (spec->length == 'L') {
                value = va_arg(*args, long double);
            } else {
                value = va_arg(*args, double);
            }
            len = s21_format_float(temp_ptr, spec, value);
            break;
        }
        case 's': {
            char* s = va_arg(*args, char*);
            if (s == S21_NULL) {
                s = "(null)";
            }
            while (*s) {
                *temp_ptr++ = *s++;
                len++;
            }
            break;
        }
        case '%':
            *temp_ptr++ = '%';
            len = 1;
            break;
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'o':
        case 'u':
        case 'x':
        case 'X':
        case 'p':
        case 'n':
        default:
            // Неизвестный спецификатор
            len = -1;
            break;
    }
    
    return len;
}

int s21_format_float(char* p, FormatSpec* spec, long double value){
    // Временная реализация через sprintf
    char buffer[256];
    int len;
    
    if (spec->has_precision && spec->precision >= 0) {
        len = sprintf(buffer, "%.*Lf", spec->precision, value);
    } else {
        len = sprintf(buffer, "%Lf", value);
    }
    
    // Копируем результат в целевой буфер
    for (int i = 0; i < len; i++) {
        p[i] = buffer[i];
    }
    
    return len;
}

int main(){
    char string[100];
    char string_copy[100];
    int iu = 1101;
    char r = 'r';
    char g = 'g';
    char s[10] = "hello";
    
    // Тест 1: Основной тест
    int how = sprintf_s21(string, "213 %d %c %s %c", iu, r, s, g);
    int how_basic = sprintf(string_copy, "213 %d %c %s %c", iu, r, s, g);
    
    printf("Custom sprintf: %s\nLength: %d\n", string, how);
    printf("Standard sprintf: %s\nLength: %d\n", string_copy, how_basic);
    
    // Тест 2: Числа
    char num_str[100], num_str_std[100];
    sprintf_s21(num_str, "Numbers: %d, %d, %d", 0, -123, 456);
    sprintf(num_str_std, "Numbers: %d, %d, %d", 0, -123, 456);
    printf("\nNumber test:\nCustom: %s\nStd: %s\n", num_str, num_str_std);
    
    // Тест 3: Процент
    char percent_str[100], percent_str_std[100];
    sprintf_s21(percent_str, "100%% complete!");
    sprintf(percent_str_std, "100%% complete!");
    printf("\nPercent test:\nCustom: %s\nStd: %s\n", percent_str, percent_str_std);
    
    return 0;
}

