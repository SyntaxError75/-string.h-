#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "s21_string.h"

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

static void s21_reverse_str(char *str, int len) {
  int start = 0;
  int end = len - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

static int s21_isdigit(char c) { return (c >= '0' && c <= '9'); }
static int s21_atoi(const char **str) {
  int result = 0;
  while (s21_isdigit(**str)) {
    result = result * 10 + (**str - '0');
    (*str)++;
  }
  return result;
}

static void s21_init_format_spec(FormatSpec *spec) {
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

static void s21_parse_flags(const char **format, FormatSpec *spec) {
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
  if (spec->plus) {
    spec->space = 0;
  }
  if (spec->minus) {
    spec->zero = 0;
  }
}

static void s21_parse_width(const char **format, FormatSpec *spec) {
  if (**format == '*') {
    spec->width_star = 1;
    (*format)++;
  } else if (s21_isdigit(**format)) {
    spec->width = s21_atoi(format);
  }
}

static void s21_parse_precision(const char **format, FormatSpec *spec) {
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

static void s21_parse_length(const char **format, FormatSpec *spec) {
  if (**format == 'h' || **format == 'l' || **format == 'L') {
    spec->length = **format;
    (*format)++;
  }
}

void s21_parse_format(const char **format, FormatSpec *spec) {
  s21_init_format_spec(spec);
  s21_parse_flags(format, spec);
  s21_parse_width(format, spec);
  s21_parse_precision(format, spec);
  s21_parse_length(format, spec);
  spec->specifier = **format;
  (*format)++;
}

static int s21_uint_to_str(char *buf, unsigned long long value, int base,
                           int uppercase) {
  const char *digits_lower = "0123456789abcdef";
  const char *digits_upper = "0123456789ABCDEF";
  const char *digits = digits_lower;
  if (uppercase) digits = digits_upper;
  int len = 0;
  if (value == 0) {
    buf[len++] = '0';
  } else {
    while (value > 0) {
      buf[len++] = digits[value % base];
      value /= base;
    }
  }
  s21_reverse_str(buf, len);
  buf[len] = '\0';
  return len;
}

static int s21_add_padding(char *str, int count, char pad_char) {
  for (int i = 0; i < count; i++) {
    str[i] = pad_char;
  }
  return count;
}

int s21_format_char(char *str, const FormatSpec *spec, int c) {
  int len = 0;
  int padding;
  if (spec->width > 1) {
    padding = spec->width - 1;
  } else {
    padding = 0;
  }
  if (!spec->minus && padding > 0) {
    len += s21_add_padding(str + len, padding, ' ');
  }
  str[len++] = (char)c;
  if (spec->minus && padding > 0) {
    len += s21_add_padding(str + len, padding, ' ');
  }
  return len;
}

int s21_format_string(char *str, const FormatSpec *spec, const char *s) {
  int len = 0;
  if (s == S21_NULL) {
    s = "(null)";
  }
  int str_len = (int)s21_strlen(s);
  if (spec->has_precision && spec->precision >= 0 &&
      spec->precision < str_len) {
    str_len = spec->precision;
  }
  int padding;
  if (spec->width > str_len)
    padding = spec->width - str_len;
  else
    padding = 0;
  if (!spec->minus && padding > 0) {
    len += s21_add_padding(str + len, padding, ' ');
  }
  s21_memcpy(str + len, s, str_len);
  len += str_len;
  if (spec->minus && padding > 0) {
    len += s21_add_padding(str + len, padding, ' ');
  }
  return len;
}

int s21_format_int(char *str, FormatSpec *spec, long long value) {
  char num_buf[64];
  int num_len;
  int is_negative = 0;
  unsigned long long abs_value;
  if (value < 0) {
    is_negative = 1;
    abs_value = (unsigned long long)(-(value + 1)) + 1;
  } else {
    abs_value = (unsigned long long)value;
  }
  num_len = s21_uint_to_str(num_buf, abs_value, 10, 0);
  if (value == 0 && spec->has_precision && spec->precision == 0) {
    num_len = 0;
    num_buf[0] = '\0';
  }
  char sign_char = 0;
  if (is_negative) {
    sign_char = '-';
  } else if (spec->plus) {
    sign_char = '+';
  } else if (spec->space) {
    sign_char = ' ';
  }
  int sign_len = 0;
  if (sign_char != 0) sign_len = 1;
  int precision = spec->has_precision ? spec->precision : 1;
  int zero_padding = precision > num_len ? precision - num_len : 0;
  int total_num_len = sign_len + zero_padding + num_len;
  int field_padding =
      spec->width > total_num_len ? spec->width - total_num_len : 0;
  int len = 0;
  if (!spec->minus && !spec->zero && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, ' ');
  }
  if (sign_char) {
    str[len++] = sign_char;
  }
  if (spec->zero && !spec->has_precision && !spec->minus && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, '0');
    field_padding = 0;
  }
  len += s21_add_padding(str + len, zero_padding, '0');
  s21_memcpy(str + len, num_buf, num_len);
  len += num_len;
  if (spec->minus && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, ' ');
  }
  return len;
}

