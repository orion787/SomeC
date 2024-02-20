#include <stdio.h>

int main(){
    enum State { STATE1, STATE2, STATE3 };
    enum State state = STATE1;

    char str[] = "ababa";
    char *ptr = str;

    while (*ptr != '\0') {
        switch (state) {
            case STATE1:
                switch (*ptr) {
                    case 'a':
                        state = STATE2;
                        break;
                    default:
                        break;
                }
                break;
            case STATE2:
                switch (*ptr) {
                    case 'b':
                        state = STATE3;
                        break;
                    case 'a':
                        state = STATE1;
                        break;
                    default:
                        break;
                }
                break;
            case STATE3:
                switch (*ptr) {
                    case 'a':
                        state = STATE3;
                        break;
                    case 'b':
                        state = STATE1;
                        break;
                    default:
                        break;
                }
                break;
        }
        ptr++;
    }

    char res = (state == STATE2);
    printf("%d\n", res ?  1 : 0);

    return 0;
}
