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
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in  servaddr; 
	int in_cnt, out_cnt, len; 
	int string_size;
	struct hostent *server_host;
	int server_port;
	char client_send_string[MAXLINE];
	
	if(argc!=4){
		fprintf(stderr,"Usage: %s Server Port send_string\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	
	
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    memset(&servaddr, 0, sizeof(servaddr)); 
	  
	server_host=gethostbyname(argv[1]);
	if (server_host == NULL){
		herror("While calling gethostbyname()");
		exit(EXIT_FAILURE);
	}
	
	server_port=atoi(argv[2]);
	strcpy(client_send_string,argv[3]);
	
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(server_port); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    string_size=strlen(client_send_string)+1;
      
	out_cnt=sendto(sockfd, client_send_string, string_size, 0,(struct sockaddr *)&servaddr ,sizeof(servaddr));  
	if(out_cnt<0){
		perror("While calling sendto()");
		exit(EXIT_FAILURE);
	} else {
		printf("Message sent.\n"); 
    }
	
	fprintf(stderr,"Have reached recvfrom(), should now block until message receipt\n");
	len=sizeof(servaddr);
	in_cnt=recvfrom(sockfd, (char *)buffer , MAXLINE, 0,(struct sockaddr *)&servaddr,&len);
    buffer[in_cnt] = '\0'; 
    printf("Server : %s\n", buffer); 
  
    close(sockfd); 
    return 0; 
} 