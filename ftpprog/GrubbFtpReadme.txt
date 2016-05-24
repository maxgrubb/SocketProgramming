*********************** Max Grubb Network Assignment 2 FTP Program Readfile **********************
This program comes with three files: 
1 server1.c SERVER
2 nc.py CLIENT
3 makefile


Use Instructions: 

IMPORTANT: Best functionality occurs when the client (nc.py) and server (server1.c/ftpServer) are located 
on completely separate hosts. The use of '127.0.0.1' or localhost generally will not allow the programs
to completely create a second data connection with each other 

COMPILATION: 
nc.py needs no compilation
To compile the server program, ensure 'server1.c' and 'makefile' are located in the same directory. At your command prompt, 
type 'make'. The program will compile, and you will have an executable called 'ftpServer'

USE:
The client can request files or the current directory contents of the server

To start the server, at your prompt enter: ftpServer <SERVER PORT> 
The server address will print on screen for use by the client
To reach the server for directory listing enter: python nc.py <SERVER ADDRESS> <SERVER PORT> -l <CLIENT PORT>
To reach the server for download, enter: python nc.py <SERVER ADDRESS> <SERVER PORT> -g <FILENAME> <CLIENT PORT>

SERVER PORT is chosen by the user and is the listening port for the server socket
CLIENT PORT is chosen by the user and is used by the client to listen for the data connection from the server

Trouble shooting: if the client does not accept the data connection from the server, try a new port number or wait a minute
for the port to shut down on its own and try again. 

Also note that if a file does not exist, it is initially created in the client directory, then deleted upon exit. 

THIS PROGRAM CAN TRANSFER Executables, or C programs that have been compiled. WARNING: however, this program was not 
designed with that in mind, and the author makes no guarantees. This was discovered in last minute testing. 

For questions, please contact Max Grubb: 
(480) 688 - 0516
grubbm@oregonstate.edu


Binary transfers coming soon! Now a word from our sponsors.....
