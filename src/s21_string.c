#include <string.h>
#include <stdio.h>


void *MY_memchr(const void *str, int c, size_t n);
int MY_memcmp(const void *str1, const void *str2, size_t n){
    unsigned char* c = (unsigned char*)str1;
    unsigned char* b = (unsigned char*)str2;
    int result = 0;
    for (int i = 0;i<(int)n;i++){
        result += (int)c[i]-(int)b[i];
    }
    return result;
}
void *MY_memcpy(void *dest, const void *src, size_t n);
void *MY_memset(void *str, int c, size_t n);
char *MY_strncat(char *dest, const char *src, size_t n);
char *MY_strchr(const char *str, int c);
int MY_strncmp(const char *str1, const char *str2, size_t n);
char *MY_strncpy(char *dest, const char *src, size_t n);
size_t MY_strcspn(const char *str1, const char *str2);
char *MY_strerror(int errnum);
size_t MY_strlen(const char *str);
char *MY_strpbrk(const char *str1, const char *str2);
char *MY_strrchr(const char *str, int c);
char *_MYstrstr(const char *haystack, const char *needle);
char *MY_strtok(char *str, const char *delim);



int main (){
    char* str1 = "hello";
    char* str2 = "hello";
    char* str3 = "Hello";
    typedef struct{
        int p;
        int a;
        int r;
    }Parts;
    int s = 5,b = 7;
    printf("%d\n",MY_memcmp(str1,str3,5));
    printf("%d\n",memcmp(str1,str3,5));
    Parts p1 = {1,2,3};
    Parts p2 = {3,2,3};
   // printf("%d\n",MY_memcmp(a,b,5));
    printf("%d\n",(memcmp(&p1,&p2,5)));
    printf("%d\n",(MY_memcmp(&p1,&p2,5)));
    return 0;
}