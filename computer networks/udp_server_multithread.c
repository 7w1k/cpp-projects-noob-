// udp_server_mt.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

int sockfd;
struct sockaddr_in client_addr;
socklen_t len;

void *send_msg(void *arg) {
    char buffer[1024];
    while (1) {
        fgets(buffer, 1024, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&client_addr, len);
    }
}

void *recv_msg(void *arg) {
    char buffer[1024];
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sockfd, buffer, 1024, 0,
                 (struct sockaddr *)&client_addr, &len);
        printf("Client: %s", buffer);
    }
}

int main() {
    struct sockaddr_in server_addr;
    pthread_t t1, t2;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    len = sizeof(client_addr);

    printf("UDP Server started...\n");

    pthread_create(&t1, NULL, send_msg, NULL);
    pthread_create(&t2, NULL, recv_msg, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    close(sockfd);
    return 0;
}