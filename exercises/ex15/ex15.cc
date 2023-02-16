// Cedric Nagata
// nagatac@uw.edu

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <fcntl.h>

#include "./Network.h"

#define BUF 256

void Usage(char *progname);

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        Usage(argv[0]);
    }

    unsigned short port = 0;
    if (sscanf(argv[2], "%hu", &port) != 1)
    {
        Usage(argv[0]);
    }

    // Get an appropriate sockaddr structure.
    struct sockaddr_storage addr;
    size_t addrlen;
    if (!LookupName(argv[1], port, &addr, &addrlen))
    {
        Usage(argv[0]);
    }

    // Connect to the remote host.
    int socket_fd;
    if (!Connect(addr, addrlen, &socket_fd))
    {
        Usage(argv[0]);
    }

    int file_fd = open(argv[3], O_RDONLY);
    if (file_fd == -1)
    {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    char readbuf[BUF];
    int bytes_read;
    while (1)
    {
        bytes_read = read(file_fd, readbuf, BUF - 1);
        if (bytes_read == 0)
        {
            std::cout << " [The client disconnected.]" << std::endl;
            break;
        }
        if (bytes_read == -1)
        {
            if ((errno == EAGAIN) || (errno == EINTR))
                continue;

            std::cout << " [Error on client socket: ";
            std::cout << strerror(errno) << "]" << std::endl;
            break;
        }
        else
        {
            readbuf[bytes_read] = '\0';
            int bytes_left = bytes_read;
            while (bytes_left > 0)
            {
                int wres = write(socket_fd, readbuf + (bytes_read - bytes_left), bytes_left);
                if (wres == 0)
                {
                    std::cerr << "socket closed prematurely" << std::endl;
                    close(file_fd);
                    close(socket_fd);
                    return EXIT_FAILURE;
                }
                if (wres == -1)
                {
                    if (errno == EINTR)
                        continue;
                    std::cerr << "socket write failure: " << strerror(errno) << std::endl;
                    close(file_fd);
                    close(socket_fd);
                    return EXIT_FAILURE;
                }
                break;
            }
        }
    }

    // Clean up.
    close(file_fd);
    close(socket_fd);
    return EXIT_SUCCESS;
}

void Usage(char *progname)
{
    std::cerr << "usage: " << progname << " port" << std::endl;
    exit(EXIT_FAILURE);
}