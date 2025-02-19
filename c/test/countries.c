#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define PILLAGED 1000000001

void travel_country_and_pillage(int **A, int N, int M, int x, int y, int country_we_are_pillaging)
{
    if (A[y][x] == country_we_are_pillaging) {
        A[y][x] = PILLAGED;
        if (x > 0) {
            travel_country_and_pillage(A, N, M, x - 1, y, country_we_are_pillaging);
        }
        if (x < M - 1) {
            travel_country_and_pillage(A, N, M, x + 1, y, country_we_are_pillaging);
        }
        if (y > 0) {
            travel_country_and_pillage(A, N, M, x, y - 1, country_we_are_pillaging);
        }
        if (y < N - 1) {
            travel_country_and_pillage(A, N, M, x, y + 1, country_we_are_pillaging);
        }
    }
}

int solution(int **A, int N, int M)
{
    int country_count = 0;

    for(int y = 0; y < N; ++y) {
        for(int x = 0; x < M; ++x) {
            if (A[y][x] != PILLAGED) {
                ++country_count;
                travel_country_and_pillage(A, N, M, x, y, A[y][x]);
            }
        }
    }

    return country_count;
}

int main()
{
    int **A;
    int N = 7;
    int M = 3;

    A = (int **)malloc(sizeof(int *)*N);
    for(int i=0; i < N; i++) {
          A[i] = (int *)malloc(sizeof(int)*M);
    }

    A[0][0] = 5;
    A[1][0] = 4;
    A[2][0] = 3;
    A[3][0] = 2;
    A[4][0] = 3;
    A[5][0] = 1;
    A[6][0] = 4;

    A[0][1] = 4;
    A[1][1] = 3;
    A[2][1] = 2;
    A[3][1] = 2;
    A[4][1] = 3;
    A[5][1] = 4;
    A[6][1] = 1;

    A[0][2] = 4;
    A[1][2] = 4;
    A[2][2] = 4;
    A[3][2] = 2;
    A[4][2] = 4;
    A[5][2] = 4;
    A[6][2] = 1;

    printf("solution: %d\n", solution(A, N, M));
}
