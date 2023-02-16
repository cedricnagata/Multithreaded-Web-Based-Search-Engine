// Cedric Nagata
// nagatac@uw.edu

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    
    // if argument count is not 1, give error message and return 1
    if (argc != 2) {
        fprintf(stderr, "Error inputting filename\n");
        return 1;
    }

    // open file
    FILE *file = fopen(argv[1], "rb");

    // if file doesn't exist
    if (file == NULL) {
        fprintf(stderr, "Error finding file\n");
        return EXIT_FAILURE;
    }

    // find size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    // iterate through characters backwards from end
    for (long bytePtr = size - 1; bytePtr >= 0; bytePtr--) {
        char c;

        fseek(file, bytePtr, SEEK_SET);
        fread(&c, sizeof(char), 1, file);

        printf("%c", c); // print characters
    }

    fclose(file);
    return EXIT_SUCCESS;
}