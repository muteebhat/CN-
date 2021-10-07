#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int sock;
    struct sockaddr_in server_addr,client_addr;
    struct hostent * host;
    char send_data[1024],recvdata[1024];
    int bytes_read, addr_len;

    host = (struct hostent *) gethostbyname ((char *)"192.168.10.1");

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0 )) == -1)
    {
        perror("socket");
        exit(1);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), 8);


    while(1)
    {
        //client sends choice
        printf("\nClient: ");
        gets(send_data);
        sendto(sock, send_data, strlen(send_data), 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

        //server will ask for choice
        printf("Server is sending choice....");
        bytes_read = recvfrom(sock, recvdata, 1024, 0, (struct sockaddr *)&server_addr, &addr_len);
        recvdata[bytes_read] = '\0';
        printf("Server: %s", recvdata);

        //clients sends choice
        printf("\nClient: ");
        fgets(send_data);
        sendto(sock, send_data, strlen(send_data), 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

        //If client doesn't choose 1 or 2 then exit
        if((strcmp(send_data, "1") !=0) && strcmp(send_data, "2") !=0)
        {
            printf("\nExiting...\n");
            break;
        }

        //Server will ask for string
        bytes_read = recvfrom(sock,recvdata,1024,0,(struct sockaddr *)&server_addr,&addr_len);
        recvdata[bytes_read] = '\0';
        printf("\nServer: %s", recvdata);

        //client sends choice
        printf("\nClient: ");
        gets(send_data);
        sendto(sock,send_data,strlen(send_data),0,(struct sockaddr *)&server_addr, sizeof(struct sockaddr));

        //server will send the converted string
        bytes_read = recvfrom(sock,recvdata,1024,0,(struct sockaddr *)&server_addr,&addr_len);
        recvdata[bytes_read] = '\0';
        printf("\nServer: %s", recvdata);


    }
}
