#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(){
    int server_fd,new_socket;
    struct sockaddr_in address;
    int addrlen=sizeof(address);
    char buffer[1024]={0};
    char *message="heiorl form the server";

    server_fd=socket(AF_INET,SOCK_STREAM,0);

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(8080);

    bind(server_fd,(struct sockaddr *)&address, sizeof(address));

    listen(server_fd,3);
    printf("the port is listening \n");

    new_socket=accept(server_fd,(struct sockaddr *)&address,(socklen_t *)&addrlen);
    printf("the connection is accepted \n");
    while(1){
        memset(buffer,0,sizeof(buffer));
        read(new_socket,buffer,1024);
        printf("client: %s \n", buffer);

        fgets(buffer,1024,stdin);
        send(new_socket,buffer,sizeof(buffer),0);
        printf("server: %s \n", buffer);
        


    }


    close(new_socket);
    close(server_fd);
    return 0;

}