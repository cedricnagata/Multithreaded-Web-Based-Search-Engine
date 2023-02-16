// Cedric Nagata
// nagatac@uw.edu

#include <stdio.h>
#include <cstdlib>
#include <iostream>

int main (int argc, char *argv[]) {
    int input;

    // get input number 
    std::cout << "Which positive integer would you like me to factorize? ";
    std::cin >> input;

    // input must be greater than 0
    if (input <= 0) {
        std::cout << "0 cannot be input" << std::endl;
        return EXIT_FAILURE;
    }

    // check each number to see if it is factor
    for (int i = 1; i <= input; i++) {
        if (input % i == 0) {
            if (i == 1) {
                std::cout << "" << i;
            } else {
                std::cout << " " << i;
            }
        }
    }

    std::cout << std::endl;
    return EXIT_SUCCESS;
}