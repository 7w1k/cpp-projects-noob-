// udp_chat_server.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("UDP Chat Server started...\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        // receive message
        recvfrom(sockfd, buffer, 1024, 0,
                 (struct sockaddr *)&client_addr, &len);
        printf("Client: %s\n", buffer);

        // exit condition
        if (strncmp(buffer, "exit", 4) == 0) break;

        // send reply
        printf("Server: ");
        fgets(buffer, 1024, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&client_addr, len);

        if (strncmp(buffer, "exit", 4) == 0) break;
    }

    close(sockfd);
    return 0;
}