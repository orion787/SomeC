#include <stdio.h>
#include <stdlib.h>

char *strcat_r(char *dest, int *bufsz, char *src){
    int d = 0, s = 0;

    while(d < *bufsz && src[d] != 0)
        d++;

    while(src[s] != 0){
        if(d >= *bufsz - 1){
            int new_size = 0;
            char *new = NULL;

            if(*bufsz == 0)
                *bufsz = 2;

            new_size = *bufsz * 2;
            new = realloc(dest, new_size * sizeof(char));

            if(new == NULL){
                fprintf(stderr, "Realloc error");
                abort();
            }

            dest = new;
            *bufsz = new_size;
        }
        dest[d++] = src[s++];
    }

    dest[d] = 0;
    return dest;
}