int s21_format_uint(char *str, FormatSpec *spec, unsigned long long value) {
  char num_buf[64];
  int num_len;
  num_len = s21_uint_to_str(num_buf, value, 10, 0);
  if (value == 0 && spec->has_precision && spec->precision == 0) {
    num_len = 0;
    num_buf[0] = '\0';
  }
  int precision = spec->has_precision ? spec->precision : 1;
  int zero_padding = precision > num_len ? precision - num_len : 0;
  int total_num_len = zero_padding + num_len;
  int field_padding =
      spec->width > total_num_len ? spec->width - total_num_len : 0;
  int len = 0;
  if (!spec->minus && !spec->zero && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, ' ');
  }
  if (spec->zero && !spec->has_precision && !spec->minus && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, '0');
    field_padding = 0;
  }
  len += s21_add_padding(str + len, zero_padding, '0');
  s21_memcpy(str + len, num_buf, num_len);
  len += num_len;
  if (spec->minus && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, ' ');
  }
  return len;
}

int s21_format_octal(char *str, FormatSpec *spec, unsigned long long value) {
  char num_buf[64];
  int num_len;
  num_len = s21_uint_to_str(num_buf, value, 8, 0);
  if (value == 0 && spec->has_precision && spec->precision == 0 &&
      !spec->hash) {
    num_len = 0;
    num_buf[0] = '\0';
  }
  int prefix_len = 0;
  if (spec->hash && value != 0) {
    prefix_len = 1;
  }
  int precision = spec->has_precision ? spec->precision : 1;
  int zero_padding = precision > num_len ? precision - num_len : 0;
  if (spec->hash && zero_padding == 0 && (value != 0 || !spec->has_precision)) {
    prefix_len = 1;
  }
  int total_len = prefix_len + zero_padding + num_len;
  int field_padding = spec->width > total_len ? spec->width - total_len : 0;
  int len = 0;
  if (!spec->minus && !spec->zero && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, ' ');
  }
  if (prefix_len > 0) {
    str[len++] = '0';
  }
  if (spec->zero && !spec->has_precision && !spec->minus && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, '0');
    field_padding = 0;
  }
  len += s21_add_padding(str + len, zero_padding, '0');
  s21_memcpy(str + len, num_buf, num_len);
  len += num_len;
  if (spec->minus && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, ' ');
  }
  return len;
}

