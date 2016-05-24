/*****************************
 * Name: Max Grubb
 * Date 2/7/2016
 * Program: Server.cpp
 * Description: Server program for chatting 
 * ***************************/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>



int main (int argc, char* argv[] ){

struct addrinfo grubbConn, *res1;  
int grubbSocket; 
int bufferSize = 500;
char buffer[bufferSize]; 
char buf2[6] = "\\quit";
int status;
int i; 
char chandle[10]; 

/*set up structures and memory */

memset(&grubbConn, 0, sizeof(grubbConn)); 
grubbConn.ai_family = AF_UNSPEC; 
grubbConn.ai_socktype = SOCK_STREAM; 

printf("Connecting to: %s  on Port: %s\n", argv[1], argv[2]);

printf("Please enter your handle: ");
fgets(chandle, sizeof(chandle), stdin); 

/*remove newline from handle name*/
for(i=0; i<strlen(chandle); i++){
	if(chandle[i] == '\n')
		chandle[i] = '\0';
}

/*get address info from command line and pass to structures for connections*/

if(getaddrinfo(argv[1], argv[2], &grubbConn, &res1) != 0)
	printf("No initial connect!\n"); 


/*create socket*/
grubbSocket = socket(res1->ai_family, res1->ai_socktype, res1->ai_protocol); 

/*make connection*/

if((status = connect(grubbSocket, res1->ai_addr, res1->ai_addrlen) < 0))
{
	printf("Unable to connect\n"); 
	return 1;	
}
	printf("Enter \\quit to terminate connection\n"); 

/* nested Loop for chatting */	
	 while(*buffer != 35){
	
		printf("%s> ", chandle);
		fgets(buffer, bufferSize, stdin); 
		if(*buffer == *buf2)
		{
			send(grubbSocket, buffer, bufferSize, 0); 
			printf("\nConnection Terminiated. Goodbye\n");  
			freeaddrinfo(res1); 
			close(grubbSocket); 
			return 1; 
		}

		send(grubbSocket, buffer, bufferSize, 0); 

		printf("Server: ");
		recv(grubbSocket, buffer, bufferSize, 0); 	
		if(*buffer == *buf2)
			{	
				printf("\nConnection terminated by Server. Goodbye!\n"); 
				freeaddrinfo(res1); 
				close(grubbSocket); 
				return 1; 
			}
			printf("%s\n", buffer); 
	}

	printf("Connection terminated. Goodbye!\n");
 

/*free structures and close sockets*/
freeaddrinfo(res1); 
close(grubbSocket); 
	return 0; 	


}





