// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define MAXLINE 1024 
  
// Driver code 
void main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr;
	int len, n, in_cnt, out_cnt;	
	int client_len;
	char client_string[MAXLINE];
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
	echo_port=atoi(argv[1]); 
	  
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(echo_port); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
	  
	client_len=sizeof(client);
	//rec 
	in_cnt=recvfrom(sockfd, client_string, BUF_LEN, 0, (struct sockaddr *)&cliaddr, (socklen_t *)&client_len);
	if( in_cnt <0 ){
		printf("Error reading from socket");
		exit(EXIT_FAILURE);
	}
    
	fprintf(stderr, "Message is %d bytes long\n", in_cnt);
    fprintf(stderr, "Message recieved is \"%s\"\n", client_string);
	
	//send
    out_cnt = sendto(sockfd, client_string, in_cnt+1, 0, (struct sockaddr *)&cliaddr, (socklen_t *)&client_len);
	if(out_cnt < 0){
		printf("Error sending to socket");
		exit(EXIT_FAILURE);
	}
    printf("Message sent.\n");  
	
	close(sockfd);
      
} 