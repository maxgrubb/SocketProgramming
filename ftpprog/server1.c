/**************************************
 * File Name: server1.c
 * Author: Max Grubb
 * Date: 3/7/2015
 * Description: Server implementation 
 * of ftp program
 * ************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <string.h>
#define MAXLINE 4096

int main (int argc, char **argv)
{
FILE *servFile; 
size_t fl; 
DIR *dp;
struct dirent *ep;
socklen_t len;
struct sockaddr_storage addr;
struct sockaddr_in cliaddr, cli2addr, servaddr;
struct addrinfo grubbConn, hints, hints1, *res, *res2, *p;
socklen_t clilen, cli2len;
char ipstr[INET6_ADDRSTRLEN];
char buf[MAXLINE], buf2[MAXLINE];
char *tok, *tok1, *token, *servString; 
int port, hn, listenfd, connfd, grubbSocket, secConn, conn2fd,  n, status, status1;
int d = 0;  
char* x[4] = {};
char* y[4] = {};
char name[32], ferror[40];


/************************************
 * Get Local Host Information
 * *********************************/

        hn = gethostname(name, 32);
        printf("%s\n", name);
//set struct memory for getaddrinfo 


	memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

//Get address information and pass to struct res
//
        if((status = getaddrinfo(name, NULL, &hints, &res)) !=0){
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
                return 2;
        }


	 printf("IP address for %s:\n\n", argv[1]);

//check structures for ipV4 information
         for(p = res; p != NULL; p = p->ai_next){
                void *addr;
                char *ipver;

                        struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
                        addr = &(ipv4->sin_addr);
                        ipver = "IPv4";

                inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
                printf(" %s: %s\n", ipver, ipstr);
	}	

	freeaddrinfo(res);

//set struct memory for getaddrinfo 
	memset(&hints, 0, sizeof hints); 
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM; 

//get actual port information and include with IP address 
	if(getaddrinfo(ipstr, argv[1], &hints, &res) != 0)	
	{
		printf("Testtttt\n");
	}

//create socket
	if ((listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) <0) {
		perror("Problem in creating the socket");
		exit(2);
  	 }

//bind the socket
	status1 = bind(listenfd, res->ai_addr, res->ai_addrlen);
	if(status1 < 0)
	{
		perror("Bind Error"); 
		return 1;   
	}
for(;;){
//listen to the socket 
	listen(listenfd, 0);
	printf("%s\n","Server running...waiting for connections.\n Press CTRL-C to exit\n");
//listen and accept
	clilen = sizeof(cliaddr);
	connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
	printf("%s\n","Received request...");

	n = recv(connfd, buf, MAXLINE,0);

	len = sizeof addr;
	getpeername(connfd, (struct sockaddr*)&addr, &len);

// show ip address 
	struct sockaddr_in *s = (struct sockaddr_in *)&addr;
	port = ntohs(s->sin_port);
	inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);

	printf("Peer IP address: %s\n", ipstr);


// set up string for parsing 

strcpy(buf2, buf);
tok1 = strtok(buf, " ");
d = 0;  

/*****************************************
 *If loop for directory and file operations
 *
 * **************************************/

if(strcmp(tok1, "-l") == 0){


//parse string

	tok = strtok(buf2, " ");
	do{
		x[d] = strdup(tok); 
		d++; 
		tok = strtok(NULL, " \n");
	} while(tok != NULL);

	printf("Port: %s\n", x[1]);  


//open temp file for directory contents
	servFile = tmpfile();  

//set directory pointer  	
	dp = opendir ("./");

//loop to get contents 	
	if (dp != NULL)
	{
		while (ep = readdir (dp))
		fprintf(servFile, "%s\n" ,ep->d_name);
		(void) closedir (dp);
        }
	else
		perror ("Couldn't open the directory");
	
//set memory for new data connection to client 
			memset(&grubbConn, 0, sizeof grubbConn); 
			grubbConn.ai_family = AF_UNSPEC; 
			grubbConn.ai_socktype = SOCK_STREAM; 

//get and set client information for connection
			if(getaddrinfo(ipstr, x[1], &grubbConn, &res2) != 0)	
			{
				perror("Get Addr Error");
			}
//create client socket
			grubbSocket = socket(res2->ai_family, res2->ai_socktype, res2->ai_protocol);
        		if(grubbSocket < 0)
			{
                		perror("Socket Error");
               		}
//connect to client 
			if((status = connect(grubbSocket, res2->ai_addr, res2->ai_addrlen) < 0))
			{
	      			perror("Connect Error");
			        return 1;
			}
        
			printf("Connected\n");

//get file length, then file contents and send to client
			fseek(servFile, 0L, SEEK_END); 
			fl = ftell(servFile); 	
			printf("length: %i\n", fl); 
			servString = malloc (sizeof(char)*fl);
			rewind(servFile); 
			fread(servString, 1, fl-1, servFile);	
			status1 = send(grubbSocket, servString, fl-1, 0);
			fclose(servFile); 
}

// get file and sent to client
else if(strcmp(tok1, "-g") == 0){

//parse string for operations
	tok = strtok(buf2, " ");
	do{
		y[d] = strdup(tok); 
		d++; 
		tok = strtok(NULL, " \n");
	} while(tok != NULL);

	printf("Port: %s\n", y[2]);  

//set memory for connection
			memset(&grubbConn, 0, sizeof grubbConn); 
			grubbConn.ai_family = AF_UNSPEC; 
			grubbConn.ai_socktype = SOCK_STREAM; 

			if(getaddrinfo(ipstr, y[2], &grubbConn, &res2) != 0)	
			{
				perror("Gett Addr Error");
			}
//set socket 
			grubbSocket = socket(res2->ai_family, res2->ai_socktype, res2->ai_protocol);
        	
			if(grubbSocket < 0)
			{
                		perror("Socket2 Error");
               		}
//connect to client
			if((status = connect(grubbSocket, res2->ai_addr, res2->ai_addrlen) < 0))
			{
	      			perror("Connect Error");
			        return 1;
			}

//get file length, contents and send to client        
			printf("connected\n");
			servFile = fopen(y[1], "r");
			if (servFile == NULL) {
			
				strcpy(ferror, "err"); 
				status1 = send(grubbSocket, ferror, 3, 0);
				
			}	
			else{	
				fseek(servFile, 0L, SEEK_END); 
				fl = ftell(servFile); 	
				printf("length: %i\n", fl); 
				servString = malloc (sizeof(char)*fl);
				rewind(servFile); 
				fread(servString, 1, fl-1, servFile);	
				status1 = send(grubbSocket, servString, fl-1, 0);
				fclose(servFile); 
			}







}

memset(buf, 0, sizeof(buf));
close(grubbSocket);

}

close(connfd);
close(listenfd);
freeaddrinfo(res);
freeaddrinfo(res2);

}