int s21_format_hex(char *str, FormatSpec *spec, unsigned long long value,
                   int uppercase) {
  char num_buf[64];
  int num_len;
  num_len = s21_uint_to_str(num_buf, value, 16, uppercase);
  if (value == 0 && spec->has_precision && spec->precision == 0) {
    num_len = 0;
    num_buf[0] = '\0';
  }
  int prefix_len = 0;
  if (spec->hash && value != 0) {
    prefix_len = 2;
  }
  int precision = spec->has_precision ? spec->precision : 1;
  int zero_padding = precision > num_len ? precision - num_len : 0;

  int total_len = prefix_len + zero_padding + num_len;
  int field_padding = spec->width > total_len ? spec->width - total_len : 0;

  int len = 0;
  if (!spec->minus && !spec->zero && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, ' ');
  }
  if (prefix_len > 0) {
    str[len++] = '0';
    str[len++] = uppercase ? 'X' : 'x';
  }
  if (spec->zero && !spec->has_precision && !spec->minus && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, '0');
    field_padding = 0;
  }
  len += s21_add_padding(str + len, zero_padding, '0');
  s21_memcpy(str + len, num_buf, num_len);
  len += num_len;
  if (spec->minus && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, ' ');
  }
  return len;
}

int s21_format_pointer(char *str, const FormatSpec *spec, void *ptr) {
  if (ptr == S21_NULL) {
    FormatSpec temp_spec = *spec;
    temp_spec.hash = 0;
    return s21_format_string(str, &temp_spec, "(nil)");
  }
  FormatSpec temp_spec = *spec;
  temp_spec.hash = 1;
  return s21_format_hex(str, &temp_spec, (unsigned long long)(uintptr_t)ptr, 0);
}

static void s21_round_and_extract(long double value, int precision,
                                  unsigned long long *int_part_out,
                                  char *frac_digits, int *frac_len) {
  long double multiplier = 1.0L;
  for (int i = 0; i < precision; i++) {
    multiplier *= 10.0L;
  }
  long double scaled = value * multiplier;
  scaled += 0.5L + 1e-9L;
  unsigned long long total = (unsigned long long)scaled;
  unsigned long long divisor = 1;
  for (int i = 0; i < precision; i++) {
    divisor *= 10;
  }
  *int_part_out = total / divisor;
  unsigned long long frac_part = total % divisor;
  *frac_len = precision;
  for (int i = precision - 1; i >= 0; i--) {
    frac_digits[i] = '0' + (frac_part % 10);
    frac_part /= 10;
  }
  frac_digits[precision] = '\0';
}

int s21_handle_special_float(char *str, const FormatSpec *spec,
                             long double value, int is_negative,
                             int uppercase) {
  int len = 0;

  if (isinf(value)) {
    char sign_char = 0;
    if (is_negative) {
      sign_char = '-';
    } else if (spec->plus) {
      sign_char = '+';
    } else if (spec->space) {
      sign_char = ' ';
    }
    int sign_len = sign_char ? 1 : 0;
    const char *special_str = uppercase ? "INF" : "inf";
    int str_len = 3;
    int padding = spec->width > (sign_len + str_len)
                      ? spec->width - sign_len - str_len
                      : 0;

    if (!spec->minus && padding > 0) {
      len += s21_add_padding(str + len, padding, ' ');
    }
    if (sign_char) {
      str[len++] = sign_char;
    }
    s21_memcpy(str + len, special_str, str_len);
    len += str_len;
    if (spec->minus && padding > 0) {
      len += s21_add_padding(str + len, padding, ' ');
    }
  } else if (isnan(value)) {
    const char *special_str = uppercase ? "NAN" : "nan";
    int str_len = 3;
    int padding = spec->width > str_len ? spec->width - str_len : 0;

    if (!spec->minus && padding > 0) {
      len += s21_add_padding(str + len, padding, ' ');
    }
    s21_memcpy(str + len, special_str, str_len);
    len += str_len;
    if (spec->minus && padding > 0) {
      len += s21_add_padding(str + len, padding, ' ');
    }
  }
  return len;
}

