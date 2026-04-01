// tcp_server_mt.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

int sock;

void *send_msg(void *arg) {
    char buffer[1024];
    while (1) {
        fgets(buffer, 1024, stdin);
        send(sock, buffer, strlen(buffer), 0);
    }
}

void *recv_msg(void *arg) {
    char buffer[1024];
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        read(sock, buffer, 1024);
        printf("Client: %s", buffer);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pthread_t t1, t2;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Waiting for client...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    sock = new_socket;

    pthread_create(&t1, NULL, send_msg, NULL);
    pthread_create(&t2, NULL, recv_msg, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    close(sock);
    close(server_fd);
    return 0;
}