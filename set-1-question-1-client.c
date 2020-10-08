#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 80 
#define SA struct sockaddr 
void func(int sockfd) 
{ 
    char buff[MAX];
	char buffSend[MAX];
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff));
		bzero(buffSend, sizeof(buffSend));
        printf("Enter the string : "); 
        n = 0; 
        while ((buffSend[n++] = getchar()) != '\n') 
            ; 
        write(sockfd, buffSend, sizeof(buffSend)); 
        bzero(buff, sizeof(buffSend)); 
        read(sockfd, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
  
int main(int argc, char *argv[]) 
{ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
	char client_send_string[MAX];
	struct hostent *server_host;
	short server_port;
	int string_size;
  
	if(argc!=4){
		fprintf(stderr,"Usage: %s Server Port send_string\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	/* Grab the command line arguments and decode them */
	/* Use the resolver to get the addresss of the server */
	server_host=gethostbyname(argv[1]);
	/* if there’s a problem, report it and exit */
	if (server_host == NULL)
		{
		herror("While calling gethostbyname()");
		exit(EXIT_FAILURE);
		}
	server_port=atoi(argv[2]);
	strcpy(client_send_string,argv[3]);
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr));


	server.sin_family=AF_INET;
	memcpy(&server.sinaddr.saddr, server_host->h_addr_list[0],server_host->h_length);
	server.sin_port=htons(server_port);
	/* set the length so that the trailing nul gets sent as well */
	string_size=strlen(client_send_string)+1;
	
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for communication 
    func(sockfd); 
  
    // close the socket 
    close(sockfd); 
} 