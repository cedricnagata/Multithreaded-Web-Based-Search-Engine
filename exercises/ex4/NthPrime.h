// Cedric Nagata
// nagatac@uw.edu

#ifndef _EX4_NTHPRIME_H_
#define _EX4_NTHPRIME_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
Returns the nth prime number in the increasing series of 
prime numbers where n is specified by the user.

Arguments:
    - int16_t n for nth prime number
Return:
    - int64_t for prime number to return
*/
int64_t NthPrime(int16_t n);

#endif