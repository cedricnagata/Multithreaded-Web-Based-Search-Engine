// Cedric Nagata
// nagatac@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool inputCheck (char input[]);

int main (int argc, char *argv[]) {
    
    // if argument count is not 1, give error message and return 1
    if (argc != 2) {
        printf("You can only enter one argument!\n");
        return 1;
    }
    
    // make sure input is positive integer
    if (!inputCheck(argv[1])) {
        printf("Argument must be a positive integer!\n");
        return 1;
    }
    
    // convert argument to int
    double n = atoi(argv[1]);
    double ans = 3.0;

    // calculate solution
    for (int j = 1; j <= n; j++) {
        double i = (double) j;
        if (j % 2 == 0) {
            ans -= ((4 / (((2*i) * ((2*i) + 1) * ((2*i) + 2)))));
        } else {
            ans += ((4 / (((2*i) * ((2*i) + 1) * ((2*i) + 2)))));
        }
    }
    
    printf("Our estimate of Pi is %.20f\n", ans);
    return 0;
}

bool inputCheck (char input[]) {
    
    // iterate through input checking each character to be a digit
    for (int i = 0; input[i] != 0; i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }

    return true;
}