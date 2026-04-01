// udp_client_mt.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

int sockfd;
struct sockaddr_in server_addr;
socklen_t len;

void *send_msg(void *arg) {
    char buffer[1024];
    while (1) {
        fgets(buffer, 1024, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&server_addr, len);
    }
}

void *recv_msg(void *arg) {
    char buffer[1024];
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sockfd, buffer, 1024, 0,
                 (struct sockaddr *)&server_addr, &len);
        printf("Server: %s", buffer);
    }
}

int main() {
    pthread_t t1, t2;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    len = sizeof(server_addr);

    pthread_create(&t1, NULL, send_msg, NULL);
    pthread_create(&t2, NULL, recv_msg, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    close(sockfd);
    return 0;
}