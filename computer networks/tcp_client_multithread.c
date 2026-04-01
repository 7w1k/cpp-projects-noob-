// tcp_client_mt.c
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
        printf("Server: %s", buffer);
    }
}

int main() {
    struct sockaddr_in serv_addr;
    pthread_t t1, t2;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    pthread_create(&t1, NULL, send_msg, NULL);
    pthread_create(&t2, NULL, recv_msg, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    close(sock);
    return 0;
}