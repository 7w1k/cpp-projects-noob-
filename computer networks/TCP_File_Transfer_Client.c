// file_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in serv_addr;

    char buffer[1024];
    FILE *fp;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // create file to write
    fp = fopen("received.txt", "w");

    while (read(sock, buffer, sizeof(buffer)) > 0) {
        fprintf(fp, "%s", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    printf("File received successfully\n");

    fclose(fp);
    close(sock);

    return 0;
}