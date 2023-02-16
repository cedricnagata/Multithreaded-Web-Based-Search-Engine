// Cedric Nagata
// nagatac@uw.edu

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

void CopyAndSort (int64_t input[], int64_t rtn[], int size);

int main (int argc, char **argv) {
    
    // declare arrays and size
    int64_t input[] = {3, 2, -5, 7, 17, 42, 6, 333, 7, 8, -8, 6};
    int size = sizeof(input) / sizeof(input[0]);
    int64_t rtn[size];

    // run function
    CopyAndSort(input, rtn, size);

    // print result
    for(int i = 0; i < size; i++) {
        if (i < size-1) {
            printf("%" PRId64 " ", rtn[i]);
        } else {
            printf("%" PRId64, rtn[i]);
        }
    }
    printf("\n");

    return 0;
}

void CopyAndSort (int64_t input[], int64_t rtn[], int size) {
    
    // insertion sort
    for (int i = 1; i < size; i++) {
        int64_t curr = input[i];
        int j = i - 1;

        while (j >= 0 && curr < input[j]) {
            input[j + 1] = input[j];
            rtn[j + 1] = input[j]; // add sorted element to new array
            j = j - 1;
        }

        input[j + 1] = curr;
        rtn[j + 1] = curr; // add sorted element to new array
    }
}