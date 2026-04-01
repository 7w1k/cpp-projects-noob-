// udp_server.c
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;
    char buffer[1024];
    int num1, num2, result;
    char op;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("UDP Server for Arithmetic Operations...\n");

    len = sizeof(client_addr);

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        recvfrom(sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr *)&client_addr, &len);

        // extract values
        sscanf(buffer, "%d %c %d", &num1, &op, &num2);

        // perform operation
        switch (op) {
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
            case '*': result = num1 * num2; break;
            case '/': 
                if (num2 != 0) result = num1 / num2;
                else result = 0;
                break;
            default: result = 0;
        }

        sprintf(buffer, "Result = %d", result);

        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&client_addr, len);
    }

    close(sockfd);
    return 0;
}