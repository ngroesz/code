#include <stdio.h>

int main()
{
    unsigned long result = 0;
    result = result << 1 | 0;
    result = result << 1 | 0;
    result = result << 1 | 0;
    result = result << 1 | 1;

    result = result << 1 | 0;
    result = result << 1 | 0;
    result = result << 1 | 0;
    result = result << 1 | 0;

    result = result << 1 | 1;
    result = result << 1 | 1;
    result = result << 1 | 1;
    result = result << 1 | 0;

    result = result << 1 | 1;
    result = result << 1 | 1;
    result = result << 1 | 1;
    result = result << 1 | 1;

    result = result << 1 | 1;
    result = result << 1 | 1;
    result = result << 1 | 1;
    result = result << 1 | 1;

    result = result << 1 | 1;
    result = result << 1 | 0;
    result = result << 1 | 0;
    result = result << 1 | 0;

    result = result << 1 | 0;
    result = result << 1 | 0;
    result = result << 1 | 0;
    result = result << 1 | 0;

    result = result << 1 | 0;
    result = result << 1 | 1;
    result = result << 1 | 1;
    result = result << 1 | 1;

    printf("result: %lu\n", result);
}
