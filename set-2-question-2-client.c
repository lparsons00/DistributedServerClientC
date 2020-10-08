#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<signal.h>
#include<errno.h>
#include<ctype.h>

#define SERVER_TCP_PORT 6086

int main(){
	int sock = 0;
	struct sockaddr_in, serv_addr;
	char buf[1024];
	
	if((sock = socket(AF_INET, SOCK_STREAM, 0))<0){
		printf("Socket creation error.");
		exit(EXIT_FAILURE);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port =htonls(PORT);
	inet_pton(AF_INET, "/*manually enter ip address */", &serv_addr.serv_addr);
	
	if(connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0){
		printf("Connection Error!");
		exit(EXIT_FAILURE);
	
	}
	while(1){
		printf("Enter Message:");
		bzero(buf, 1024);
		fgets(buf, 1024, stdin);
		
		if(write(sock, buf, strlen(buf)) < 0){
			printf("Writing Error!");
			exit(EXIT_FAILURE);
		}
		bzero(buf, 1024);
		read(sock, buf, 1023);
		printf("Message from server:%s", buf);
	}
	return 0;

}