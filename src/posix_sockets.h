#if !defined(__POSIX_SOCKET_TEMPLATE_H__)
#define __POSIX_SOCKET_TEMPLATE_H__

#include <stdio.h>
#include <sys/types.h>
#if !defined(WIN32)
#include <netdb.h>
#include <sys/socket.h>
#else
#include <ws2tcpip.h>
static int ws_started = 0;
#endif
#if defined(__VMS)
#include <ioctl.h>
#endif
#include <fcntl.h>

/*
    A template for opening a non-blocking POSIX socket.
*/
int open_nb_socket(const char *addr, const char *port);

int open_nb_socket(const char *addr, const char *port) {
  int rv;
#ifdef WIN32
  if (!ws_started) {
    WSADATA data;
    rv = WSAStartup(MAKEWORD(2, 2), &data);
    if (rv != 0) {
      printf("WSAStartup failed: %d\n", rv);
      return -1;
    }
    ws_started = 1;
  }
#endif
  struct addrinfo hints = {0};

  hints.ai_family = AF_UNSPEC;     /* IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* Must be TCP */
  int sockfd = -1;
  struct addrinfo *p, *servinfo;

  /* get address information */
  rv = getaddrinfo(addr, port, &hints, &servinfo);
  if (rv != 0) {
    fprintf(stderr, "Failed to open socket (getaddrinfo): %d\n", rv);
    return -1;
  }

  /* open the first possible socket */
  for (p = servinfo; p != NULL; p = p->ai_next) {
    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (sockfd == -1)
      continue;

    /* connect to server */
    rv = connect(sockfd, p->ai_addr, p->ai_addrlen);
    if (rv == -1) {
      close(sockfd);
      sockfd = -1;
      continue;
    }
    break;
  }

  /* free servinfo */
  freeaddrinfo(servinfo);

  /* make non-blocking */
#if !defined(WIN32)
  if (sockfd != -1)
    fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);
#else
  if (sockfd != INVALID_SOCKET) {
    int iMode = 1;
    ioctlsocket(sockfd, FIONBIO, &iMode);
  }
#endif
#if defined(__VMS)
  /*
      OpenVMS only partially implements fcntl. It works on file descriptors
      but silently fails on socket descriptors. So we need to fall back on
      to the older ioctl system to set non-blocking IO
  */
  int on = 1;
  if (sockfd != -1)
    ioctl(sockfd, FIONBIO, &on);
#endif

  /* return the new socket fd */
  return sockfd;
}

#endif
