#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

#define USAGE \
    "Usage:\n" \
    "%s [host] [service]\n" \
    "one of host or service must be specified.\n"

#define SOCK_DOMAIN (AF_INET)
#define SOCK_TYPE (SOCK_STREAM)
#define SOCK_PROTOCOL (0)       /* by default */

void validation(void);
void init_template(struct addrinfo *aip);

int
main(int argc, char **argv)
{
    int fd;
    char *host;
    char *service;
    struct addrinfo addr_filter;
    struct addrinfo *aip = NULL;
    char addrstr[INET_ADDRSTRLEN];
    char buffer[256] = "GET /index.php HTTP/1.1\r\n";

    switch (argc) {
        case 1:
            printf(USAGE, argv[0]);
            return 0;
        case 2:
            validation();
            host = argv[1];
            service = NULL;     /* if not specified, it will be NULL */
            break;
        case 3:
            validation();
            host = argv[1];
            service = argv[2];
            break;
        default:
            break;
    }

    init_template(&addr_filter);
    printf("%d\n", getaddrinfo(argv[1], argv[2], &addr_filter, &aip));

    inet_ntop(SOCK_DOMAIN, &((struct sockaddr_in *)aip->ai_addr)->sin_addr, addrstr, INET_ADDRSTRLEN);
    printf("%s\n", addrstr);

    fd = socket(SOCK_DOMAIN, SOCK_TYPE, SOCK_PROTOCOL);

    connect(fd, aip->ai_addr, aip->ai_addrlen);

    send(fd, buffer, sizeof buffer - 1, MSG_DONTWAIT);
    
    sleep(1);

    recv(fd, buffer, sizeof buffer - 1, MSG_DONTWAIT);

    printf("%s\n", buffer);

    //shutdown(fd, SHUT_RDWR);

    return 0;
}

void
init_template(struct addrinfo *aip)
{
    memset(aip, 0x00, sizeof (struct addrinfo));
    aip->ai_flags = AI_NUMERICHOST | AI_NUMERICSERV;
}

void
validation(void)
{

}
