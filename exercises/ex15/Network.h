// Cedric Nagata
// nagatac@uw.edu

#ifndef _NETWORK_H_
#define _NETWORK_H_

bool LookupName(char *name,
                unsigned short port,
                struct sockaddr_storage *ret_addr,
                size_t *ret_addrlen);

bool Connect(const struct sockaddr_storage &addr,
             const size_t &addrlen,
             int *ret_fd);

#endif