int s21_format_float(char *str, const FormatSpec *spec, long double value) {
  int len = 0, num_len = 0, is_negative = 0;
  char num_buf[512];
  if (value < 0) {
    is_negative = 1;
    value = -value;
  }
  if (isinf(value) || isnan(value)) {
    return s21_handle_special_float(str, spec, value, is_negative, 0);
  }
  int precision = 6;
  if (spec->has_precision) {
    precision = spec->precision;
  }
  unsigned long long int_part;
  char frac_digits[64];
  int frac_len;
  s21_round_and_extract(value, precision, &int_part, frac_digits, &frac_len);
  num_len = s21_uint_to_str(num_buf, int_part, 10, 0);
  if (precision > 0 || spec->hash) {
    num_buf[num_len++] = '.';
    for (int i = 0; i < frac_len; i++) {
      num_buf[num_len++] = frac_digits[i];
    }
  }
  num_buf[num_len] = '\0';
  char sign_char = 0;
  if (is_negative) {
    sign_char = '-';
  } else if (spec->plus) {
    sign_char = '+';
  } else if (spec->space) {
    sign_char = ' ';
  }
  int sign_len = sign_char ? 1 : 0;
  int total_len = sign_len + num_len;
  int field_padding = spec->width > total_len ? spec->width - total_len : 0;
  if (!spec->minus && !spec->zero && field_padding > 0)
    len += s21_add_padding(str + len, field_padding, ' ');
  if (sign_char) str[len++] = sign_char;
  if (spec->zero && !spec->minus && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, '0');
    field_padding = 0;
  }
  s21_memcpy(str + len, num_buf, num_len);
  len += num_len;
  if (spec->minus && field_padding > 0)
    len += s21_add_padding(str + len, field_padding, ' ');
  return len;
}

static int build_exponential_number(long double value, int precision,
                                    int uppercase, char *num_buf,
                                    int *exponent_result,
                                    const FormatSpec *spec) {
  int num_len = 0, exponent = 0;
  if (value != 0.0L) {
    exponent = (int)floorl(log10l(value));
    value /= powl(10.0L, exponent);
    if (value >= 10.0L) {
      value /= 10.0L;
      exponent++;
    } else if (value < 1.0L && value > 0.0L) {
      value *= 10.0L;
      exponent--;
    }
  }
  unsigned long long int_part;
  char frac_digits[64];
  int frac_len;
  s21_round_and_extract(value, precision, &int_part, frac_digits, &frac_len);
  if (int_part >= 10) {
    int_part = 1;
    exponent++;
    s21_round_and_extract(1.0L, precision, &int_part, frac_digits, &frac_len);
  }
  num_len = s21_uint_to_str(num_buf, int_part, 10, 0);
  if (precision > 0) {
    num_buf[num_len++] = '.';
    for (int i = 0; i < frac_len; i++) {
      num_buf[num_len++] = frac_digits[i];
    }
  } else if (precision == 0 && spec->hash) {
    num_buf[num_len++] = '.';
  }
  num_buf[num_len++] = uppercase ? 'E' : 'e';
  num_buf[num_len++] = exponent >= 0 ? '+' : '-';
  if (exponent < 0) exponent = -exponent;
  if (exponent < 10) {
    num_buf[num_len++] = '0';
    num_buf[num_len++] = '0' + exponent;
  } else if (exponent < 100) {
    num_buf[num_len++] = '0' + exponent / 10;
    num_buf[num_len++] = '0' + exponent % 10;
  } else {
    char exp_buf[16];
    int exp_len = s21_uint_to_str(exp_buf, exponent, 10, 0);
    s21_memcpy(num_buf + num_len, exp_buf, exp_len);
    num_len += exp_len;
  }
  num_buf[num_len] = '\0';
  if (exponent_result) *exponent_result = exponent;
  return num_len;
}

