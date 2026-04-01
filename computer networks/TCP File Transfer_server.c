// file_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    FILE *fp;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Waiting for client...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // open file
    fp = fopen("test.txt", "r");

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        send(new_socket, buffer, strlen(buffer), 0);
    }

    printf("File sent successfully\n");

    fclose(fp);
    close(new_socket);
    close(server_fd);

    return 0;
}