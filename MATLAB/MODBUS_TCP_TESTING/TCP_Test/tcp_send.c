#include "tcp_send.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void tcp_send(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "192.168.0.210", &server_addr.sin_addr) <= 0) {
    close(sock);
    }


    int result = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (result < 0) {
    close(sock);
    }

    char message[] = "Hello from PX4!";
    send(sock, message, strlen(message), 0);

    close(sock);

    return;
}
