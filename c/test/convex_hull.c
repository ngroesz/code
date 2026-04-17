#include <stdio.h>
#include <stdlib.h>

struct Point2D {
    int x;
    int y;
};

int ccw(struct Point2D A1, struct Point2D A2, struct Point2D A3)
{
    return (A2.x - A1.x) * (A3.y - A1.y) - (A2.y - A1.y) * (A3.x - A1.x);
}

float slope(struct Point2D A1, struct Point2D A2)
{
    if (abs(A1.x - A2.y) == 0) {
        return 0;
    }
    return (abs(A1.y - A2.y) / abs(A1.x - A2.x));
}

void swap_points(struct Point2D *A1, struct Point2D *A2)
{
    struct Point2D swap;
    swap.x = A1->x;
    swap.y = A1->y;
    A1->x = A2->x;
    A1->y = A2->y;
    A2->x = swap.x;
    A2->y = swap.y;
}


int partition(struct Point2D A[], struct Point2D lowest_point, int start, int end)
{
    struct Point2D pivot = A[end];
    int i = start - 1;
    for (int j = start; j < end; ++j) {
        if (slope(A[j], lowest_point) < slope(pivot, lowest_point)) {
            i += 1;
            swap_points(&A[i], &A[j]);
        }
    }
    if (slope(A[end], lowest_point) < slope(A[i + 1], lowest_point)) {
        swap_points(&A[end], &A[i + 1]);
    }

    return i + 1;
}

void quicksort(struct Point2D A[], struct Point2D lowest_point, int start, int end)
{
    if (start < end) {
        int partition_index = partition(A, lowest_point, start, end);
        quicksort(A, lowest_point, start, partition_index - 1);
        quicksort(A, lowest_point, partition_index + 1, end);
    }
}


int solution(struct Point2D A[], int N) 
{
    struct Point2D *lowest_point = NULL;

    for(int i = 0; i < N; ++i) {
        if (lowest_point == NULL || A[i].y < lowest_point->y || (A[i].y == lowest_point->y && A[i].x < lowest_point->x)) {
            lowest_point = &A[i];
        }
    }

    swap_points(&A[0], lowest_point);
    
    quicksort(A, A[0], 0, N - 1);
    return 0;
}

int main()
{
    struct Point2D A[6];

    A[0].x = 3; 
    A[1].x = 6;   
    A[2].x = 2;   
    A[3].x = 5;   
    A[4].x = 1;   
    A[5].x = 4;   

	A[0].y = 2;
	A[1].y = 3;
	A[2].y = 5;
	A[3].y = 2;
	A[4].y = 1;
	A[5].y = 4; 

    printf("solution: %d\n", solution(A, 5));
}


