#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
// #include<netdb.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int str_to_num(char arr[])
{
    int num = 0, i=0;
    while (arr[i] != '\0')
    {
        num *=10;
        num +=(int) arr[i] - '0';
        i++;
    }
    return num;
}

int main()
{
    int sock,choice;
    int addr_len, bytes_read;
    char recv_data[1024], send_data[1024];
    struct sockaddr_in server_addr,client_addr;
    int A_to_a = 32;


     if ((sock = socket(AF_INET, SOCK_DGRAM, 0 )) == -1)
    {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), 8);

    if(bind(sock,(struct sockaddr *)&server_addr, 
    sizeof(struct sockaddr)) ==-1 )
    {
        perror("Bind");
        exit(1);

    }

    addr_len = sizeof(struct sockaddr);
    printf("\nUDPServer waiting for client on port 9000\n\n");
    fflush(stdout);

    while(1)
    {
        bytes_read = recvfrom(sock,recv_data,1024,0,
        (struct sockaddr *)&client_addr,&addr_len);


        recv_data[bytes_read] = '\0';
        printf("\nClient: %s",recv_data);


        strcpy(send_data, "\nEnter the string:");
        printf("\nServer: %s", send_data);
        sendto(sock,send_data,strlen(send_data),0,(struct sockaddr*)&client_addr,sizeof(struct sockaddr));

        //Take the string as client input
        bytes_read = recvfrom(sock,recv_data,1024,0,(struct sockaddr *)&client_addr,&addr_len);
        recv_data[bytes_read] = '\0';
        printf("\nClient: %s", recv_data);

        //convert the string: Uppercase to Lowercase
        {
            for(int i =0; i<strlen(recv_data);i++)
            {
                if(recv_data[i] >='A' && recv_data[i]<='Z')
                {
                    send_data[i] = recv_data[i] + A_to_a;
                }
                else
                {
                    send_data[i] = recv_data[i];
                }
            }
        }

    
        //send the converted string
        send_data[strlen(recv_data)] = '\0';
        printf("\nServer: %s",send_data);
        sendto(sock,send_data,strlen(send_data),0,(struct sockaddr*)&client_addr,sizeof(struct sockaddr));
    }
return 0;
    
}