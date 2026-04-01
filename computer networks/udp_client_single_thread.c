// udp_chat_client.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    socklen_t len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    printf("UDP Chat Client started...\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        // send message
        printf("Client: ");
        fgets(buffer, 1024, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&server_addr, len);

        if (strncmp(buffer, "exit", 4) == 0) break;

        // receive reply
        recvfrom(sockfd, buffer, 1024, 0,
                 (struct sockaddr *)&server_addr, &len);
        printf("Server: %s\n", buffer);

        if (strncmp(buffer, "exit", 4) == 0) break;
    }

    close(sockfd);
    return 0;
}