#include <stdio.h>

int solution(int n) {
    int d[30];
    int l = 0;
    int p;
    while (n > 0) {
        d[l] = n % 2;
        n /= 2;
        l++;
    }

    printf("binary: ");
    for (int i = 0; i < l; ++i) {
        printf("%d", d[i]);
    }
    printf("\n");

    for (p = 1; p <= l / 2; ++p) {
        int ok = 1;
        int i;
        printf("incrementing\n");
        for (i = 1; i < l - p; ++i) {
            printf("p: %d, d[%d]: %d, d[%d]: %d\n", p, i, d[i], i + p, d[i + p]);
            if (d[i] != d[i + p] && &d[i] != &d[i + p]) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            return p;
        }
    }
    return -1;
}

int main()
{
	printf("solution 955: %d\n", solution(955));
	printf("solution 2457: %d\n", solution(2457));
}
