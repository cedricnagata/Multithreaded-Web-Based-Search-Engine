// Cedric Nagata
// nagatac@uw.edu

#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <stdbool.h>
#include <stdint.h>

void ReadFile(char *new_name);

int main (int argc, char *argv[]) {

    // check arguments
    if (argc != 2) {
        fprintf(stderr, "Wrong argument count\n");
        return EXIT_FAILURE;
    }

    // open directory
    DIR *dirp = opendir(argv[1]);

    if (dirp == NULL) {
        fprintf(stderr, "Could not open directory\n");
        return EXIT_FAILURE;   
    }

    // iterate through directory
    while (true) {
        struct dirent *file = readdir(dirp);

        if (file == NULL) {
            break;
        }

        int name_len = strlen(file->d_name);

        // check if name ends in .txt
        if ((name_len >= 4) && (strcmp(file->d_name + (name_len - 4), ".txt") == 0)) {
            int dir_len = strlen(argv[1]);
            int file_len = strlen(file->d_name);

            char *new_name = (char *) malloc((dir_len + file_len + 2) * sizeof(char));
            if (new_name == NULL) {
                fprintf(stderr, "New file not created\n");
                return EXIT_FAILURE;
            }

            // create new name with file and directory
            snprintf(new_name, dir_len + file_len + 2, "%s/%s", argv[1], file->d_name);
            ReadFile(new_name);
        }
  }
}

void ReadFile(char *new_name) {
    // bytes to read in
    int32_t n = 100;
    
    // open file
    int fd = open(new_name, O_RDONLY);

    if (fd == -1) {
        perror("Open failed\n");
        exit(EXIT_FAILURE);
    }

    // declare buffer array to store characters
    char* buf[n];

    // declare bytes to be read and result
    int32_t bytes = sizeof(buf);
    int result;

    // read contents and print to stdout
    while (true) {
        result = read(fd, buf, bytes);
        
        if (result == -1) { // file not read
            if (errno != EINTR) {
                perror("Read failed\n");
                exit(EXIT_FAILURE);
            }

            continue;

        } else if (result == 0) { // reached end of file
            break;
        } else { // write char to output
            if (fwrite(buf, result, 1, stdout) != 1) {
                fprintf(stderr, "Write failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    close(fd);
}