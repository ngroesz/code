#include <stdio.h>
#include <iostream>

using namespace std;

int binary_search_for_factor(int key, int factor_1, int last, int last_last)
{
    int half = (key + 1) / 2;

    int result = factor_1 * last;
    int next;

    if (result == key) {
        return last;
    } else if(result < key) {
        next = int(((last_last - last) / 2) + 1) + last;
    } else {
        next = int((last / 2) + 1);
    }

    if (abs(next - last) <= 1) {
        return -1;
    }

    return binary_search_for_factor(key, factor_1, next, last);
}

void factor_key(int key)
{
    int half = (key + 1) / 2;

    for (int i = 3; i <= half; ++i) {
        int j = binary_search_for_factor(key, i, (key + 1) / 2, 0);
        if (j > 0) {
            cout << "answer: " << i << ", " << j << endl;
            return;
        }
    }
}

void simple_factor_key(long unsigned int key)
{
    for (long unsigned int n1 = 3; n1<key; n1+=2) {
        if (key % n1 == 0) {
            long unsigned n2 = key / n1;
            cout << "answer: " << "n1 = " << n1 << " n2 = " << n2 << endl;
            return;
        }
    }
    cout << "drat!" << endl;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "I need a number, baby" << endl;
        exit(0);
    }

    long unsigned int key = atoi(argv[1]);

    // factor_key(key);
    
    simple_factor_key(key);
}