int s21_format_exp(char *str, FormatSpec *spec, long double value,
                   int uppercase) {
  int len = 0;
  int is_negative = 0;
  if (value < 0) {
    is_negative = 1;
    value = -value;
  }
  if (isinf(value) || isnan(value)) {
    return s21_handle_special_float(str, spec, value, is_negative, uppercase);
  }
  int precision = spec->has_precision ? spec->precision : 6;
  char num_buf[512];
  int num_len = build_exponential_number(value, precision, uppercase, num_buf,
                                         NULL, spec);
  char sign_char = 0;
  if (is_negative) {
    sign_char = '-';
  } else if (spec->plus) {
    sign_char = '+';
  } else if (spec->space) {
    sign_char = ' ';
  }
  int sign_len = sign_char ? 1 : 0;
  int total_len = sign_len + num_len;
  int field_padding = spec->width > total_len ? spec->width - total_len : 0;
  if (!spec->minus && !spec->zero && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, ' ');
  }
  if (sign_char) {
    str[len++] = sign_char;
  }
  if (spec->zero && !spec->minus && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, '0');
    field_padding = 0;
  }
  s21_memcpy(str + len, num_buf, num_len);
  len += num_len;
  if (spec->minus && field_padding > 0) {
    len += s21_add_padding(str + len, field_padding, ' ');
  }
  return len;
}

static int s21_trim_trailing_zeros(char *str, int len, int has_hash) {
  if (!has_hash) {
    int dot_pos = -1;
    for (int i = 0; i < len; i++) {
      if (str[i] == '.') {
        dot_pos = i;
        break;
      }
    }
    if (dot_pos >= 0) {
      int end_pos = len;
      for (int i = dot_pos; i < len; i++) {
        if (str[i] == 'e' || str[i] == 'E') {
          end_pos = i;
          break;
        }
      }
      int new_end = end_pos;
      while (new_end > dot_pos + 1 && str[new_end - 1] == '0') {
        new_end--;
      }
      if (new_end == dot_pos + 1) {
        new_end = dot_pos;
      }
      if (end_pos < len) {
        int shift = end_pos - new_end;
        for (int i = end_pos; i < len; i++) {
          str[i - shift] = str[i];
        }
        len -= shift;
      } else {
        len = new_end;
      }
    }
  }
  str[len] = '\0';
  return len;
}

int s21_format_g(char *str, const FormatSpec *spec, long double value,
                 int uppercase) {
  int precision = 6;
  if (spec->has_precision) precision = spec->precision;

  if (precision == 0) precision = 1;

  long double abs_value = value;
  if (value < 0) abs_value = -value;
  int exponent = 0;
  if (abs_value != 0.0L && !isinf(abs_value) && !isnan(abs_value)) {
    exponent = (int)floorl(log10l(abs_value));
  }
  int len;
  if (exponent < -4 || exponent >= precision) {
    FormatSpec temp_spec = *spec;
    temp_spec.precision = precision - 1;
    temp_spec.has_precision = 1;
    len = s21_format_exp(str, &temp_spec, value, uppercase);
  } else {
    FormatSpec temp_spec = *spec;
    temp_spec.precision = precision - 1 - exponent;
    if (temp_spec.precision < 0) temp_spec.precision = 0;
    temp_spec.has_precision = 1;
    len = s21_format_float(str, &temp_spec, value);
  }
  len = s21_trim_trailing_zeros(str, len, spec->hash);
  return len;
}

int s21_format_percent(char *str, FormatSpec *spec) {
  int len = 0;
  int padding = 0;
  if (spec->width > 1) padding = spec->width - 1;
  if (!spec->minus && padding > 0) {
    char pad_char = spec->zero ? '0' : ' ';
    len += s21_add_padding(str + len, padding, pad_char);
  }

  str[len++] = '%';

  if (spec->minus && padding > 0) {
    len += s21_add_padding(str + len, padding, ' ');
  }

  return len;
}

static void handle_star_args(FormatSpec *spec, va_list *args) {
  if (spec->width_star) {
    spec->width = va_arg(*args, int);
    if (spec->width < 0) {
      spec->width = -spec->width;
      spec->minus = 1;
    }
  }

  if (spec->prec_star) {
    spec->precision = va_arg(*args, int);
    if (spec->precision < 0) {
      spec->has_precision = 0;
      spec->precision = -1;
    }
  }
}

