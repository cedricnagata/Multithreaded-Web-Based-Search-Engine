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

// prints out error message
void Usage(char *progname);

// read data from client and print to stdout
void HandleClient(int c_fd, struct sockaddr *addr, size_t addrlen,
                  int sock_family);

int main(int argc, char **argv)
{
    // Expect the port number as a command line argument.
    if (argc != 2)
    {
        Usage(argv[0]);
    }

    int sock_family;
    int listen_fd = Listen(argv[1], &sock_family);
    if (listen_fd <= 0)
    {
        // We failed to bind/listen to a socket.  Quit with failure.
        std::cerr << "Couldn't bind to any addresses." << std::endl;
        return EXIT_FAILURE;
    }

    while (1)
    {
        struct sockaddr_storage caddr;
        socklen_t caddr_len = sizeof(caddr);
        int client_fd = accept(listen_fd,
                               reinterpret_cast<struct sockaddr *>(&caddr),
                               &caddr_len);
        if (client_fd < 0)
        {
            if ((errno == EINTR) || (errno == EAGAIN) || (errno == EWOULDBLOCK))
                continue;
            std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
            break;
        }

        HandleClient(client_fd,
                     reinterpret_cast<struct sockaddr *>(&caddr),
                     caddr_len,
                     sock_family);
        break;
    }

    // Close file descriptor
    close(listen_fd);
    return EXIT_SUCCESS;
}

void Usage(char *progname)
{
    std::cerr << "usage: " << progname << " port" << std::endl;
    exit(EXIT_FAILURE);
}

void HandleClient(int c_fd, struct sockaddr *addr, size_t addrlen,
                  int sock_family)
{
    char readbuf[BUF];
    int bytes_read;

    while (1)
    {
        bytes_read = read(c_fd, readbuf, BUF - 1);
        if (bytes_read == 0)
        {
            std::cout << " [The client disconnected.]" << std::endl;
            break; // EOF
        }
        else if (bytes_read == -1)
        {
            if ((errno != EAGAIN) && (errno != EINTR))
            {
                std::cout << " [Error on client socket: ";
                std::cout << strerror(errno) << "]" << std::endl;
                break;
            }
            // try again since error is EINTR
            continue;
        }
        else
        {
            readbuf[bytes_read] = '\0'; // set EOF
            int bytes_left = bytes_read;

            while (bytes_left > 0)
            {
                int bytes_written = write(1, readbuf + (bytes_read - bytes_left), bytes_left);
                if (bytes_written == 0)
                {
                    break; // reached EOF
                }
                else if (bytes_written == -1)
                {
                    if (errno != EINTR)
                    {
                        // Error is not acceptable
                        std::cerr << "write failed: " << strerror(errno) << std::endl;
                    }
                    continue;
                }
                
                bytes_left -= bytes_written;
            }
        }
    }

    close(c_fd);
}