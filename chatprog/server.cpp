/*****************************
 * Name: Max Grubb
 * Date 2/7/2016
 * Program: Server.cpp
 * Description: Server program for chatting 
 * ***************************/

#include <iostream>
#include <iomanip>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;


int main(int argc, char *argv[])
{
	struct sockaddr_storage their_addr; 
	struct addrinfo hints, *res;
	socklen_t addr_size;
	addr_size = sizeof their_addr; 
	int sockfd, new_fd; 
	int bufferSize = 500;
	char buffer[bufferSize]; 
	char buf2[6] = {"\\quit"};
	int status1; 

/*set up structures and get address info for socket*/
	memset(&hints, 0, sizeof hints); 
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM; 
	getaddrinfo(NULL, "3500", &hints, &res); 

/*Create socket*/
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 

/*Catch errors*/	
	if (sockfd < 0)
	{
		cout << "Connection establishment error." << endl;
		return 1; 
	}
		cout << "Socket created.." << endl;

/*Assoiate socket to local machine*/
 	
	status1 = bind(sockfd, res->ai_addr, res->ai_addrlen);;

	if(status1 < 0)
	{ 	

		cout << "Binding serror" << endl;
		return 1; 
	}	  
	else
	{
		cout << "Waiting on connection" << endl;
	}

/*Listen for connections */
	listen(sockfd, 0); 

	/*Accept connection*/
	status1 = (new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size));  
	
	if(status1 < 0)
	{
		cout << "Acceptance Error" << endl;
		return 1; 
	}
	else
	{	
		cout << "No acceptance error" << endl;
	}

/*Netsed loop structure to handle back and forth messaging*/

	while(status1 > 0) 
	{

		cout << "Connection with client estabished" << endl;
		cout << "Enter \\quit  to terminate" << endl; 
	do{
		cout << "Client:";

		recv(new_fd, buffer, bufferSize, 0); 
		if(*buffer == *buf2)
		{
		cout << "\nConnection terminated by client.\n"; 
			return 1;
			close(new_fd); 
			close(sockfd); 
			freeaddrinfo(res); 
		}			

		cout << buffer; 
		cout << "Server: ";
		cin.getline(buffer, bufferSize); 
		send(new_fd, buffer, bufferSize, 0); 
	}while(*buffer != *buf2);		


	cout << "Connection terminated. Goodbye!" << endl;
	
/*Close sockets and free pointer memory*/
	close(new_fd); 
	close(sockfd); 
	freeaddrinfo(res); 
	return 0; 
}
} 
