#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 4000
#define MAXLINE 1000
#include <string.h>
#include <math.h>
// Driver code
int main()
{
    char buffer[100];
    char message[20] ="Converterd string :";
    int listenfd, len;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));

    // Create a UDP Socket
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    // bind server address to socket descriptor
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    //receive the datagram
    len = sizeof(cliaddr);

    int n = recvfrom(listenfd, buffer, sizeof(buffer),
            0, (struct sockaddr*)&cliaddr,&len); //receive message from server
    buffer[n] = '\0';
    //for decimal
    int i=0,val;
    long long decimal, place;
    int leng = strlen(buffer);
    decimal = 0;
    place = 1;
    leng --;

    for(i=0; buffer[i]!='\0'; i++)
    {

        if(buffer[i]>='0' && buffer[i]<='9')
        {
            val = buffer[i] - 48;
        }
        else if(buffer[i]>='a' && buffer[i]<='f')
        {
            val = buffer[i] - 97 + 10;
        }
        else if(buffer[i]>='A' && buffer[i]<='F')
        {
            val = buffer[i] - 65 + 10;
        }

        decimal += val * pow(16, leng);
        leng--;
    }
    sendto(listenfd, message, MAXLINE, 0,
        (struct sockaddr*)&cliaddr, sizeof(cliaddr));

    bzero(buffer,sizeof(buffer));
    sprintf(buffer, "%lld", decimal);
    // send the response
    sendto(listenfd, buffer, MAXLINE, 0,
        (struct sockaddr*)&cliaddr, sizeof(cliaddr));
}
