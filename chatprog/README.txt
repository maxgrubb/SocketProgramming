Read Me For Max' Chat Programs! 

There are two program files for this program: 

connect.c 
server.cpp

There is one makefile. 

These two programs rely on a TCP connection to implement a simple chat program. 

connect.c is the client program and is written in c code
connect.c connects to the server process on the Linux Command Prompt:
chatclient <hostname> <port>

Port 3500 is hard coded into the server process. 

server.cpp is the server program and is written in c++, its executable is 'chatserve'. 
It listens for incoming connections and makes TCP connection to the client program. 
 
To create the program executables, keep connect.c and server.cpp and the makefile in the same
directory and on the command prompt enter: make
 
Two executable files will be created: chatserve and chatclient
 
Chatting is started on the client, and each process will wait for the
other's response, and then can respond on their own. 

The client needs to create a handle upon start. 

To exit the program, either user can enter '\quit'.
 

 
 For questions: 
 Contact Max Grubb 
 email: grubbm@oregonstate.edu
 phone: 480 688 0516
 