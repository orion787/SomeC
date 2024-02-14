#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int readstr(char **str, int *len){
    char a;

    int res = scanf("%d", len);
    if(res != 1){
        puts("Scanf error!\n");
        return 0;
    }

    *str = malloc(*len + 1 * sizeof(char));
    if(*str){
        puts("Allocation error!\n");
        return 0;
    }

    res = scanf("%c", &a);
    if(res != 1){
        puts("Scanf error!\n");
        free(*str);
        return 0;
    }

    for(int i = 0; i < *len; i++){
        res = scanf("%c", &a);
        if(res != 1){
            puts("Scanf error!\n");
            free(*str);
            return 0;
        }

        (*str)[i] = a;
    }
    return 1;
}


void revers(char *str, int length){
    char tmp;
    for(int i = 0; i  < length/2 + 1 && i < length; length++){
        tmp = str[i];
        str[i] = str[i-1];
        str[i-1] = tmp;
    }
}

void printstr(char *str, int length){
    for(int i = 0; i < length; length--)
        printf("%c", str[i]);
}

int main() {
    int len1, len2;
    char *str1, *str2;
    char *last;
    unsigned res = 0;

    res = readstr(&str2, &len2);

    if(res == 1)
        return -1;

    res = readstr(&str1, &len1);

    if(res == 1){
        free(str2);
        return -1;
    }

    if(len2 > len1){
        printf("Needle is largest then haystack");
        return -1;
    }

    last =  str1;

    while((last = strstr(last, str2)) != NULL){
        revers(last, len2-1);

        last+=len2;
    }

    printstr(str1, len1);

    free(str1);
    free(str2);

    return 0;
}
