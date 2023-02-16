// Cedric Nagata
// nagatac@uw.edu

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "./NthPrime.h"

int main(int argc, char **argv) {
    if (NthPrime(5) != 11 || NthPrime(10) != 29 || NthPrime(100) != 541) {
        fprintf(stderr, "Test cases failed\n");
        return EXIT_FAILURE;
    }
    
    printf("The 5th prime number is %" PRId64 "\n", NthPrime(5));
    printf("The 10th prime number is %" PRId64 "\n", NthPrime(10));
    printf("The 100th prime number is %" PRId64 "\n", NthPrime(100));

    return EXIT_SUCCESS;
}