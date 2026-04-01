#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    int sock =0;
    struct sockaddr_in serv_addr;
    char buffer[1024]={0};
    char *message="hiii from the client";

    sock=socket(AF_INET,SOCK_STREAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port =htons(8080);

    inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr);

    connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    while(1){
        memset(buffer,0,sizeof(buffer));


        fgets(buffer,1024,stdin);

        send(sock,buffer,1024,0);
        read(sock,buffer,1024);
        printf("server: %s \n", buffer);

    }

    close(sock);
    return 0;

    
}