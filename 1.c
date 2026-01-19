#include <stdio.h>

int s21_isdigit(char c) {
    return (c >= '0' && c <= '9');
}

int s21_atoi(const char **str) {
    int result = 0;
    while (s21_isdigit(**str)) {
        result = result * 10 + (**str - '0');
        (*str)++;
    }
    return result;
}

int main(){
    char* str[11] = "1234567890";
    int i = s21_atoi(str);

printf("%d\n", i);
return 0;
}