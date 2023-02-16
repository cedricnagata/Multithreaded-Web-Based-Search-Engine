// Cedric Nagata
// nagatac@uw.edu

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./NthPrime.h"

bool checkPrime(int64_t num);

/*
Returns the nth prime number in the increasing series of 
prime numbers where n is specified by the user.

Arguments:
    - int16_t n for nth prime number
Return:
    - int64_t for prime number to return
*/
int64_t NthPrime(int16_t n) {
    int16_t primeCtr = 0;
    int16_t num = 0;

    if (n == 0) {
        fprintf(stderr, "n cannot be 0\n");
        return EXIT_FAILURE;
    }

    while(primeCtr != n) {
        num++;
        
        if(checkPrime(num)) {
            primeCtr++;
        }
    }

    return num;
}

bool checkPrime(int64_t num) {
    if (num == 2) {
        return true;
    } else if (num == 1) {
        return false;
    }
    for(int i = 2; i <= (num / 2); i++) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}