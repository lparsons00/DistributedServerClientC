#include <#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define SA struct sockaddr 

/* takes instr reverses it and stores the reversed string in outstr */
int string_reverse(char *instr, char *outstr)
{
	int j, len, test;
	len=strlen(instr);
	for(j=0;j<len;j++)	{
		test = len-1-j;
		outstr[j]=instr[test];
	}
	outstr[len]=’\0’;
	return len;
}


void exit(char *buff){
	bzero(buff, MAX);
	char strExit[10] = "exit";
	memcpy(buff, strExit, strlen(strExit));
}

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
	char buff[MAX]; 
	char buffSend[MAX];
	int n; 
	//loop for communication 
	for (int i =0; i < max_iterations;i++) { 
		bzero(buff, MAX); 

		// read the message from client and copy it in buffer 
		read(sockfd, buff, sizeof(buff)); 
		// print buffer which contains the client contents 
		printf("From client: %s\t To client : ", buff); 
		bzero(buff, MAX); 
		n = 0; 
		//reverse string from original buffer
		if(i == max_iterations-1){
			exit(buffSend);
		} else {
			string_reverse(buff, buffSend);
		}
		
		// and send that buffer to client 
		write(sockfd, buffSend, sizeof(buffSend)); 
	} 
} 

// Driver function 
int main(int argc, char *argv[]) 
{ 
	int max_iterations;
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 
	short echo_port;

	/* Check for correct command line usage */
	if(argc!=3){
		fprintf(stderr,"Usage: %s Port max_iterations\n",argv[0]);
		exit(EXIT_FAILURE);
	}	
	
	/* Grab the command line arguments and decode them */
	echo_port=atoi(argv[1]);
	max_iterations=atoi(argv[2]);

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(EXIT_FAILURE); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(echo_port); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server waiting for client message..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(sockfd); 
} 
