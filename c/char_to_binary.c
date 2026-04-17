#include <stdio.h>

void char_to_binary(unsigned char code)
{
    for (int i = 0; i < 8; ++i) {
        if (code % 2 == 1) {
            printf("n: 1\n");
        } else if (code % 2 == 0) {
            printf("n: 0\n");
        } else {
            printf("n: %d\n", code % 2);
        }
        code = code / 2;
    }
}

int main()
{
    char_to_binary(85);
}
