#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main()
{
int sock;
struct sockaddr_in server_addr,client_addr;
struct hostent *host;
char send_data[1024],recvdata[1024];
int bytes_read,addr_len;
host= (struct hostent *) gethostbyname((char *)"127.1.32.36");
if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
{
perror("socket");
exit(1);
}
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(8000);
server_addr.sin_addr = *((struct in_addr *)host->h_addr);
bzero(&(server_addr.sin_zero),8);
 while (1)
 {
 printf("\nClient :");
 fgets(send_data);
 if ((strcmp(send_data,"q") == 0) || strcmp(send_data,"Q") == 0)
 {
 sendto(sock, send_data, strlen(send_data), 0,
 (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
 
 
 break;
 }
 else
 sendto(sock, send_data, strlen(send_data), 0,
 (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
 
 bytes_read=recvfrom(sock,recvdata,1024,0,(struct sockaddr*)&server_addr,&addr_len);
 
 recvdata[bytes_read]='\0';
 if ((strcmp(recvdata , "q") == 0) || strcmp(recvdata , "Q") == 0)
 break;
 else
 {
 
 printf("\nServer : %s", recvdata);
 fflush(stdout);
 }
 }
}
