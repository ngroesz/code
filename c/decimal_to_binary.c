#include <stdio.h>

void decimal_to_binary(int n)
{
    int output[4];

    int i = 0;
    while (n > 0) {
        output[i] = n % 2;
        n = n / 2;
        ++i;
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", output[j]);
    }

    printf("\n");
}

int main()
{
    decimal_to_binary(14);
}
