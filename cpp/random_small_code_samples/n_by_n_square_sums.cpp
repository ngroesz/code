#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

bool check_sums(int numbers[], int size)
{
    int side_length = (int)sqrt(size);
    int row_count = size / side_length;

    // check rows and columns
    int last_row_sum = 0;
    int last_column_sum = 0;
    for(int side_index = 0; side_index < row_count; ++side_index) {
        // check a row
        int current_row_sum = 0;
        for(int i = 0; i < side_length; ++i) {
            current_row_sum += numbers[side_length * side_index + i];
        }
        if (last_row_sum == 0) {
            last_row_sum = current_row_sum;
        } else if(last_row_sum != current_row_sum) {
            return false;
        }

        // check a column
        int current_column_sum = 0;
        for(int i = 0; i < side_length; ++i) {
            current_column_sum += numbers[side_length * i + side_index];
        }
        if (last_column_sum == 0) {
            last_column_sum = current_column_sum;
        } else if (last_column_sum != current_column_sum) {
            return false;
        }
    }

    return true;
}

void print_numbers(int numbers[], int size)
{
    int side_length = (int)sqrt(size);
    int row_count = size / side_length;

    for(int i=0; i<size; ++i) {
        cout << numbers[i] << " ";
        if ((i + 1) % side_length == 0) {
            cout << endl;
        }
    }
}

void make_square(int size)
{
    int *numbers;

    numbers = new int[size];

    for(int i=0; i<size; ++i) {
        numbers[i] = i + 1;
    }

    int check_count = 0;
    do {
        ++check_count;
        //print_numbers(numbers, size);
        if (check_sums(numbers, size)) {
            cout << "found the answer!" << endl;
            print_numbers(numbers, size);
            return;
        }
        //if (check_count > 2) {
        //    return;
        //}
    } while (next_permutation(numbers, numbers+size));
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "I need a number, baby" << endl;
        exit(0);
    }

    int size = atoi(argv[1]);
    make_square(size);
}