static long long get_int_value(const FormatSpec *spec, va_list *args,
                               int is_signed) {
  long long value = 0;
  if (spec->length == 'l') {
    value = is_signed ? (long long)va_arg(*args, long)
                      : (long long)va_arg(*args, unsigned long);
  } else if (spec->length == 'h') {
    value = is_signed ? (long long)(short)va_arg(*args, int)
                      : (long long)(unsigned short)va_arg(*args, unsigned int);
  } else {
    value = is_signed ? (long long)va_arg(*args, int)
                      : (long long)va_arg(*args, unsigned int);
  }
  return value;
}

static long double get_float_value(const FormatSpec *spec, va_list *args) {
  long double value;
  if (spec->length == 'L') {
    value = va_arg(*args, long double);
  } else {
    value = va_arg(*args, double);
  }
  return value;
}

static int handle_integer_specifiers(char *str, FormatSpec *spec, va_list *args,
                                     char specifier) {
  unsigned long long value =
      get_int_value(spec, args, (specifier == 'd' || specifier == 'i'));
  int len;
  switch (specifier) {
    case 'd':
    case 'i':
      len = s21_format_int(str, spec, (long long)value);
      break;
    case 'u':
      len = s21_format_uint(str, spec, value);
      break;
    case 'o':
      len = s21_format_octal(str, spec, value);
      break;
    case 'x':
      len = s21_format_hex(str, spec, value, 0);
      break;
    case 'X':
      len = s21_format_hex(str, spec, value, 1);
      break;
    default:
      len = 0;
      break;
  }
  return len;
}

static int handle_float_specifiers(char *str, FormatSpec *spec, va_list *args,
                                   char specifier) {
  long double value = get_float_value(spec, args);
  int len;
  switch (specifier) {
    case 'f':
      len = s21_format_float(str, spec, value);
      break;
    case 'e':
      len = s21_format_exp(str, spec, value, 0);
      break;
    case 'E':
      len = s21_format_exp(str, spec, value, 1);
      break;
    case 'g':
      len = s21_format_g(str, spec, value, 0);
      break;
    case 'G':
      len = s21_format_g(str, spec, value, 1);
      break;
    default:
      len = 0;
      break;
  }
  return len;
}

static int handle_other_specifiers(char *str, FormatSpec *spec, va_list *args,
                                   char specifier) {
  int len;
  switch (specifier) {
    case 'c': {
      int c = va_arg(*args, int);
      len = s21_format_char(str, spec, c);
      break;
    }
    case 's': {
      const char *s = va_arg(*args, char *);
      len = s21_format_string(str, spec, s);
      break;
    }
    case 'p': {
      void *ptr = va_arg(*args, void *);
      len = s21_format_pointer(str, spec, ptr);
      break;
    }
    case 'n':
      len = 0;
      break;
    case '%':
      len = s21_format_percent(str, spec);
      break;
    default:
      str[0] = '%';
      str[1] = specifier;
      len = 2;
      break;
  }
  return len;
}

int s21_handle_specifier(char *str, FormatSpec *spec, va_list *args) {
  handle_star_args(spec, args);
  char sp = spec->specifier;
  int len;
  if (sp == 'd' || sp == 'i' || sp == 'u' || sp == 'o' || sp == 'x' ||
      sp == 'X') {
    len = handle_integer_specifiers(str, spec, args, sp);
  } else if (sp == 'f' || sp == 'e' || sp == 'E' || sp == 'g' || sp == 'G') {
    len = handle_float_specifiers(str, spec, args, sp);
  } else {
    len = handle_other_specifiers(str, spec, args, sp);
  }
  return len;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int total_len = 0;
  const char *p = format;
  while (*p != '\0') {
    if (*p == '%') {
      p++;
      if (*p == '\0') {
        break;
      }

      FormatSpec spec;
      s21_parse_format(&p, &spec);
      if (spec.specifier == 'n') {
        int *n_ptr = va_arg(args, int *);
        if (n_ptr != S21_NULL) {
          *n_ptr = total_len;
        }
        continue;
      }
      int len = s21_handle_specifier(str + total_len, &spec, &args);
      total_len += len;
    } else {
      str[total_len++] = *p;
      p++;
    }
  }
  str[total_len] = '\0';
  va_end(args);
  return total_len;
}
